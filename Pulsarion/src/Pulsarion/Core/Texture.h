#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Util/Image.h"
#include "Pulsarion/Util/File.h"

#include <memory>

namespace Pulsarion
{
    class Texture2DBackend
    {
    public:
        virtual ~Texture2DBackend() = default;

        virtual void SetData(const Image& image) = 0;
        virtual bool Bind(std::uint32_t textureSlot = 0) const = 0;
        virtual void Unbind() const = 0;
    };

    class PULSARION_API Texture2D
    {
    public:
        Texture2D(const Image& imageTexture);
        ~Texture2D();

        const Image& GetImage() const { return m_Image; }
        void Bind(std::uint32_t textureSlot) const;
        void Unbind() const;
    private:
        std::unique_ptr<Texture2DBackend> m_Backend;
        Image m_Image;
    };

    extern std::unique_ptr<Texture2DBackend> Create2DTextureBackend(const Image& image);
}
