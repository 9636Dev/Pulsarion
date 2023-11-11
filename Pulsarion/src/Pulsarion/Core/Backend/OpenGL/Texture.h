#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "GL.h"
#include "Enum.h"

#include "Pulsarion/Util/Image.h"

namespace Pulsarion::OpenGL
{
    class Texture
    {
    public:
        Texture();
        ~Texture();

        void DefaultSettings();

        void SetData(const Image& image);

        void Bind() const;
        void Unbind() const;
        void SetTextureUnit(TextureUnit unit);

        void MinFilter(TextureFilter filter);
        void MagFilter(TextureFilter filter);
        void WrapS(TextureWrap wrap);
        void WrapT(TextureWrap wrap);
    private:
        Texture_t m_Texture;
        TextureUnit m_TextureUnit;
    };
}
