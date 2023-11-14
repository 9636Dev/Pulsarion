#include "Pulsarionpch.h"
#include "MaterialManager.h"

namespace Pulsarion
{
    std::unordered_map<std::string, std::shared_ptr<Material>> MaterialManager::s_Materials;

    std::shared_ptr<Material> MaterialManager::CreateMaterial(const std::string& name)
    {
        auto material = std::make_shared<Material>();
        s_Materials[name] = material;
        return material;
    }

    void MaterialManager::AddMaterial(const std::string& name, const std::shared_ptr<Material>& material)
    {
        s_Materials[name] = material;
    }

    std::shared_ptr<Material> MaterialManager::GetMaterial(const std::string& name)
    {
        return s_Materials[name];
    }

    bool MaterialManager::HasMaterial(const std::string& name)
    {
        return s_Materials.find(name) != s_Materials.end();
    }

    std::shared_ptr<Material> MaterialManager::RemoveMaterial(const std::string& name)
    {
        auto material = s_Materials[name];
        s_Materials.erase(name);
        return material;
    }
}
