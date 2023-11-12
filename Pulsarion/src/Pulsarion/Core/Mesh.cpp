#include "Pulsarionpch.h"
#include "Mesh.h"
#include "Pulsarion/Core/Backend/MeshBackend.h"

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

    void Mesh2D::SetIndices(const std::vector<std::uint32_t>& indices)
    {
        m_Indices = indices;
    }

    bool Mesh2D::CreateBackend()
    {
        if (m_Backend)
            return false;

        m_Backend = CreateMeshBackend2D();
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
}
