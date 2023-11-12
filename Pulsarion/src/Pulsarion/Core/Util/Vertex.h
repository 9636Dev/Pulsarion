#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Util/Concepts.h"

#include <memory>
#include <vector>

namespace Pulsarion
{
    enum class PULSARION_API VertexDataType
    {
        TightlyPacked,
        Interleaved
    };

    // TODO: Bone weights and indices in the future
    class PULSARION_API VertexData2D
    {
    public:
        virtual ~VertexData2D() = default;

        /// <summary>
        /// Copies the vertices into the vertex data, size should be a multiple of 2 and equal to vertexCount * 2.
        /// </summary>
        /// <param name="vertices">A vector containing data for the vertex positions.</param>
        virtual void SetVertices(const std::vector<double>& vertices) = 0;
        virtual void SetTextureCoordinates(const std::vector<float>& textureCoordinates) = 0;

        /// <summary>
        /// Will either allocate space for the vertices or shrink the vector to the specified size
        /// </summary>
        /// <param name="count">The current count of the vertices</param>
        virtual void SetVertexCount(std::size_t count) = 0;
        virtual std::size_t GetVertexCount() const = 0;

        virtual std::vector<double> GetVertices() const = 0;
        virtual std::vector<float> GetTextureCoordinates() const = 0;
    };

    class PULSARION_API VertexData3D
    {
    public:
        virtual ~VertexData3D() = default;
        virtual void SetVertices(const std::vector<double>& vertices) = 0;
        virtual void SetTextureCoordinates(const std::vector<float>& textureCoordinates) = 0;
        virtual void SetNormals(const std::vector<double>& normals) = 0;
        virtual void SetBiTangents(const std::vector<double>& biTangents) = 0;

        virtual std::vector<double> GetVertices() const = 0;
        virtual std::vector<float> GetTextureCoordinates() const = 0;
        virtual std::vector<double> GetNormals() const = 0;
        virtual std::vector<double> GetBiTangents() const = 0;
    };

    struct PULSARION_API Vertex2DInterleaved
    {
        double Vertex[2];
        float TextureCoordinate[2];

        Vertex2DInterleaved(double x, double y, float u, float v)
            : Vertex{ x, y }, TextureCoordinate{ u, v }
        {

        }
        Vertex2DInterleaved() : Vertex2DInterleaved(0.0, 0.0, 0.0f, 0.0f) { }
    };

    class VertexData2DPacked : public VertexData2D
    {
    public:
        VertexData2DPacked();
        ~VertexData2DPacked();

        void SetVertices(const std::vector<double>& vertices) override;
        void SetTextureCoordinates(const std::vector<float>& textureCoordinates) override;

        std::vector<double> GetVertices() const override;
        std::vector<float> GetTextureCoordinates() const override;

        void SetVertexCount(std::size_t count) override;
        std::size_t GetVertexCount() const override;
    private:
        std::vector<double> m_Vertices;
        std::vector<float> m_TextureCoordinates;
        std::size_t m_VertexCount;
    };

    class VertexData2DInterleaved : public VertexData2D
    {
    public:
        VertexData2DInterleaved();
        ~VertexData2DInterleaved();

        void SetVertices(const std::vector<double>& vertices) override;
        void SetTextureCoordinates(const std::vector<float>& textureCoordinates) override;
        void AddVertices(const std::vector<double>& vertices, std::size_t offset = 0);
        void AddTextureCoordinates(const std::vector<float>& textureCoordinates, std::size_t offset = 0);

        std::vector<double> GetVertices() const override;
        std::vector<float> GetTextureCoordinates() const override;

        void SetVertexCount(std::size_t count) override;
        std::size_t GetVertexCount() const override;

        const std::vector<Vertex2DInterleaved>& GetInterleaved() const;
    private:
        std::vector<Vertex2DInterleaved> m_Data;
    };

    std::unique_ptr<VertexData2D> CreateVertexData2D(VertexDataType type);
}
