#include "Pulsarionpch.h"
#include "AABB.h"

namespace Pulsarion
{
    AxisAlignedBoundingBox2D::AxisAlignedBoundingBox2D(float minX, float maxX, float minY, float maxY) : m_MinX(minX), m_MaxX(maxX), m_MinY(minY), m_MaxY(maxY)
    {

    }

    AxisAlignedBoundingBox3D::AxisAlignedBoundingBox3D(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) : m_MinX(minX), m_MaxX(maxX), m_MinY(minY), m_MaxY(maxY), m_MinZ(minZ), m_MaxZ(maxZ)
    {

    }
}
