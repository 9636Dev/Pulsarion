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
    struct PLSMeshHeader
    {
        std::uint32_t Signature = 0x4D534C50;
        std::uint32_t Version = 1;
        std::uint32_t VertexCount;
        std::uint32_t IndexCount;
        std::uint8_t Dimensions;
        std::uint8_t TextureType;
        std::uint32_t DataTypeBitmap;
    };

    struct PLSMeshData {
        std::vector<float> VertexData;
        std::vector<std::uint32_t> IndexData;
        std::vector<float> TexCoordData;
    };

    struct PLSMeshFooter
    {
        std::uint32_t Crc32;
        std::uint8_t Eof;
    };

    struct PULSARION_API MeshParseResult
    {
        bool Success = false;
        std::size_t BytesParsed = 0;
        std::uint64_t TimeTaken = 0;
        std::string Message = "";
        std::shared_ptr<Mesh2D> Mesh2D = nullptr;
        std::shared_ptr<Mesh3D> Mesh3D = nullptr;
    };

    struct PULSARION_API MeshReadResult
    {
        bool Success = false;
        std::size_t BytesRead = 0;
        std::uint64_t TimeTaken = 0;
        std::string Message = "";
    };

    struct PULSARION_API MeshWriteResult
    {
        bool Success = false;
        std::size_t BytesWritten = 0;
        std::uint64_t TimeTaken = 0;
        std::string Message = "";
    };

    class PULSARION_API PLSMesh {
    public:
        static MeshParseResult Parse(const File& file, UsageType usageType = UsageType::Static, VertexDataType meshType = VertexDataType::TightlyPacked);
        static MeshWriteResult Write(File& file, const Mesh2D& mesh);

        static MeshWriteResult WriteData(File& file, const PLSMeshHeader& header, const PLSMeshData& data);
        static MeshReadResult ReadData(const File& file, PLSMeshHeader& header, PLSMeshData& data);

        static std::size_t GetTexCoordDimensions(const PLSMeshHeader& header);
    };
}
