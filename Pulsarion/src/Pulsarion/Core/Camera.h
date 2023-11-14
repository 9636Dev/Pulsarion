#pragma once
#include "Pulsarion/Core/PulsarionCore.h"

#include "Pulsarion/Util/Modifiable.h"

#include <glm/glm.hpp>

namespace Pulsarion
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::quat& rotation);

        const glm::vec3& GetPosition() const;
        const glm::quat& GetRotation() const;
        glm::vec3& GetPositionRef();
        glm::quat& GetRotationRef();

        glm::mat4 GetPositionMatrix() const;
        glm::mat4 GetRotationMatrix() const;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 Get2DViewMatrix() const;
    private:
        Modifiable<glm::vec3> m_Position;
        Modifiable<glm::quat> m_Rotation;
        mutable bool m_Position2DDirty;
        mutable bool m_Rotation2DDirty;
    };
}