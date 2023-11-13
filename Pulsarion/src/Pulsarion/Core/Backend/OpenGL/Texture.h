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

        void Bind(TextureUnit unit = TextureUnit::Texture0) const;
        void Unbind() const;

        void MinFilter(TextureFilter filter);
        void MagFilter(TextureFilter filter);
        void WrapS(TextureWrap wrap);
        void WrapT(TextureWrap wrap);
    private:
        Texture_t m_Texture;
    };
}
