#include "Pulsarionpch.h"
#include "Camera.h"

namespace Pulsarion
{
    Camera::Camera() : m_Position2D(glm::vec2(0.0f, 0.0f)), m_Rotation2D(0.0f), m_Position3D(glm::vec3(0.0f, 0.0f, 0.0f)), m_Rotation3D(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
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
        static glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position2D.GetConst(), 0.0f));
        if (m_Position2D.IsDirty())
        {
            positionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position2D.GetConst(), 0.0f));
            m_Position2D.SetDirty(false);
        }
        return positionMatrix;
    }

    const glm::mat4& Camera::Get2DRotationMatrix() const
    {
        static glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), m_Rotation2D.GetConst(), glm::vec3(0.0f, 0.0f, 1.0f));
        if (m_Rotation2D.IsDirty())
        {
            rotationMatrix = glm::rotate(glm::mat4(1.0f), m_Rotation2D.GetConst(), glm::vec3(0.0f, 0.0f, 1.0f));
            m_Rotation2D.SetDirty(false);
        }
        return rotationMatrix;
    }

    const glm::mat4& Camera::Get3DPositionMatrix() const
    {
        static glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), m_Position3D.GetConst());
        if (m_Position3D.IsDirty())
        {
            positionMatrix = glm::translate(glm::mat4(1.0f), m_Position3D.GetConst());
            m_Position3D.SetDirty(false);
        }
        return positionMatrix;
    }

    const glm::mat4& Camera::Get3DRotationMatrix() const
    {
        static glm::mat4 rotationMatrix = glm::toMat4(m_Rotation3D.GetConst());
        if (m_Rotation3D.IsDirty())
        {
            rotationMatrix = glm::toMat4(m_Rotation3D.GetConst());
            m_Rotation3D.SetDirty(false);
        }
        return rotationMatrix;
    }

    const glm::mat4& Camera::Get2DViewMatrix() const
    {
        static glm::mat4 viewMatrix = Get2DPositionMatrix() * Get2DRotationMatrix();
        if (m_Position2D.IsDirty() || m_Rotation2D.IsDirty())
            viewMatrix = Get2DPositionMatrix() * Get2DRotationMatrix();
        
        return viewMatrix;
    }

    const glm::mat4& Camera::Get3DViewMatrix() const
    {
        static glm::mat4 viewMatrix = Get3DPositionMatrix() * Get3DRotationMatrix();
        if (m_Position3D.IsDirty() || m_Rotation3D.IsDirty())
            viewMatrix = Get3DPositionMatrix() * Get3DRotationMatrix();

        return viewMatrix;
    }
}
