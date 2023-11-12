#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

namespace Pulsarion
{
    class VertexData2D;

    class PULSARION_API MeshBackend2D
    {
    public:
        virtual ~MeshBackend2D() = default;

        virtual void SetVertexData(const VertexData2D& vertexData) = 0;
        virtual void SetIndices(const std::vector<std::uint32_t>& indices) = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };

    extern std::unique_ptr<MeshBackend2D> CreateMeshBackend2D();
}
