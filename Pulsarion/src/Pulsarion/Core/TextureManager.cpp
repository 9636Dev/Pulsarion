#include "Pulsarionpch.h"
#include "TextureManager.h"

#include <nlohmann/json.hpp>

namespace Pulsarion
{
    std::uint32_t TextureManager::s_TextureID = 1;
    std::unordered_map<std::string, std::uint32_t> TextureManager::s_2DTextureIDs;
    std::unordered_map<std::uint32_t, std::shared_ptr<Texture2D>> TextureManager::s_2DTextures;

    std::uint32_t TextureManager::CreateTexture2D(const std::string& textureName, const Image& textureImage)
    {
        std::uint32_t id = s_TextureID++;
        s_2DTextureIDs[textureName] = id;
        s_2DTextures[id] = std::make_shared<Texture2D>(textureImage);
        return id;
    }

    bool TextureManager::DeleteTexture2D(const std::string& textureName)
    {
        auto it = s_2DTextureIDs.find(textureName);
        if (it != s_2DTextureIDs.end())
        {
            s_2DTextures.erase(it->second);
            s_2DTextureIDs.erase(it);
            return true;
        }
        return false;
    }

    std::uint32_t TextureManager::Get2DTextureID(const std::string& textureName)
    {
        auto it = s_2DTextureIDs.find(textureName);
        if (it != s_2DTextureIDs.end())
        {
            return it->second;
        }
        return 0;


    }

    bool TextureManager::Bind2DTexture(std::uint32_t textureID, std::uint32_t slot)
    {
        auto it = s_2DTextures.find(textureID);
        if (it != s_2DTextures.end())
        {
            it->second->Bind(slot);
            return true;
        }
        return false;
    }

    std::shared_ptr<Texture2D> TextureManager::Get2DTexture(const std::string& textureName)
    {
        auto it = s_2DTextureIDs.find(textureName);
        if (it != s_2DTextureIDs.end())
        {
            return s_2DTextures[it->second];
        }
        return nullptr;
    }

    std::string TextureManager::Get2DTextureName(std::uint32_t textureId)
    {
        for (auto& texture : s_2DTextureIDs)
        {
            if (texture.second == textureId)
            {
                return texture.first;
            }
        }
        return "";
    }

    bool TextureManager::LoadFromTextureList(const File& textureListFile)
    {
        auto textureListPath = textureListFile.GetParent().GetAbsolutePath();
        auto content = textureListFile.GetContent();
        if (!content.has_value()) return false;
        try
        {
            auto textureList = nlohmann::json::parse(content.value());
            for (auto& texture : textureList["textures"])
            {
                auto textureName = texture["name"].get<std::string>();
                auto texturePath = texture["path"].get<std::string>();
                // Append texture path to the texture list path
                texturePath = textureListPath.string() + "/" + texturePath;
                Image textureImage = Image(File(texturePath));
                (void)CreateTexture2D(textureName, textureImage);
            }
            return true;
        }
        catch (const std::exception& e)
        {
            PLS_LOG_WARN("Failed to load texture list: {0}", e.what());
            return false;
        }
    }
}
