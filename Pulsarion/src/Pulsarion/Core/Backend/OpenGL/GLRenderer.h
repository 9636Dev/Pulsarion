#pragma once

#include "Pulsarion/Core/Renderer.h"

#include <unordered_map>

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
        void SetWireframeMode(bool wireframe) override;

        void RenderUIWindow(const UI::Window& window) override;
        std::uint64_t Add2DRenderable(GraphicalObject2D&& renderable);
        std::optional<GraphicalObject2D> Remove2DRenderable(std::uint64_t id);

        void Render() override;
    private:
        inline std::uint64_t NextRenderableId() { return m_RenderableId++; }

        std::unordered_map<std::uint64_t, GraphicalObject2D> m_2DRenderables;
        static std::uint64_t m_RenderableId;
    };
}
