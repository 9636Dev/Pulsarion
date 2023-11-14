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

        void Set3DPosition(const glm::vec3& position);
        void Set3DRotation(const glm::quat& rotation);
        void Set2DPosition(const glm::vec2& position);
        void Set2DRotation(float rotation);

        const glm::vec3& Get3DPosition() const;
        const glm::quat& Get3DRotation() const;
        const glm::vec2& Get2DPosition() const;
        float Get2DRotation() const;

        glm::vec3& Get3DPositionRef();
        glm::quat& Get3DRotationRef();
        glm::vec2& Get2DPositionRef();

        const glm::mat4& Get3DPositionMatrix() const;
        const glm::mat4& Get3DRotationMatrix() const;
        const glm::mat4& Get2DPositionMatrix() const;
        const glm::mat4& Get2DRotationMatrix() const;

        const glm::mat4& Get3DViewMatrix() const;
        const glm::mat4& Get2DViewMatrix() const;
    private:
        Modifiable<glm::vec3> m_Position3D;
        Modifiable<glm::quat> m_Rotation3D;
        Modifiable<glm::vec2> m_Position2D;
        Modifiable<float> m_Rotation2D;
    };
}
