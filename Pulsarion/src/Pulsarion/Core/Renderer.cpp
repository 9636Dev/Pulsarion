#include "Pulsarionpch.h"
#include "Renderer.h"

#include "Pulsarion/Core/Mesh.h"
#include "Pulsarion/Core/Backend/MeshBackend.h"

namespace Pulsarion
{
    MeshBackend2D* Renderer::GetMeshBackend2D(std::shared_ptr<Mesh2D>& mesh)
    {
        return mesh->m_Backend.get();
    }
}
