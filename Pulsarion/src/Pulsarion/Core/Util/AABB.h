#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

namespace Pulsarion
{
    class PULSARION_API AxisAlignedBoundingBox2D
    {
    public:
        AxisAlignedBoundingBox2D(float minX, float maxX, float minY, float maxY);
        AxisAlignedBoundingBox2D(const AxisAlignedBoundingBox2D& other) = default;
        AxisAlignedBoundingBox2D(AxisAlignedBoundingBox2D&& other) noexcept = default;
        AxisAlignedBoundingBox2D& operator=(const AxisAlignedBoundingBox2D& other) = default;
        AxisAlignedBoundingBox2D& operator=(AxisAlignedBoundingBox2D&& other) noexcept = default;
        ~AxisAlignedBoundingBox2D() = default;


    private:
        float m_MinX;
        float m_MaxX;
        float m_MinY;
        float m_MaxY;
    };

    class PULSARION_API AxisAlignedBoundingBox3D
    {
    public:
        AxisAlignedBoundingBox3D(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
        AxisAlignedBoundingBox3D(const AxisAlignedBoundingBox3D& other) = default;
        AxisAlignedBoundingBox3D(AxisAlignedBoundingBox3D&& other) noexcept = default;
        AxisAlignedBoundingBox3D& operator=(const AxisAlignedBoundingBox3D& other) = default;
        AxisAlignedBoundingBox3D& operator=(AxisAlignedBoundingBox3D&& other) noexcept = default;
        ~AxisAlignedBoundingBox3D() = default;

    private:
        float m_MinX;
        float m_MaxX;
        float m_MinY;
        float m_MaxY;
        float m_MinZ;
        float m_MaxZ;
    };
}
