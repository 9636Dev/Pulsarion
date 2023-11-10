#pragma once

#include "GL.h"
#include "Enum.h"

namespace Pulsarion::OpenGL
{
    class VertexArray;

    class VertexBuffer {
    public:
        friend class VertexArray;
        VertexBuffer();
        ~VertexBuffer();

        void SetData(const void* data, std::uint32_t size, BufferUsage = BufferUsage::StaticDraw);
    private:
        void Bind() const;
        void Unbind() const;

        Buffer_t m_Buffer;
    };
}