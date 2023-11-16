#include <glm/gtc/quaternion.hpp>
#include "Pulsarion.h"
#include "Pulsarion/Test.h"
#include <memory>

#include <random>
#include <iostream>

using namespace Pulsarion;

int main(int argc, char** argv) {
    Initializers::InitLogger();

    /*
    * Current largest benchmark:
        Write info:
        Success: 1
        Message: Successfully wrote mesh data to file.
        Bytes Written: 2000000027
        Time taken: 18138
        Parse info:
        Success: 1
        Message: Successfully parsed mesh file.
        Bytes Parsed: 2000000027
        Time taken: 15031
    */
    // Test writing and loading a mesh with 10000 vertices and 10000 indices, generated randomly
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

    std::vector<float> vertexPositions;
    std::vector<std::uint32_t> indices;
    std::vector<float> textureCoords;

    for (size_t i = 0; i < 10000; ++i)
    {
        vertexPositions.push_back(distribution(generator));
        vertexPositions.push_back(distribution(generator));
        indices.push_back(static_cast<std::uint32_t>(i));
        textureCoords.push_back(distribution(generator));
        textureCoords.push_back(distribution(generator));
    }

    File meshFile("assets/mesh/test_10k.plsmesh");
    std::shared_ptr<Mesh2D> mesh = std::make_shared<Mesh2D>(UsageType::Static);
    mesh->GetVertexDataRef().SetVertexCount(10000);
    mesh->GetVertexDataRef().SetVertices(vertexPositions);
    mesh->GetVertexDataRef().SetTextureCoordinates(textureCoords);
    mesh->SetIndices(indices);

    auto result = PLSMesh::Write(meshFile, *mesh);
    // Print results
    std::cout << "Write info:" << std::endl;
    std::cout << "Success: " << result.Success << std::endl;
    std::cout << "Message: " << result.Message << std::endl;
    std::cout << "Bytes Written: " << result.BytesWritten << std::endl;
    std::cout << "Time taken: " << result.TimeTaken << std::endl;

    // Read the mesh back
    auto parseResult = PLSMesh::Parse(meshFile);
    std::cout << "Parse info:" << std::endl;
    std::cout << "Success: " << parseResult.Success << std::endl;
    std::cout << "Message: " << parseResult.Message << std::endl;
    std::cout << "Bytes Parsed: " << parseResult.BytesParsed << std::endl;
    std::cout << "Time taken: " << parseResult.TimeTaken << std::endl;

    // Compare the meshes
    std::cout << "Comparing meshes..." << std::endl;
    for (size_t i = 0; i < 1000; ++i)
    {
        if (mesh->GetVertexData().GetVertices()[i] != parseResult.Mesh2D->GetVertexData().GetVertices()[i])
        {
            std::cout << "Vertex mismatch at index " << i << std::endl;
            std::cout << "Original: " << mesh->GetVertexData().GetVertices()[i] << std::endl;
            std::cout << "Parsed: " << parseResult.Mesh2D->GetVertexData().GetVertices()[i] << std::endl;
        }

        if (mesh->GetVertexData().GetTextureCoordinates()[i] != parseResult.Mesh2D->GetVertexData().GetTextureCoordinates()[i])
        {
            std::cout << "Texture coordinate mismatch at index " << i << std::endl;
            std::cout << "Original: " << mesh->GetVertexData().GetTextureCoordinates()[i] << std::endl;
            std::cout << "Parsed: " << parseResult.Mesh2D->GetVertexData().GetTextureCoordinates()[i] << std::endl;
        }

        if (mesh->GetIndices()[i] != parseResult.Mesh2D->GetIndices()[i])
        {
            std::cout << "Index mismatch at index " << i << std::endl;
            std::cout << "Original: " << mesh->GetIndices()[i] << std::endl;
            std::cout << "Parsed: " << parseResult.Mesh2D->GetIndices()[i] << std::endl;
        }
    }

    // Arg argument is generate_mesh
    if (argc == 2)
    {
        if (std::strcmp(argv[1], "generate_mesh") == 0)
        {
            Mesh2D rectangle(UsageType::Static);
            rectangle.GetVertexDataRef().SetVertexCount(4);
            rectangle.GetVertexDataRef().SetVertices({
                -1.0f,  1.0f,
                 1.0f,  1.0f,
                -1.0f, -1.0f,
                 1.0f, -1.0f,
            });
            rectangle.GetVertexDataRef().SetTextureCoordinates({
                -1.0f,  1.0f,
                 1.0f,  1.0f,
                -1.0f, -1.0f,
                 1.0f, -1.0f
            });
            rectangle.SetIndices({ 0, 1, 2, 1, 2, 3 });
            File rectFile("assets/mesh/rectangle_base.plsmesh");
            PLSMesh::Write(rectFile, rectangle);
        }
    }

    Test();
}
