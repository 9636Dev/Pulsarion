#include "Pulsarionpch.h"
#include "MeshManager.h"

namespace Pulsarion
{
    std::unordered_map<std::string, std::shared_ptr<Mesh2D>> MeshManager::s_2DMeshes;

    std::shared_ptr<Mesh2D> MeshManager::Create2DMesh(const std::string& name, UsageType usageType, VertexDataType vertexDataType)
    {
        std::shared_ptr<Mesh2D> mesh = std::make_shared<Mesh2D>(usageType, vertexDataType);
        // Find by name
        auto it = s_2DMeshes.find(name);
        if (it != s_2DMeshes.end())
        {
            // Name already exists
            return nullptr;
        }
        s_2DMeshes[name] = mesh;
        return mesh;
    }

    bool MeshManager::Add2DMesh(const std::string& name, std::shared_ptr<Mesh2D> mesh)
    {
        auto it = s_2DMeshes.find(name);
        if (it != s_2DMeshes.end())
        {
            // Name already exists
            return false;
        }

        s_2DMeshes[name] = mesh;
        return true;
    }

    std::shared_ptr<Mesh2D> MeshManager::Get2DMesh(const std::string& name)
    {
        auto it = s_2DMeshes.find(name);
        if (it == s_2DMeshes.end())
        {
            // Name does not exist
            return nullptr;
        }
        return it->second;
    }

    std::shared_ptr<Mesh2D> MeshManager::Remove2DMesh(const std::string& name)
    {
        auto it = s_2DMeshes.find(name);
        if (it == s_2DMeshes.end())
        {
            // Name does not exist
            return nullptr;
        }

        std::shared_ptr<Mesh2D> mesh = it->second;
        s_2DMeshes.erase(it);
        return mesh;
    }
}
