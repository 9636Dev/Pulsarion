#include "Pulsarionpch.h"
#include "VertexBuffer.h"

namespace Pulsarion::OpenGL
{
    VertexBufferLayout::VertexBufferLayout()
        : m_Stride(0), m_Attributes()
    {

    }

    VertexBufferLayout::~VertexBufferLayout()
    {

    }

    Buffer_t GenerateVertexBuffer()
    {
        Buffer_t buffer;
        GL::GenBuffers(1, &buffer);
        return buffer;
    }

    VertexBuffer::VertexBuffer() : m_Buffer(GenerateVertexBuffer())
    {

    }

    VertexBuffer::~VertexBuffer()
    {
        GL::DeleteBuffers(1, &m_Buffer);
    }

    void VertexBuffer::SetData(const void* data, std::uint32_t size, BufferUsage usage)
    {
        Bind();
        GL::BufferData(BufferTarget::ArrayBuffer, size, data, usage);
        Unbind();
    }

    void VertexBuffer::SetSubData(const void* data, std::uint32_t size, std::uint32_t offset)
    {
        Bind();
        GL::BufferSubData(BufferTarget::ArrayBuffer, offset, size, data);
    }

    void VertexBuffer::Bind() const
    {
        GL::BindBuffer(BufferTarget::ArrayBuffer, m_Buffer);
    }

    void VertexBuffer::Unbind() const
    {
        GL::BindBuffer(BufferTarget::ArrayBuffer, 0);
    }
}
