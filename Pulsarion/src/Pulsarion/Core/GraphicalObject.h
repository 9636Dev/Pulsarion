#pragma once

#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"

#include <memory>

namespace Pulsarion
{
    namespace OpenGL
    {
        class GLRenderer;
    }
    class Renderer;

    class PULSARION_API GraphicalObject2D
    {
    public:
        friend class Renderer;
        friend class OpenGL::GLRenderer;
        struct RenderOptions
        {
            bool Wireframe = false;
            bool BackFaceCull = true;
            bool FrustumCull = true;

            RenderOptions() : Wireframe(false), BackFaceCull(true), FrustumCull(true) {}
        };
        GraphicalObject2D(std::shared_ptr<Material> material, std::shared_ptr<Mesh2D> mesh);
        ~GraphicalObject2D();

        void SetMaterial(std::shared_ptr<Material> material);
        void SetMesh(std::shared_ptr<Mesh2D> mesh);
        void SetTransform(const Transform2D& transform);
        void SetRenderOptions(const RenderOptions& renderOptions);

        std::shared_ptr<Material> GetMaterial() const;
        std::shared_ptr<Mesh2D> GetMesh() const;
        const Transform2D& GetTransform() const;
        const RenderOptions& GetRenderOptions() const;
        const ShaderSignature& GetShaderSignature() const;
        std::shared_ptr<Shader> GetCachedShader() const;

        Transform2D& GetTransformRef();

        bool IsChanged() const;
    private:
        std::shared_ptr<Material> m_Material;
        std::shared_ptr<Mesh2D> m_Mesh;
        std::shared_ptr<Shader> m_CachedShader;
        ShaderSignature m_ShaderSignature;
        Transform2D m_Transform;
        RenderOptions m_RenderOptions;
        bool m_IsChanged;
    };
}
