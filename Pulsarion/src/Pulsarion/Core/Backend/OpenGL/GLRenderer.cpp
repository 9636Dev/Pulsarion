#include "Pulsarionpch.h"
#include "GLRenderer.h"

#include "Enum.h"
#include "GL.h"

#include "Pulsarion/UI/Window.h"

#include "Pulsarion/Core/GraphicalObject.h"
#include "Pulsarion/Core/Backend/MeshBackend.h"
#include "Pulsarion/Core/ShaderManager.h"
#include "Pulsarion/Core/TextureManager.h"
#include "Pulsarion/Core/Camera.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Pulsarion::OpenGL
{
    std::uint64_t GLRenderer::m_RenderableId = 0;

    GLRenderer::GLRenderer() : m_2DProjection(glm::identity<glm::mat4>()), m_RenderInfo(), m_2DRenderables()
    {

    }

    GLRenderer::~GLRenderer()
    {

    }

    void GLRenderer::Clear()
    {
        GL::Clear(ClearTarget::ColorAndDepthBufferBit);
    }

    void GLRenderer::SetClearColor(glm::vec4 color)
    {
        GL::ClearColor(color.r, color.g, color.b, color.a);
    }

    void GLRenderer::RenderUIWindow(const UI::Window& window)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GLRenderer::SetBlend(bool blend)
    {
        if (blend)
        {
            GL::Enable(EnableTarget::Blend);
            GL::BlendFunc(BlendFactor::SourceAlpha, BlendFactor::OneMinusSourceAlpha);
        }
        else
        {
            GL::Disable(EnableTarget::Blend);
        }
    }

    void GLRenderer::SetWireframeMode(bool wireframe)
    {
        if (wireframe)
        {
            GL::SetPolygonMode(PolygonFace::FrontAndBack, PolygonMode::Line);
        }
        else
        {
            GL::SetPolygonMode(PolygonFace::FrontAndBack, PolygonMode::Fill);
        }
    }

    std::uint64_t GLRenderer::Add2DRenderable(std::shared_ptr<GraphicalObject2D> object)
    {
        m_2DRenderables[m_RenderableId] = object;
        return m_RenderableId++;
    }

    std::shared_ptr<GraphicalObject2D> GLRenderer::Remove2DRenderable(std::uint64_t id)
    {
        auto it = m_2DRenderables.find(id);
        if (it != m_2DRenderables.end())
        {
            auto renderable = it->second;
            m_2DRenderables.erase(it);
            return renderable;
        }
        return nullptr;
    }

    void GLRenderer::Render(const Camera& camera)
    {
        m_RenderInfo.Clear();
        auto startTime = std::chrono::high_resolution_clock::now();

        for (auto& renderable : m_2DRenderables)
        {
            auto shader = ShaderManager::GetShader(renderable.second->GetShaderSignature());
            shader->Bind();
            shader->SetUniform("u_ProjectionMatrix", m_2DProjection);
            shader->SetUniform("u_ViewMatrix", camera.Get2DViewMatrix());
            shader->SetUniform("u_ModelMatrix", renderable.second->GetTransform().GetAsMatrix());
            shader->SetUniform("u_Texture2D", 0);
            shader->SetUniform("u_DiffuseColor", renderable.second->GetMaterial()->GetDiffuseColor());
            TextureManager::Bind2DTexture(renderable.second->GetMaterial()->GetTextureId(), 0);
            renderable.second->GetMesh()->GetBackend().Bind();

            GL::DrawElements(DrawMode::Triangles, renderable.second->GetMesh()->GetIndices().size(), Type::UnsignedInt, nullptr);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        m_RenderInfo.TimeMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    }

    const RenderInfo& GLRenderer::GetRenderInfo() const
    {
        return m_RenderInfo;
    }

    void GLRenderer::Set2DProjection(const glm::mat4 &projection)
    {
        m_2DProjection = projection;
    }

    const glm::mat4 &GLRenderer::Get2DProjection() const
    {
        return m_2DProjection;
    }
}

namespace Pulsarion
{
    std::unique_ptr<Renderer> CreateRenderer()
    {
        return std::make_unique<OpenGL::GLRenderer>();
    }
}
