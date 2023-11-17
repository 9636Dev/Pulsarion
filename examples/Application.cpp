#include <glm/gtc/quaternion.hpp>
#include "Pulsarion.h"
#include "Pulsarion/Test.h"
#include <memory>

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
