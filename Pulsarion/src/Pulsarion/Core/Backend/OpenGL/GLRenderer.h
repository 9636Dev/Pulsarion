#pragma once

#include "Pulsarion/Core/Renderer.h"

namespace Pulsarion::OpenGL
{
    class GLRenderer : public Renderer
    {
    public:
        GLRenderer();
        ~GLRenderer();

        void Clear() override;
        void SetClearColor(glm::vec4 color) override;
        void SetBlend(bool blend) override;

        void RenderUIWindow(const UI::Window& window) override;
    };
}
