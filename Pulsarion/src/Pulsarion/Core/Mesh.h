#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Core/Util/Vertex.h"
#include "Pulsarion/Util/Modifiable.h"
#include "Pulsarion/Util/UsageType.h"

#include <memory>
#include <vector>

namespace Pulsarion
{
    namespace Shading
    {
        struct ShaderSignature;
    }
    class MeshBackend2D;
    class Renderer;

    class PULSARION_API Mesh2D
    {
    public:
        friend class Renderer;
        Mesh2D(UsageType type, VertexDataType vertexType = VertexDataType::TightlyPacked);
        ~Mesh2D();

        const VertexData2D& GetVertexData() const;
        VertexData2D& GetVertexDataRef();
        const std::vector<std::uint32_t>& GetIndices() const;
        void SetIndices(const std::vector<std::uint32_t>& indices);
        std::vector<float> GetVertices() const;
        void SetVertices(const std::vector<float>& vertices);
        void SetTextureCoordinates(const std::vector<float>& textureCoordinates);
        void SetVertexCount(std::size_t count);

        bool CreateBackend();
        void DestroyBackend();
        bool IsBackendCreated() const;
        const MeshBackend2D& GetBackend() const;
        Shading::ShaderSignature GetShaderSignature() const;
    private:
        UsageType m_UsageType;
        std::unique_ptr<VertexData2D> m_VertexData;
        std::vector<std::uint32_t> m_Indices; // TODO: Allow user specified indices type
        std::unique_ptr<MeshBackend2D> m_Backend;
    };

    class PULSARION_API Mesh3D
    {
    };
}
