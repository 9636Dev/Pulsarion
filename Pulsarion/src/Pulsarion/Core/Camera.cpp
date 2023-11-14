#include "Pulsarionpch.h"
#include "Camera.h"

namespace Pulsarion
{
    Camera::Camera() : m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(0.0f)), m_Position2DDirty(true), m_Rotation2DDirty(true)
    {

    }

    Camera::~Camera()
    {

    }

    void Camera::SetPosition(const glm::vec3& position)
    {
        m_Position2DDirty = true;
        m_Position.Set(position);
    }

    void Camera::SetRotation(const glm::quat& rotation)
    {
        m_Rotation2DDirty = true;
        m_Rotation.Set(rotation);
    }

    const glm::vec3& Camera::GetPosition() const
    {
        return m_Position.GetConst();
    }

    const glm::quat& Camera::GetRotation() const
    {
        return m_Rotation.GetConst();
    }

    glm::vec3& Camera::GetPositionRef()
    {
        m_Position2DDirty = true;
        return m_Position.Get();
    }

    glm::quat& Camera::GetRotationRef()
    {
        m_Rotation2DDirty = true;
        return m_Rotation.Get();
    }

    glm::mat4 Camera::GetPositionMatrix() const
    {
        static glm::mat4 translation = glm::mat4(1.0f);
        if (m_Position.IsDirty())
        {
            translation = glm::translate(glm::mat4(1.0f), m_Position.GetConst());
            m_Position.SetDirty(false);
        }
        return translation;
    }

    glm::mat4 Camera::GetRotationMatrix() const
    {
        static glm::mat4 rotation = glm::mat4(1.0f);
        if (m_Rotation.IsDirty())
        {
            rotation = glm::toMat4(m_Rotation.GetConst());
        }
        return rotation;
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        static glm::mat4 view = GetPositionMatrix() * GetRotationMatrix();
        if (m_Position.IsDirty() || m_Rotation.IsDirty())
        {
            view = GetPositionMatrix() * GetRotationMatrix();
        }
        return view;
    }

    glm::mat4 Camera::Get2DViewMatrix() const
    {
        static glm::mat4 view = glm::mat4(1.0f);
        if (m_Position2DDirty || m_Rotation2DDirty)
        {
            glm::vec3 eulerAngles = glm::eulerAngles(m_Rotation.GetConst());
            // Translate x and y only
            view = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.GetConst().x, m_Position.GetConst().y, 0.0f));
            // Rotate the z axis only
            view = glm::rotate(view, eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
            m_Position2DDirty = false;
            m_Rotation2DDirty = false;
        }
        return view;
    }
}