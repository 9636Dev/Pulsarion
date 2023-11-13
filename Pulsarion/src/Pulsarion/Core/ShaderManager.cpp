#include "Pulsarionpch.h"
#include "ShaderManager.h"

namespace Pulsarion
{
    std::unordered_map<ShaderSignature, std::shared_ptr<Shader>> ShaderManager::s_Shaders;

    void ShaderManager::CreateShader(const ShaderSignature& signature)
    {
        s_Shaders[signature] = CreateShaderWithSignature(signature);
    }

    std::shared_ptr<Shader> ShaderManager::GetShader(const ShaderSignature& signature)
    {
        if (s_Shaders.find(signature) == s_Shaders.end())
        {
            CreateShader(signature);
        }

        return s_Shaders[signature];
    }

    void ShaderManager::AddShader(std::shared_ptr<Shader> shader)
    {
        s_Shaders[shader->GetSignature()] = shader;
    };

    void ShaderManager::RemoveShader(const ShaderSignature& signature)
    {
        s_Shaders.erase(signature);
    }
}
