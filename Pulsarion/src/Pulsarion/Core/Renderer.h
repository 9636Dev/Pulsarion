#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include "Camera.h"

#include <glm/vec4.hpp>
#include <memory>


namespace Pulsarion
{
    namespace UI
    {
        class Window;
    }

    class GraphicalObject2D;

    class PULSARION_API Renderer
    {
    public:
        virtual ~Renderer() = default;

        virtual void SetWireframeMode(bool wireframe) = 0;
        virtual void SetBlend(bool blend) = 0;
        virtual void Clear() = 0;
        virtual void SetClearColor(glm::vec4 color) = 0;

        virtual void RenderUIWindow(const UI::Window& window) = 0;
        virtual std::uint64_t Add2DRenderable(std::shared_ptr<GraphicalObject2D> renderable) = 0;
        virtual std::shared_ptr<GraphicalObject2D> Remove2DRenderable(std::uint64_t id) = 0;

        virtual void Render(const Camera& camera) = 0;
    };

    extern PULSARION_API std::unique_ptr<Renderer> CreateRenderer();
}
