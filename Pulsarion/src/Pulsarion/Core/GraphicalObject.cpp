#include "Pulsarionpch.h"
#include "GraphicalObject.h"

namespace Pulsarion
{
    GraphicalObject2D::GraphicalObject2D(std::shared_ptr<Material> material, std::shared_ptr<Mesh2D> mesh)
        : m_Material(material), m_Mesh(mesh), m_Transform(), m_RenderOptions(), m_IsChanged(true)
    {
        
    }

    GraphicalObject2D::~GraphicalObject2D()
    {

    }

    void GraphicalObject2D::SetMaterial(std::shared_ptr<Material> material)
    {
        m_Material = material;
        m_IsChanged = true;
    }

    void GraphicalObject2D::SetMesh(std::shared_ptr<Mesh2D> mesh)
    {
        m_Mesh = mesh;
        m_IsChanged = true;
    }

    void GraphicalObject2D::SetTransform(const Transform2D& transform)
    {
        m_Transform.GetTranslationRef() = transform.GetTranslation();
        m_Transform.GetScaleRef() = transform.GetScale();
        m_Transform.SetRotation(transform.GetRotation());
        m_IsChanged = true;
    }

    void GraphicalObject2D::SetRenderOptions(const RenderOptions& renderOptions)
    {
        m_RenderOptions = renderOptions;
        m_IsChanged = true;
    }

    std::shared_ptr<Material> GraphicalObject2D::GetMaterial() const
    {
        return m_Material;
    }

    std::shared_ptr<Mesh2D> GraphicalObject2D::GetMesh() const
    {
        return m_Mesh;
    }

    const Transform2D& GraphicalObject2D::GetTransform() const
    {
        return m_Transform;
    }

    const GraphicalObject2D::RenderOptions& GraphicalObject2D::GetRenderOptions() const
    {
        return m_RenderOptions;
    }

    bool GraphicalObject2D::IsChanged() const
    {
        return m_IsChanged;
    }

    Shading::ShaderSignature GraphicalObject2D::GetShaderSignature()
    {
        Shading::ShaderSignature signature;
        signature.AddVertexUniform(Shading::ShaderInputUniform::ViewMatrix);
        signature.AddVertexUniform(Shading::ShaderInputUniform::ProjectionMatrix);
        return signature;
    }

    Transform2D& GraphicalObject2D::GetTransformRef()
    {
        m_IsChanged = true;
        return m_Transform;
    }
}
