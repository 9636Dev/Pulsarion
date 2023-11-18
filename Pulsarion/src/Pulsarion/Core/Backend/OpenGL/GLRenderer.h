#pragma once
#include "Pulsarion/Core/Renderer.h"

#include "Pulsarion/Core/Mesh.h"
#include "Pulsarion/Core/Shader.h"

#include "UniformBuffer.h"

#include <unordered_map>
#include <memory>

namespace Pulsarion::OpenGL
{
    struct Mesh2DData
    {

    };

    struct ShaderSignatureData
    {

    };

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
        const RenderInfo& GetRenderInfo() const override;

        void Set2DProjection(const glm::mat4& projection) override;
        const glm::mat4& Get2DProjection() const override;
    private:
        inline std::uint64_t NextRenderableId() { return m_RenderableId++; }

        RenderInfo m_RenderInfo;
        std::unordered_map<ShaderSignature, std::vector<std::uint64_t>> m_2DShaderSignatures;
        std::unordered_map<std::uint64_t, std::shared_ptr<GraphicalObject2D>> m_2DRenderables;
        static std::uint64_t m_RenderableId;
        glm::mat4 m_2DProjection;
        UniformBuffer m_2DUniformBuffer;
    };
}
