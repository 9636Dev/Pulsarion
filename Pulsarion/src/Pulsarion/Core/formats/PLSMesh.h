#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Core/Mesh.h"
#include "Pulsarion/Util/File.h"

#include <memory>
#include <utility>
#include <vector>
#include <string>

namespace Pulsarion
{
    struct PLSMeshHeader {
        std::uint32_t Signature;
        std::uint32_t Version;
        std::uint64_t DataTypeBitmap;
        std::uint8_t IndexType;
        std::uint32_t VertexCount;
        std::uint32_t IndexCount;
        std::uint8_t Dimensions;
        std::uint8_t TextureType;
    };

    struct PULSARION_API MeshParseResult
    {

    };

    struct PULSARION_API MeshReadResult
    {

    };

    struct PULSARION_API MeshWriteResult
    {

    };

    struct PLSMeshData2D {

    };

    class PLSMesh {
    public:
        static MeshParseResult Parse(const File& file);
        static MeshWriteResult Write(File& file, const Mesh2D& mesh);
        static MeshWriteResult Write(File& file, const Mesh3D& mesh);
    private:
        static MeshWriteResult WriteData(File& file, const PLSMeshHeader& header, const PLSMeshData2D& data);
        static MeshReadResult ReadData(const File& file, PLSMeshHeader& header, PLSMeshData2D& data);

        static std::size_t GetBytesPerVertex(const PLSMeshHeader& header);
        static std::size_t GetBytesPerIndex(const PLSMeshHeader& header);
    };
}
