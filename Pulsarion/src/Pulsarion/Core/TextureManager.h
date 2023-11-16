#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Texture.h"

#include "Pulsarion/Util/Image.h"

#include <unordered_map>
#include <memory>
#include <utility>
#include <string>

namespace Pulsarion
{
    class PULSARION_API TextureManager
    {
    public:
        static std::uint32_t CreateTexture2D(const std::string& textureName, const Image& textureImage);
        static bool DeleteTexture2D(const std::string& textureName);
        static std::uint32_t Get2DTextureID(const std::string& textureName);
        static std::shared_ptr<Texture2D> Get2DTexture(const std::string& textureName);
        static bool Bind2DTexture(std::uint32_t textureId, std::uint32_t slot);
        static std::string Get2DTextureName(std::uint32_t textureId);
        static bool LoadFromTextureList(const File& textureListFile);
    private:
        static std::uint32_t s_TextureID;
        static std::unordered_map<std::string, std::uint32_t> s_2DTextureIDs;
        static std::unordered_map<std::uint32_t, std::shared_ptr<Texture2D>> s_2DTextures;
    };
}
