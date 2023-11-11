#pragma once

#include "GL.h"

namespace Pulsarion::OpenGL
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void SetData(const void* data, unsigned int size, BufferUsage = BufferUsage::StaticDraw);

        void Bind() const;
        void Unbind() const;

    private:
        Buffer_t m_Buffer;
    };
}
