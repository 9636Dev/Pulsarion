#include "Pulsarionpch.h"
#include "Vertex.h"

namespace Pulsarion
{
    VertexData2DPacked::VertexData2DPacked()
         : m_Vertices(), m_TextureCoordinates(), m_VertexCount(0)
    {

    }

    VertexData2DPacked::~VertexData2DPacked()
    {

    }

    void VertexData2DPacked::SetVertices(const std::vector<double>& vertices)
    {
        PLS_CORE_ASSERT(vertices.size() % 2 == 0, "Vertex data must be a multiple of 2");
        PLS_CORE_ASSERT(vertices.size() != 0, "Vertex data must not be empty");
        PLS_CORE_ASSERT(vertices.size() / 2 == m_VertexCount, "Vertex count must be set before setting vertices");
        std::copy(vertices.begin(), vertices.end(), m_Vertices.begin());
    }

    void VertexData2DPacked::SetTextureCoordinates(const std::vector<float>& textureCoordinates)
    {
        PLS_CORE_ASSERT(textureCoordinates.size() % 2 == 0, "Texture coordinate data must be a multiple of 2");
        PLS_CORE_ASSERT(textureCoordinates.size() != 0, "Texture coordinate data must not be empty");
        PLS_CORE_ASSERT(textureCoordinates.size() / 2 == m_VertexCount, "Vertex count must be set before setting texture coordinates");
        std::copy(textureCoordinates.begin(), textureCoordinates.end(), m_TextureCoordinates.begin());
    }

    std::vector<double> VertexData2DPacked::GetVertices() const
    {
        return m_Vertices;
    }

    std::vector<float> VertexData2DPacked::GetTextureCoordinates() const
    {
        return m_TextureCoordinates;
    }

    void VertexData2DPacked::SetVertexCount(std::size_t count)
    {
        m_VertexCount = count;
        m_Vertices.resize(count * 2);
        m_TextureCoordinates.resize(count * 2);
    }

    std::size_t VertexData2DPacked::GetVertexCount() const
    {
        return m_VertexCount;
    }

    VertexData2DInterleaved::VertexData2DInterleaved()
        : m_Data()
    {

    }

    VertexData2DInterleaved::~VertexData2DInterleaved()
    {

    }

    void VertexData2DInterleaved::SetVertices(const std::vector<double>& vertices)
    {
        PLS_CORE_ASSERT(vertices.size() % 2 == 0, "Vertex data must be a multiple of 2");
        PLS_CORE_ASSERT(vertices.size() != 0, "Vertex data must not be empty");
        PLS_CORE_ASSERT(vertices.size() / 2 == m_Data.size(), "Vertex count must be set before setting vertices");

        for (std::size_t i = 0; i < vertices.size() / 2; i++)
        {
            m_Data[i].Vertex[0] = vertices[i * 2];
            m_Data[i].Vertex[1] = vertices[i * 2 + 1];
        }
    }

    std::vector<double> VertexData2DInterleaved::GetVertices() const
    {
        std::vector<double> vertices(m_Data.size() * 2);
        for (std::size_t i = 0; i < m_Data.size(); i++)
        {
            vertices[i * 2] = m_Data[i].Vertex[0];
            vertices[i * 2 + 1] = m_Data[i].Vertex[1];
        }
        return vertices;
    }

    void VertexData2DInterleaved::SetTextureCoordinates(const std::vector<float>& textureCoordinates)
    {
        PLS_CORE_ASSERT(textureCoordinates.size() % 2 == 0, "Texture coordinate data must be a multiple of 2");
        PLS_CORE_ASSERT(textureCoordinates.size() != 0, "Texture coordinate data must not be empty");
        PLS_CORE_ASSERT(textureCoordinates.size() / 2 == m_Data.size(), "Vertex count must be set before setting texture coordinates");

        for (std::size_t i = 0; i < textureCoordinates.size() / 2; i++)
        {
            m_Data[i].TextureCoordinate[0] = textureCoordinates[i * 2];
            m_Data[i].TextureCoordinate[1] = textureCoordinates[i * 2 + 1];
        }
    }

    std::vector<float> VertexData2DInterleaved::GetTextureCoordinates() const
    {
        std::vector<float> textureCoordinates(m_Data.size() * 2);
        for (std::size_t i = 0; i < m_Data.size(); i++)
        {
            textureCoordinates[i * 2] = m_Data[i].TextureCoordinate[0];
            textureCoordinates[i * 2 + 1] = m_Data[i].TextureCoordinate[1];
        }
        return textureCoordinates;
    }

    const std::vector<Vertex2DInterleaved>& VertexData2DInterleaved::GetInterleaved() const
    {
        return m_Data;
    }

    void VertexData2DInterleaved::SetVertexCount(std::size_t count)
    {
        if (count > m_Data.size())
        {
            m_Data.reserve(count);
            for (std::size_t i = m_Data.size(); i < count; i++)
            {
                m_Data.emplace_back();
            }
        }
        m_Data.resize(count);
    }

    std::size_t VertexData2DInterleaved::GetVertexCount() const
    {
        return m_Data.size();
    }

    std::unique_ptr<VertexData2D> CreateVertexData2D(VertexDataType type)
    {
        switch (type)
        {
        case VertexDataType::TightlyPacked:
            return std::make_unique<VertexData2DPacked>();
        case VertexDataType::Interleaved:
            return std::make_unique<VertexData2DInterleaved>();
        default:
            PLS_LOG_ERROR("Unknown vertex data type");
            return nullptr;
        }
    }
}
