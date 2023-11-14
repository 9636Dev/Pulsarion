#include "Pulsarionpch.h"
#include "MeshManager.h"

namespace Pulsarion
{
    std::uint32_t MeshManager::s_MeshID = 0;
    std::unordered_map<std::uint32_t, std::shared_ptr<Mesh2D>> MeshManager::s_2DMeshes;

    std::pair<std::uint32_t, std::shared_ptr<Mesh2D>> MeshManager::Create2DMesh(UsageType usageType, VertexDataType vertexDataType)
    {
        std::shared_ptr<Mesh2D> mesh = std::make_shared<Mesh2D>(usageType, vertexDataType);
        std::uint32_t id = GetNextId();
        s_2DMeshes[id] = mesh;
        return std::make_pair(id, mesh);
    }

    std::uint32_t MeshManager::Add2DMesh(std::shared_ptr<Mesh2D> mesh)
    {
        std::uint32_t id = GetNextId();
        s_2DMeshes[id] = mesh;
        return id;
    }

    std::shared_ptr<Mesh2D> MeshManager::Get2DMesh(std::uint32_t id)
    {
        return s_2DMeshes[id];
    }

    std::shared_ptr<Mesh2D> MeshManager::Remove2DMesh(std::uint32_t id)
    {
        std::shared_ptr<Mesh2D> mesh = s_2DMeshes[id];
        s_2DMeshes.erase(id);
        return mesh;
    }

    std::uint32_t MeshManager::GetNextId()
    {
        return s_MeshID++;
    }
}
