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
        static void CreateShader(const Shading::ShaderSignature& signature, Shading::ShaderInputOrder inputOrder = Shading::ShaderInputOrder());
        static void AddShader(std::shared_ptr<Shader> shader);
        static std::shared_ptr<Shader> GetShader(const Shading::ShaderSignature& signature);
        static void RemoveShader(const Shading::ShaderSignature& signature);

    private:
        static std::unordered_map<Shading::ShaderSignature, std::shared_ptr<Shader>> s_Shaders;
    };
}
