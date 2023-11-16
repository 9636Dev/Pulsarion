#include "Pulsarionpch.h"
#include "IndexBuffer.h"

#include "Enum.h"

namespace Pulsarion::OpenGL
{
    IndexBuffer::IndexBuffer()
    {
        GL::GenBuffers(1, &m_Buffer);
    }

    IndexBuffer::~IndexBuffer()
    {
        GL::DeleteBuffers(1, &m_Buffer);
    }

    void IndexBuffer::SetData(const void* data, unsigned int size, BufferUsage usage)
    {
        Bind();
        GL::BufferData(BufferTarget::ElementArrayBuffer, size, data, usage);
        Unbind();
    }

    void IndexBuffer::Bind() const
    {
        GL::BindBuffer(BufferTarget::ElementArrayBuffer, m_Buffer);
    }

    void IndexBuffer::Unbind() const
    {
        GL::BindBuffer(BufferTarget::ElementArrayBuffer, 0);
    }
}
