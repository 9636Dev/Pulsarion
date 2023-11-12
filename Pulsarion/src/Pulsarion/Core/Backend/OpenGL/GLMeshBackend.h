#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Core/Backend/Meshbackend.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Pulsarion::OpenGL
{
    class PULSARION_API GLMeshBackend2D : public MeshBackend2D
    {
    public:
        GLMeshBackend2D();
        ~GLMeshBackend2D();

        void SetVertexData(const VertexData2D& vertexData) override;
        void SetIndices(const std::vector<std::uint32_t>& indices) override;

        void Bind() override;
        void Unbind() override;
    private:
        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;
        IndexBuffer m_IndexBuffer;
        VertexBufferLayout m_Layout;
    };
}
