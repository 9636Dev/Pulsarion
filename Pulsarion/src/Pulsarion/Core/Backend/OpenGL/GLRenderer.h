#pragma once
#include "Pulsarion/Core/Renderer.h"

#include "Pulsarion/Core/Mesh.h"

#include <unordered_map>
#include <memory>

namespace Pulsarion::OpenGL
{
    class GLRenderer : public Renderer
    {
    public:
        GLRenderer();
        ~GLRenderer() override;

        void Clear() override;
        void SetClearColor(glm::vec4 color) override;
        void SetBlend(bool blend) override;
        void SetWireframeMode(bool wireframe) override;

        void RenderUIWindow(const UI::Window& window) override;
        std::uint64_t Add2DRenderable(std::shared_ptr<GraphicalObject2D> renderable) override;
        std::shared_ptr<GraphicalObject2D> Remove2DRenderable(std::uint64_t id) override;

        void Render(const Camera& camera) override;

        void Set2DProjection(const glm::mat4& projection) override;
        const glm::mat4& Get2DProjection() const override;
    private:
        inline std::uint64_t NextRenderableId() { return m_RenderableId++; }

        std::unordered_map<std::shared_ptr<Mesh2D>, std::vector<std::uint64_t>> m_2DRenderableMeshes;
        std::unordered_map<std::uint64_t, std::shared_ptr<GraphicalObject2D>> m_2DRenderables;
        static std::uint64_t m_RenderableId;
        glm::mat4 m_2DProjection;
    };
}
