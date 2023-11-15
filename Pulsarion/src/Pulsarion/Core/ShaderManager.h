#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Shader.h"

#include <unordered_map>
#include <memory>

namespace Pulsarion
{
    class PULSARION_API ShaderManager
    {
    public:
        static void CreateShader(const ShaderSignature& signature);
        static void AddShader(std::shared_ptr<Shader> shader);
        static std::shared_ptr<Shader> GetShader(const ShaderSignature& signature);
        static void RemoveShader(const ShaderSignature& signature);

    private:
        static std::unordered_map<ShaderSignature, std::shared_ptr<Shader>> s_Shaders;
    };
}
