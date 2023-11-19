#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Core/Backend/MeshBackend.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Pulsarion::OpenGL
{
    class GLRenderer;
    class PULSARION_API GLMeshBackend2D : public MeshBackend2D
    {
    public:
        friend class GLRenderer;
        GLMeshBackend2D();
        ~GLMeshBackend2D();

        void SetVertexData(const VertexData2D& vertexData) override;
        void SetIndices(const std::vector<std::uint32_t>& indices) override;

        void Bind() const override;
        void Unbind() const override;
    private:
        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;
        std::unique_ptr<VertexBuffer> m_InstanceBuffer;
        IndexBuffer m_IndexBuffer;
        VertexBufferLayout m_Layout;
    };
}
