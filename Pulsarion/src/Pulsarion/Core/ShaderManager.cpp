#include "Pulsarionpch.h"
#include "ShaderManager.h"

namespace Pulsarion
{
    std::unordered_map<Shading::ShaderSignature, std::shared_ptr<Shader>> ShaderManager::s_Shaders;

    void ShaderManager::CreateShader(const Shading::ShaderSignature& signature, Shading::ShaderInputOrder inputOrder)
    {
        if (inputOrder.VertexInputs.empty())
        {
            inputOrder = Shading::ShaderInputOrder::DefaultOrder(signature);
        }
        s_Shaders[signature] = CreateShaderWithSignature(signature, inputOrder);
    }

    std::shared_ptr<Shader> ShaderManager::GetShader(const Shading::ShaderSignature& signature)
    {
        if (s_Shaders.find(signature) == s_Shaders.end())
            CreateShader(signature);

        return s_Shaders[signature];
    }

    void ShaderManager::AddShader(std::shared_ptr<Shader> shader)
    {
        s_Shaders[shader->GetSignature()] = shader;
    };

    void ShaderManager::RemoveShader(const Shading::ShaderSignature& signature)
    {
        s_Shaders.erase(signature);
    }
}
