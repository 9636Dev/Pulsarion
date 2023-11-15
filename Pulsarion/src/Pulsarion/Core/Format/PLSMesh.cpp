#include "Pulsarionpch.h"
#include "PLSMesh.h"

#include "Pulsarion/Util/Checksum.h"

// =========================
// File Format
// =========================
// Header
// Signature: 4 bytes (PLSM ascii)
// Version: 4 bytes (uint32_t)
// Vertex Count: 4 bytes (uint32_t)
// Index Count: 4 bytes (uint32_t)
// Dimensions: 1 byte (uint8_t [0 = 2D, 1 = 3D])
// Texture Type: 1 byte (uint8_t [0 = None, 1 = 1D, 2 = 2D, 3 = 3D, 4 = Cube])
// Data Type Bitmap: 4 bytes (uint32_t [1 bit for each type of data present])
//      0: Texture Coordinates
//      1: Normals
//      2: Tangents
// =========================
// Data
// Index Data: index count * sizeof(uint32_t)
// Vertex Data: Dimension * vertex count * sizeof(float)
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
    MeshWriteResult PLSMesh::WriteData(File& file, const PLSMeshHeader& header, const PLSMeshData& data)
    {
        MeshWriteResult result;
        
        try
        {
            // Open in binary write mode with all error checking enabled
            std::ofstream stream(file.GetAbsolutePath(), std::ios::binary | std::ios::out);
            stream.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
            auto startTime = std::chrono::high_resolution_clock::now();

            // Write header, manually write each field to prevent padding
            stream.write(reinterpret_cast<const char*>(&header.Signature), sizeof(header.Signature));
            stream.write(reinterpret_cast<const char*>(&header.Version), sizeof(header.Version));
            stream.write(reinterpret_cast<const char*>(&header.VertexCount), sizeof(header.VertexCount));
            stream.write(reinterpret_cast<const char*>(&header.IndexCount), sizeof(header.IndexCount));
            stream.write(reinterpret_cast<const char*>(&header.Dimensions), sizeof(header.Dimensions));
            stream.write(reinterpret_cast<const char*>(&header.TextureType), sizeof(header.TextureType));
            stream.write(reinterpret_cast<const char*>(&header.DataTypeBitmap), sizeof(header.DataTypeBitmap));

            std::size_t bytesPerVertex = sizeof(float) * header.Dimensions;
            std::size_t bytesPerIndex = sizeof(std::uint32_t);
            std::size_t bytesPerTexCoord = sizeof(float) * GetTexCoordDimensions(header);

            std::size_t vertexDataSize = bytesPerVertex * header.VertexCount;
            std::size_t indexDataSize = bytesPerIndex * header.IndexCount;
            std::size_t texCoordDataSize = bytesPerTexCoord * header.VertexCount; // Will be 0 if bytesPerTexCoord is 0

            std::size_t dataBufferSize = indexDataSize + vertexDataSize + texCoordDataSize;
            std::vector<std::byte> dataBuffer(dataBufferSize);
            dataBuffer.resize(dataBufferSize);

            for (std::size_t i = 0; i < header.IndexCount; i++)
            {
                std::size_t offset = i * bytesPerIndex;
                std::memcpy(dataBuffer.data() + offset, &data.IndexData[i], sizeof(std::uint32_t));
            }

            for (std::size_t i = 0; i < header.VertexCount; i++)
            {
                for (std::size_t j = 0; j < header.Dimensions; j++)
                {
                    std::size_t offset = indexDataSize + i * bytesPerVertex + j * sizeof(float);
                    std::memcpy(dataBuffer.data() + offset, &data.VertexData[i * header.Dimensions + j], sizeof(float));
                }

                for (std::size_t j = 0; j < GetTexCoordDimensions(header); j++)
                {
                    std::size_t offset = indexDataSize + vertexDataSize + i * bytesPerTexCoord + j * sizeof(float);
                    std::memcpy(dataBuffer.data() + offset, &data.TexCoordData[i * header.TextureType + j], sizeof(float));
                }
            }

            stream.write(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size());
            
            // Construct footer 
            PLSMeshFooter footer;
            footer.Crc32 = Checksum::CRC32(dataBuffer.data(), dataBuffer.size());
            footer.Eof = 0xff;

            stream.write(reinterpret_cast<const char*>(&footer.Crc32), sizeof(footer.Crc32));
            stream.write(reinterpret_cast<const char*>(&footer.Eof), sizeof(footer.Eof));
            std::size_t bytesWritten = stream.tellp();
            stream.close();

            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            
            result.Success = true;
            result.BytesWritten = bytesWritten;
            result.TimeTaken = duration;
            result.Message = "Successfully wrote mesh data to file.";
            return result;
        }
        catch (const std::ios_base::failure& e)
        {
            PLS_LOG_WARN("Failed to write mesh data to file: {0}", e.what());
            std::stringstream ss("Failed to write to mesh file: ");
            ss << e.what();
            result.Message = ss.str();
            return result;
        }
    }

    MeshReadResult PLSMesh::ReadData(const File& file, PLSMeshHeader& header, PLSMeshData& data)
    {
        MeshReadResult result;
        try
        {
            // Open file in binary mode with all error checking enabled
            std::ifstream stream(file.GetAbsolutePath(), std::ios::binary | std::ios::in);
            stream.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
            auto startTime = std::chrono::high_resolution_clock::now();

            // Read header, manually read each field to prevent padding
            stream.read(reinterpret_cast<char*>(&header.Signature), sizeof(header.Signature));
            stream.read(reinterpret_cast<char*>(&header.Version), sizeof(header.Version));
            stream.read(reinterpret_cast<char*>(&header.VertexCount), sizeof(header.VertexCount));
            stream.read(reinterpret_cast<char*>(&header.IndexCount), sizeof(header.IndexCount));
            stream.read(reinterpret_cast<char*>(&header.Dimensions), sizeof(header.Dimensions));
            stream.read(reinterpret_cast<char*>(&header.TextureType), sizeof(header.TextureType));
            stream.read(reinterpret_cast<char*>(&header.DataTypeBitmap), sizeof(header.DataTypeBitmap));

            std::size_t bytesPerVertex = sizeof(float) * header.Dimensions;
            std::size_t bytesPerIndex = sizeof(std::uint32_t);
            std::size_t bytesPerTexCoord = sizeof(float) * GetTexCoordDimensions(header);

            std::size_t vertexDataSize = bytesPerVertex * header.VertexCount;
            std::size_t indexDataSize = bytesPerIndex * header.IndexCount;
            std::size_t texCoordDataSize = bytesPerTexCoord * header.VertexCount; // Will be 0 if bytesPerTexCoord is 0

            std::size_t dataBufferSize = indexDataSize + vertexDataSize + texCoordDataSize;
            std::vector<std::byte> dataBuffer(dataBufferSize);
            dataBuffer.resize(dataBufferSize);
            stream.read(reinterpret_cast<char*>(dataBuffer.data()), dataBuffer.size());

            // Seperate out into vertex data, index data, and texture coordinate data
            data.IndexData.resize(header.IndexCount);
            data.VertexData.resize(header.VertexCount * header.Dimensions);
            data.TexCoordData.resize(header.VertexCount * GetTexCoordDimensions(header));

            for (std::size_t i = 0; i < header.IndexCount; i++)
            {
                std::size_t offset = i * bytesPerIndex;
                std::memcpy(&data.IndexData[i], dataBuffer.data() + offset, sizeof(std::uint32_t));
            }

            for (std::size_t i = 0; i < header.VertexCount; i++)
            {
                for (std::size_t j = 0; j < header.Dimensions; j++)
                {
                    std::size_t offset = indexDataSize + i * bytesPerVertex + j * sizeof(float);
                    std::memcpy(&data.VertexData[i * header.Dimensions + j], dataBuffer.data() + offset, sizeof(float));
                }

                for (std::size_t j = 0; j < GetTexCoordDimensions(header); j++)
                {
                    std::size_t offset = indexDataSize + vertexDataSize + i * bytesPerTexCoord + j * sizeof(float);
                    std::memcpy(&data.TexCoordData[i * header.TextureType + j], dataBuffer.data() + offset, sizeof(float));
                }
            }

            // Read footer
            PLSMeshFooter footer;
            stream.read(reinterpret_cast<char*>(&footer.Crc32), sizeof(footer.Crc32));
            stream.read(reinterpret_cast<char*>(&footer.Eof), sizeof(footer.Eof));

            // Verify footer
            if (!Checksum::ValidateCRC32(dataBuffer.data(), dataBuffer.size(), footer.Crc32))
            {
                PLS_LOG_WARN("Mesh file CRC32 checksum failed.");
                result.Message = "Mesh file CRC32 checksum failed.";
                return result;
            }

            if (footer.Eof != 0xff)
            {
                PLS_LOG_WARN("Mesh file EOF marker failed.");
                result.Message = "Mesh file EOF marker failed.";
                return result;
            }

            result.BytesRead = stream.tellg();
            stream.close();
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            result.TimeTaken = duration;
            result.Success = true;
            result.Message = "Successfully read mesh data from file.";
            return result;
        }
        catch (const std::ios_base::failure& e)
        {
            PLS_LOG_WARN("Failed to read mesh data from file: {0}", e.what());
            std::stringstream ss("Failed to read from mesh file: ");
            ss << e.what();
            result.Message = ss.str();
            return result;
        }
    }

    MeshWriteResult PLSMesh::Write(File& file, const Mesh2D& mesh)
    {
        PLSMeshHeader header;
        header.Dimensions = 2;
        header.IndexCount = mesh.GetIndices().size();
        header.VertexCount = mesh.GetVertexData().GetVertexCount();
        header.TextureType = 2;
        header.DataTypeBitmap = 0b00000001;
        PLSMeshData data;
        data.VertexData = mesh.GetVertexData().GetVertices();
        data.IndexData = mesh.GetIndices();
        data.TexCoordData = mesh.GetVertexData().GetTextureCoordinates();
        return WriteData(file, header, data);
    }

    MeshParseResult PLSMesh::Parse(const File& file, UsageType usageType, VertexDataType type)
    {
        PLSMeshHeader header;
        PLSMeshData data;
        MeshReadResult readResult = ReadData(file, header, data);
        MeshParseResult result;
        if (!readResult.Success)
        {
            PLS_LOG_WARN("Failed to parse mesh file: {0}", readResult.Message);
            result.Message = readResult.Message;
            return result;
        }

        result.Mesh2D = std::make_shared<Mesh2D>(usageType, type);
        result.Mesh2D->GetVertexDataRef().SetVertexCount(header.VertexCount);
        result.Mesh2D->GetVertexDataRef().SetVertices(data.VertexData);
        result.Mesh2D->GetVertexDataRef().SetTextureCoordinates(data.TexCoordData);
        result.Mesh2D->SetIndices(data.IndexData);
        result.BytesParsed = readResult.BytesRead;
        result.Success = true;
        result.Message = "Successfully parsed mesh file.";
        result.TimeTaken = readResult.TimeTaken;
        return result;
    }

    std::size_t PLSMesh::GetTexCoordDimensions(const PLSMeshHeader& header)
    {
        if ((header.DataTypeBitmap & (1ull<< 0)) == 0)
            return 0; // No texture coordinates
        switch (header.TextureType)
        {
            case 0:
                return 0;
            case 1:
                return 1; // 1D texture coordinates are always 1 float
            case 2:
                return 2; // 2D texture coordinates are always 2 float
            case 3:
                return 3; // 3D texture coordinates are always 3 float
            case 4:
                return 4; // Cube texture coordinates are always 4 float
            default:
                PLS_LOG_WARN("Invalid texture type: {0}", header.TextureType);
                return 0xffff; // Magic number to indicate error
        }
    }
}
