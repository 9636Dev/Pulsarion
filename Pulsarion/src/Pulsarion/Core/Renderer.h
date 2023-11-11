#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include <glm/vec4.hpp>

#include <memory>

namespace Pulsarion
{
    namespace UI
    {
        class Window;
    }

    class PULSARION_API Renderer
    {
    public:
        virtual ~Renderer() = default;

        virtual void SetBlend(bool blend) = 0;
        virtual void Clear() = 0;
        virtual void SetClearColor(glm::vec4 color) = 0;

        virtual void RenderUIWindow(const UI::Window& window) = 0;
    };

    extern PULSARION_API std::unique_ptr<Renderer> CreateRenderer();
}
