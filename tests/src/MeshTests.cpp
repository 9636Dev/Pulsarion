#include <stfcpp/include/stfcpp/stfcpp.h>

#include "Pulsarion.h"
#include "Pulsarion/Core/Mesh.h"

#include <random>

using namespace Pulsarion;

STF_TEST_SUITE(MeshTests)
{
    void test_creation()
    {
        // 1000 random vertices and 3000 random indices, between 0 and 1000
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1000.0f);
        std::uniform_int_distribution<uint32_t> dis2(0, 1000);

        std::vector<float> vertices;
        std::vector<uint32_t> indices;

        for (int i = 0; i < 1000; i++) {
            vertices.push_back(dis(gen));
            vertices.push_back(dis(gen));
        }

        for (int i = 0; i < 3000; i++) {
            indices.push_back(dis2(gen));
        }

        Mesh2D mesh(UsageType::Static);
        mesh.SetVertexCount(1000);
        mesh.SetVertices(vertices);
        mesh.SetIndices(indices);

        STF_BASIC_ASSERT(mesh.GetVertices(), vertices, "Vertices do not match!");
        STF_BASIC_ASSERT(mesh.GetIndices(), indices, "Indices do not match!");

    }

    STF_SUITE_TEST(CreationTest, test_creation);
};
STF_REGISTER_SUITE(MeshTests);
