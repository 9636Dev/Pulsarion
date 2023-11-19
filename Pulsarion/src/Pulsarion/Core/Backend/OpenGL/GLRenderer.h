#pragma once
#include "Pulsarion/Core/Renderer.h"

#include "Pulsarion/Core/Mesh.h"
#include "Pulsarion/Core/Shader.h"
#include "Pulsarion/Core/Material.h"

#include "UniformBuffer.h"

#include <unordered_map>
#include <memory>

namespace Pulsarion::OpenGL
{
    template <typename T>
    struct ConfigValue
    {
        T Value;
        std::uint64_t FastestRenderTime;
    };

    struct InternalConfig
    {
        ConfigValue<std::size_t> MaterialOptimizationThreshold = {10, 0};
    };

    struct Material2DData
    {
        std::shared_ptr<UniformBuffer> UniformBuffer;
        std::vector<std::shared_ptr<GraphicalObject2D>> Renderables;
    };

    struct Mesh2DData
    {
        std::shared_ptr<Mesh2D> Mesh;
        Shading::ShaderSignature OptimizedShaderSignature;
        bool IsMaterialOptimized;
        std::shared_ptr<Shader> Shader;
        std::unordered_map<std::shared_ptr<Material>, Material2DData> Materials;
        std::unordered_map<std::uint32_t, std::uint32_t> TextureUnitMap;

        Mesh2DData(std::shared_ptr<Mesh2D> mesh) : Mesh(mesh), OptimizedShaderSignature(Shading::ShaderSignature()), IsMaterialOptimized(false), Shader(nullptr), Materials(), TextureUnitMap()
        {

        }

        Mesh2DData() : Mesh2DData(nullptr)
        {

        }
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
        void Add2DRenderable(std::shared_ptr<GraphicalObject2D> renderable) override;
        bool Remove2DRenderable(std::shared_ptr<GraphicalObject2D> renderable) override;

        void Render(const Camera& camera) override;
        const RenderInfo& GetRenderInfo() const override;

        void Set2DProjection(const glm::mat4& projection) override;
        const glm::mat4& Get2DProjection() const override;
    private:
        InternalConfig m_Config;
        RenderInfo m_RenderInfo;
        std::unordered_map<std::shared_ptr<Mesh2D>, Mesh2DData> m_2DRenderables;
        glm::mat4 m_2DProjection;
    };
}
