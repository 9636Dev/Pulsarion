#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include "Mesh.h"

#include <memory>
#include <utility>
#include <unordered_map>

namespace Pulsarion
{
    class MeshManager
    {
    public:
        static std::pair<std::uint32_t, std::shared_ptr<Mesh2D>> Create2DMesh(UsageType type, VertexDataType vertexType = VertexDataType::TightlyPacked);
        static std::uint32_t Add2DMesh(std::shared_ptr<Mesh2D> mesh);

        static std::shared_ptr<Mesh2D> Get2DMesh(std::uint32_t);
        static std::shared_ptr<Mesh2D> Remove2DMesh(std::uint32_t);

    private:
        static std::uint32_t GetNextId();

        static std::uint32_t s_MeshID;
        static std::unordered_map<std::uint32_t, std::shared_ptr<Mesh2D>> s_2DMeshes;
    };
}
