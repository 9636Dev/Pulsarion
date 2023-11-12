#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Core/Util/Vertex.h"
#include "Pulsarion/Util/Modifiable.h"
#include "Pulsarion/Util/UsageType.h"

#include <memory>
#include <vector>

namespace Pulsarion
{
    class MeshBackend2D;

    class Mesh2D
    {
    public:
        Mesh2D(UsageType type, VertexDataType vertexType = VertexDataType::TightlyPacked);
        ~Mesh2D();

        const VertexData2D& GetVertexData() const;
        void SetIndices(const std::vector<std::uint32_t>& indices);

        bool CreateBackend();
        void DestroyBackend();
        bool IsBackendCreated() const;
        const MeshBackend2D& GetBackend() const;
    private:
        UsageType m_UsageType;
        std::unique_ptr<VertexData2D> m_VertexData;
        std::vector<std::uint32_t> m_Indices; // TODO: Allow user specified indices type
        std::unique_ptr<MeshBackend2D> m_Backend;
    };
}
