#include "Pulsarionpch.h"
#include "UniformBuffer.h"

namespace Pulsarion::OpenGL
{
    static Buffer_t CreateBuffer()
    {
        Buffer_t buffer;
        GL::GenBuffers(1, &buffer);
        return buffer;
    }

    UniformBuffer::UniformBuffer() : m_Buffer(CreateBuffer())
    {

    }

    UniformBuffer::~UniformBuffer()
    {
        GL::DeleteBuffers(1, &m_Buffer);
    }

    void UniformBuffer::Bind() const
    {
        GL::BindBuffer(BufferTarget::UniformBuffer, m_Buffer);
    }

    void UniformBuffer::Unbind() const
    {
        GL::BindBuffer(BufferTarget::UniformBuffer, 0);
    }

    void UniformBuffer::SetSubData(const void* data, std::uint32_t size, std::uint32_t offset)
    {
        GL::BindBuffer(BufferTarget::UniformBuffer, m_Buffer);
        GL::BufferSubData(BufferTarget::UniformBuffer, offset, size, data);
    }

    void UniformBuffer::SetData(const void* data, std::uint32_t size, BufferUsage usage)
    {
        GL::BindBuffer(BufferTarget::UniformBuffer, m_Buffer);
        GL::BufferData(BufferTarget::UniformBuffer, size, data, usage);
    }
}
