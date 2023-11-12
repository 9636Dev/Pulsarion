#include "Pulsarionpch.h"
#include "GLRenderer.h"

#include "Enum.h"
#include "GL.h"

#include "Pulsarion/UI/Window.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Pulsarion::OpenGL
{
    GLRenderer::GLRenderer() 
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
}

namespace Pulsarion
{
    std::unique_ptr<Renderer> CreateRenderer()
    {
        return std::make_unique<OpenGL::GLRenderer>();
    }
}
