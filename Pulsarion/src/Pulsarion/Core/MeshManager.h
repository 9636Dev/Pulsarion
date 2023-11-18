#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include "Mesh.h"

#include <memory>
#include <utility>
#include <unordered_map>
#include <string>

namespace Pulsarion
{
    class PULSARION_API MeshManager
    {
    public:
        [[nodiscard]] std::shared_ptr<Mesh2D> Create2DMesh(const std::string& name, UsageType type, VertexDataType vertexType = VertexDataType::TightlyPacked);
        [[nodiscard]] static bool Add2DMesh(const std::string& name, std::shared_ptr<Mesh2D> mesh);

        static std::shared_ptr<Mesh2D> Get2DMesh(const std::string& name);
        static std::shared_ptr<Mesh2D> Remove2DMesh(const std::string& name);

    private:
        static std::unordered_map<std::string, std::shared_ptr<Mesh2D>> s_2DMeshes;
    };
}
