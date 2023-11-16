#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Util/Modifiable.h"
#include <glm/glm.hpp>

namespace Pulsarion
{
    struct ShaderSignature;

    class PULSARION_API Transform2D
    {
    public:
        Transform2D();
        Transform2D(const glm::dvec2& translation, const glm::dvec2& scale, double rotation);
        Transform2D(const Transform2D& other);
        Transform2D(Transform2D&& other) noexcept;

        glm::mat4 GetAsMatrix() const;

        const glm::dvec2& GetTranslation() const;
        glm::dvec2& GetTranslationRef();
        const glm::dvec2& GetScale() const;
        glm::dvec2& GetScaleRef();
        double GetRotation() const;
        void SetTranslation(const glm::dvec2& translation);
        void SetScale(const glm::dvec2& scale);
        void SetRotation(double rotation);
        bool IsDirty() const;

        ShaderSignature GetShaderSignature() const;
    private:
        mutable glm::mat4 m_Matrix;

        Modifiable<glm::dvec2> m_Translation;
        Modifiable<glm::dvec2> m_Scale;
        Modifiable<double> m_Rotation;
    };

    class Transform3D
    {
    public:

    private:
        Modifiable<glm::dvec3> m_Translation;
        Modifiable<glm::dvec3> m_Scale;
        Modifiable<glm::dquat> m_Rotation;
    };
}
