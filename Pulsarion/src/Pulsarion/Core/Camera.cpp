#include "Pulsarionpch.h"
#include "Camera.h"

namespace Pulsarion
{
    Camera::Camera() : m_Position2D(glm::vec2(0.0f, 0.0f)), m_Rotation2D(0.0f), m_Position3D(glm::vec3(0.0f, 0.0f, 0.0f)), m_Rotation3D(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), m_2DPositionMatrix(1.0f), m_2DRotationMatrix(1.0f), m_3DPositionMatrix(1.0f), m_3DRotationMatrix(1.0f), m_2DViewMatrix(1.0f), m_3DViewMatrix(1.0f)
    {

    }

    Camera::~Camera()
    {

    }

    void Camera::Set2DPosition(const glm::vec2& position)
    {
        m_Position2D.Set(position);
    }

    void Camera::Set2DRotation(float rotation)
    {
        m_Rotation2D.Set(rotation);
    }

    void Camera::Set3DPosition(const glm::vec3& position)
    {
        m_Position3D.Set(position);
    }

    void Camera::Set3DRotation(const glm::quat& rotation)
    {
        m_Rotation3D.Set(rotation);
    }

    const glm::vec2& Camera::Get2DPosition() const
    {
        return m_Position2D.GetConst();
    }

    float Camera::Get2DRotation() const
    {
        return m_Rotation2D.GetConst();
    }

    const glm::vec3& Camera::Get3DPosition() const
    {
        return m_Position3D.GetConst();
    }

    const glm::quat& Camera::Get3DRotation() const
    {
        return m_Rotation3D.GetConst();
    }

    glm::vec2& Camera::Get2DPositionRef()
    {
        return m_Position2D.Get();
    }

    glm::quat& Camera::Get3DRotationRef()
    {
        return m_Rotation3D.Get();
    }

    glm::vec3& Camera::Get3DPositionRef()
    {
        return m_Position3D.Get();
    }

    const glm::mat4& Camera::Get2DPositionMatrix() const
    {
        if (m_Position2D.IsDirty())
        {
            m_2DPositionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position2D.GetConst(), 0.0f));
            m_Position2D.SetDirty(false);
        }
        return m_2DPositionMatrix;
    }

    const glm::mat4& Camera::Get2DRotationMatrix() const
    {
        if (m_Rotation2D.IsDirty())
        {
            m_2DRotationMatrix = glm::rotate(glm::mat4(1.0f), m_Rotation2D.GetConst(), glm::vec3(0.0f, 0.0f, 1.0f));
            m_Rotation2D.SetDirty(false);
        }
        return m_2DRotationMatrix;
    }

    const glm::mat4& Camera::Get3DPositionMatrix() const
    {
        if (m_Position3D.IsDirty())
        {
            m_3DPositionMatrix = glm::translate(glm::mat4(1.0f), m_Position3D.GetConst());
            m_Position3D.SetDirty(false);
        }
        return m_3DPositionMatrix;
    }

    const glm::mat4& Camera::Get3DRotationMatrix() const
    {
        if (m_Rotation3D.IsDirty())
        {
            m_3DRotationMatrix = glm::toMat4(m_Rotation3D.GetConst());
            m_Rotation3D.SetDirty(false);
        }
        return m_3DRotationMatrix;
    }

    const glm::mat4& Camera::Get2DViewMatrix() const
    {
        if (m_Position2D.IsDirty() || m_Rotation2D.IsDirty())
            m_2DViewMatrix = Get2DRotationMatrix() * Get2DPositionMatrix();
        
        return m_2DViewMatrix;
    }

    const glm::mat4& Camera::Get3DViewMatrix() const
    {
        if (m_Position3D.IsDirty() || m_Rotation3D.IsDirty())
            m_3DViewMatrix = Get3DRotationMatrix() * Get3DPositionMatrix();

        return m_3DViewMatrix;
    }
}
