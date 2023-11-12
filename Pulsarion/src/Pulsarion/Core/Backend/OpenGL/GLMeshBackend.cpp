#include "Pulsarionpch.h"
#include "GLMeshBackend.h"

#include "Pulsarion/Core/Util/Vertex.h"

namespace Pulsarion::OpenGL
{
    GLMeshBackend2D::GLMeshBackend2D() : m_VertexArray(), m_VertexBuffer(), m_Layout(), m_IndexBuffer()
    {

    }

    GLMeshBackend2D::~GLMeshBackend2D()
    {

    }

    void GLMeshBackend2D::SetVertexData(const VertexData2D& vertexData)
    {
        m_Layout.Clear();
        if (const VertexData2DPacked* packed = dynamic_cast<const VertexData2DPacked*>(&vertexData))
        {
            std::uint32_t verticesSize = static_cast<uint32_t>(packed->GetVertices().size() * sizeof(float));
            std::uint32_t textureCoordinatesSize = static_cast<uint32_t>(packed->GetTextureCoordinates().size() * sizeof(float));
            m_VertexBuffer.SetData(nullptr, verticesSize + textureCoordinatesSize);
            m_VertexBuffer.SetSubData(packed->GetVertices().data(), verticesSize, 0);
            m_Layout.Push<float>(2, false, false, 0, 0);
            m_VertexBuffer.SetSubData(packed->GetTextureCoordinates().data(), textureCoordinatesSize, verticesSize);
            m_Layout.Push<float>(2, false, false, 0, verticesSize);
        }
        else
        {
            PLS_LOG_ERROR("Unsupported vertex data type!");
        }
        m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);
    }

    void GLMeshBackend2D::SetIndices(const std::vector<std::uint32_t>& indices)
    {
        m_IndexBuffer.SetData(indices.data(), static_cast<std::uint32_t>(indices.size() * sizeof(std::uint32_t)));
    }

    void GLMeshBackend2D::Bind() const
    {
        m_VertexArray.Bind();
        m_IndexBuffer.Bind();
    }

    void GLMeshBackend2D::Unbind() const
    {
        m_VertexArray.Unbind();
        m_IndexBuffer.Unbind();
    }
}

namespace Pulsarion
{
    std::unique_ptr<MeshBackend2D> CreateMeshBackend2D()
    {
        return std::make_unique<OpenGL::GLMeshBackend2D>();
    }
}
