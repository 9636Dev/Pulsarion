#include "Pulsarionpch.h"
#include "Mesh.h"
#include "Pulsarion/Core/Backend/MeshBackend.h"

#include "Shader.h"

namespace Pulsarion
{
    Mesh2D::Mesh2D(UsageType type, VertexDataType vertexType) : m_VertexData(CreateVertexData2D(vertexType)), m_Backend(), m_UsageType(type)
    {
 
    }

    Mesh2D::~Mesh2D()
    {

    }

    const VertexData2D& Mesh2D::GetVertexData() const
    {
        return *m_VertexData;
    }

    VertexData2D& Mesh2D::GetVertexDataRef()
    {
        return *m_VertexData;
    }

    const std::vector<std::uint32_t>& Mesh2D::GetIndices() const
    {
        return m_Indices;
    }

    void Mesh2D::SetIndices(const std::vector<std::uint32_t>& indices)
    {
        m_Indices = indices;
    }

    std::vector<float> Mesh2D::GetVertices() const
    {
        return m_VertexData->GetVertices();
    }

    void Mesh2D::SetVertices(const std::vector<float>& vertices)
    {
        m_VertexData->SetVertices(vertices);
    }

    void Mesh2D::SetVertexCount(std::size_t count)
    {
        m_VertexData->SetVertexCount(count);
    }

    bool Mesh2D::CreateBackend()
    {
        if (m_Backend)
            return false;

        m_Backend = CreateMeshBackend2D();
        m_Backend->SetVertexData(*m_VertexData);
        m_Backend->SetIndices(m_Indices);
        return true;
    }

    void Mesh2D::DestroyBackend()
    {
        m_Backend.reset();
    }

    bool Mesh2D::IsBackendCreated() const
    {
        return m_Backend != nullptr;
    }

    const MeshBackend2D& Mesh2D::GetBackend() const
    {
        return *m_Backend;
    }

    ShaderSignature Mesh2D::GetShaderSignature() const
    {
        ShaderSignature signature;
        // TODO: Make dynamic
        signature.EnableInput(ShaderSignatureBit::Position2D);
        if (m_VertexData->GetTextureCoordinates().size() != 0) signature.EnableInput(ShaderSignatureBit::TexCoord2D);
        return signature;
    }
}
