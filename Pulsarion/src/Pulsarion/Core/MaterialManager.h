#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Core/Material.h"

#include <memory>
#include <unordered_map>
#include <string>

namespace Pulsarion
{
    class PULSARION_API MaterialManager
    {
    public:
        static std::shared_ptr<Material> CreateMaterial(const std::string& name);
        static void AddMaterial(const std::string& name, const std::shared_ptr<Material>& material);
        static std::shared_ptr<Material> GetMaterial(const std::string& name);
        static bool HasMaterial(const std::string& name);
        static std::shared_ptr<Material> RemoveMaterial(const std::string& name);

    private:
        static std::unordered_map<std::string, std::shared_ptr<Material>> s_Materials;
    };
}
