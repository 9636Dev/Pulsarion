#pragma once

#include "GL.h"
#include "Enum.h"

namespace Pulsarion::OpenGL
{
    class UniformBuffer {
    public:
        UniformBuffer();
        ~UniformBuffer();

        void SetData(const void* data, std::uint32_t size, BufferUsage = BufferUsage::StaticDraw);
        void SetSubData(const void* data, std::uint32_t size, std::uint32_t offset);
    private:
        void Bind() const;
        void Unbind() const;

        Buffer_t m_Buffer;
    };
}
