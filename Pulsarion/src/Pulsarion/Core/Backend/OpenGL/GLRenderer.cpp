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

    GLRenderer::GLRenderer() : m_2DRenderables(), m_2DShaderSignatures(), m_2DProjection(glm::identity<glm::mat4>()), m_RenderInfo(), m_2DUniformBuffer()
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
        m_2DRenderables.emplace(m_RenderableId, object);
        auto it = m_2DShaderSignatures.find(object->GetShaderSignature());
        if (it != m_2DShaderSignatures.end())
        {
            // Try to find a object with the same mesh
            std::int64_t index = -1;
            for (std::int64_t i = static_cast<std::int64_t>(it->second.size()) - 1; i >= 0; --i)
            {
                auto& renderable = m_2DRenderables[it->second[i]];
                if (renderable->GetMesh() == object->GetMesh())
                {
                    index = i;
                    break;
                }
            }

            if (index == -1)
            {
                it->second.push_back(m_RenderableId);
            }
            else
            {
                // Add after the last renderable with the same mesh
                it->second.insert(it->second.begin() + index + 1, m_RenderableId);
            }
        }
        else
        {
            m_2DShaderSignatures.emplace(object->GetShaderSignature(), std::vector<std::uint64_t>{ m_RenderableId });
        }
        return m_RenderableId++;
    }

    std::shared_ptr<GraphicalObject2D> GLRenderer::Remove2DRenderable(std::uint64_t id)
    {
        auto it = m_2DRenderables.find(id);
        if (it != m_2DRenderables.end())
        {
            auto object = it->second;
            m_2DRenderables.erase(it);

            auto shaderIt = m_2DShaderSignatures.find(object->GetShaderSignature());
            if (shaderIt != m_2DShaderSignatures.end())
            {
                auto& renderables = shaderIt->second;
                auto renderableIt = std::find(renderables.begin(), renderables.end(), id);
                if (renderableIt != renderables.end())
                {
                    renderables.erase(renderableIt);
                }
            }

            return object;
        }
        return nullptr;
    }

    void GLRenderer::Render(const Camera& camera)
    {
        m_RenderInfo.Clear();
        auto startTime = std::chrono::high_resolution_clock::now();

        std::shared_ptr<Shader> shader;
        std::shared_ptr<Mesh2D> mesh;
        std::shared_ptr<Material> material;
        std::uint32_t textureId = 0;

        for (const auto& [signature, renderables] : m_2DShaderSignatures)
        {
            shader = ShaderManager::GetShader(signature);
            shader->Bind();
            shader->SetUniform("u_ViewMatrix", camera.Get2DViewMatrix());
            shader->SetUniform("u_ProjectionMatrix", m_2DProjection);

            for (auto& renderable : renderables)
            {
                auto& object = m_2DRenderables[renderable];
                // Mesh should be sorted to avoid unnecessary binding
                if (mesh != object->GetMesh())
                {
                    mesh = object->GetMesh();
                    mesh->GetBackend().Bind();
                }

                // Material is not sorted, so it must be bound every time
                material = object->GetMaterial();

                shader->SetUniform("u_ModelMatrix", object->GetTransform().GetAsMatrix());
                shader->SetUniform("u_DiffuseColor", material->GetDiffuseColor());
                if (material->GetTextureId() != 0 && material->GetTextureId() != textureId)
                {
                    TextureManager::Bind2DTexture(material->GetTextureId(), 0);
                    shader->SetUniform("u_Texture2D", 0);
                    textureId = material->GetTextureId();
                }

                GL::DrawElements(DrawMode::Triangles, static_cast<sizei_t>(mesh->GetIndices().size()), Type::UnsignedInt, nullptr);
            }
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
