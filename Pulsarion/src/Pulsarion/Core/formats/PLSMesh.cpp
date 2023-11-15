#include "Pulsarionpch.h"
#include "PLSMesh.h"

// =========================
// File Format
// =========================
// Header
// Signature: 4 bytes (PLSM ascii)
// Version: 4 bytes (uint32_t)
// Data Type Bitmap: 8 bytes (uint64_t, 2 bits per data type [1 bit for enabled, 1 bit for double precision])
// Index Type: 1 byte (uint8_t [0 = uint8_t, 1 = uint16_t, 2 = uint32_t, 3 = uint64_t])
// Vertex Count: 4 bytes (uint32_t)
// Index Count: 4 bytes (uint32_t)
// Dimensions: 1 byte (uint8_t [0 = 2D, 1 = 3D])
// Texture Type: 1 byte (uint8_t [0 = None, 1 = 1D, 2 = 2D, 3 = 3D, 4 = Cube])
// =========================
// Data
// Vertex Data: Dimension * vertex count * vertex data type size (float, double)
// Index Data: index count * index type size (uint8_t, uint16_t, uint32_t, uint64_t)
// Contains Texture Coordinates: 1 byte (uint8_t [0 = false, 1 = true])
// Texture Coordinates: vertex count * TextureType * vertex data type size (float, double)
// Normals: vertex count * Dimension * vertex data type size (float, double)
// Tangents: vertex count * Dimension * vertex data type size (float, double)
// =========================
// Footer
// CRC32: 4 bytes (uint32_t)
// EOF: 1 byte (uint8_t)
// =========================


namespace Pulsarion
{
    MeshWriteResult PLSMesh::WriteData(File& file, const PLSMeshHeader& header, const PLSMeshData2D& data)
    {
        // Open in binary write mode with all error checking enabled
        std::ofstream stream(file.GetAbsolutePath(), std::ios::binary | std::ios::out);
        stream.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);

        try
        {
            // Write header, manually write each field to prevent padding
            stream.write(reinterpret_cast<const char*>(&header.Signature), sizeof(header.Signature));
            stream.write(reinterpret_cast<const char*>(&header.Version), sizeof(header.Version));
            stream.write(reinterpret_cast<const char*>(&header.DataTypeBitmap), sizeof(header.DataTypeBitmap));
            stream.write(reinterpret_cast<const char*>(&header.IndexType), sizeof(header.IndexType));
            stream.write(reinterpret_cast<const char*>(&header.VertexCount), sizeof(header.VertexCount));
            stream.write(reinterpret_cast<const char*>(&header.IndexCount), sizeof(header.IndexCount));
            stream.write(reinterpret_cast<const char*>(&header.Dimensions), sizeof(header.Dimensions));
            stream.write(reinterpret_cast<const char*>(&header.TextureType), sizeof(header.TextureType));

            std::size_t vertexDataSize = header.VertexCount * header.Dimensions * (header.DataTypeBitmap & 0x1 ? sizeof(double) : sizeof(float));
            std::size_t bytesPerIndex = 0;
            switch (header.IndexType)
            {
                case 0:
                    bytesPerIndex = sizeof(std::uint8_t);
                    break;
                case 1:
                    bytesPerIndex = sizeof(std::uint16_t);
                    break;
                case 2:
                    bytesPerIndex = sizeof(std::uint32_t);
                    break;
                case 3:
                    bytesPerIndex = sizeof(std::uint64_t);
                    break;
                default:
                    PLS_LOG_WARN("Invalid index type: {0}", header.IndexType);
            }
            std::size_t indexDataSize = header.IndexCount * header.Dimensions * bytesPerIndex;
            std::size_t otherDataSize = 0;


            // Write vertex data, while generating CRC32
            std::vector<char> dataBuffer;
            dataBuffer.reserve(vertexDataSize + indexDataSize);

        }
        catch (const std::ifstream::failure& e)
        {
            PLS_LOG_WARN("Failed to write mesh data to file: {0}", e.what());
        }
    }

    std::size_t PLSMesh::GetBytesPerVertex(const PLSMeshHeader& header)
    {
        return header.DataTypeBitmap & 0x1 ? sizeof(double) : sizeof(float);
    }

    std::size_t PLSMesh::GetBytesPerIndex(const PLSMeshHeader& header)
    {
        switch (header.IndexType)
        {
            case 0:
                return sizeof(std::uint8_t);
            case 1:
                return sizeof(std::uint16_t);
            case 2:
                return sizeof(std::uint32_t);
            case 3:
                return sizeof(std::uint64_t);
            default:
                PLS_LOG_WARN("Invalid index type: {0}", header.IndexType);
        }
    }
}
