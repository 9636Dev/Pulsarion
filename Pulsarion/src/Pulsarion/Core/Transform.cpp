#include "Pulsarionpch.h"
#include "Transform.h"

namespace Pulsarion
{
    Transform2D::Transform2D()
        : Transform2D(glm::dvec2(0.0), glm::dvec2(1.0), 0.0)
    {

    }

    Transform2D::Transform2D(const glm::dvec2& translation, const glm::dvec2& scale, double rotation)
        : m_Translation(translation), m_Scale(scale), m_Rotation(rotation)
    {

    }

    Transform2D::Transform2D(const Transform2D& other) : m_Translation(other.m_Translation.GetConst()), m_Scale(other.m_Scale.GetConst()), m_Rotation(other.m_Rotation.GetConst())
    {

    }

    Transform2D::Transform2D(Transform2D&& other) noexcept : m_Translation(std::move(other.m_Translation)), m_Scale(std::move(other.m_Scale)), m_Rotation(std::move(other.m_Rotation))
    {

    }

    glm::mat3 Transform2D::GetAsMatrix() const {
        static glm::mat3 matrix = glm::mat3(1.0);
        if (IsDirty()) {
            float cosTheta = glm::cos(static_cast<float>(m_Rotation.GetConst()));
            float sinTheta = glm::sin(static_cast<float>(m_Rotation.GetConst()));
            float scaleX = static_cast<float>(m_Scale.GetConst().x);
            float scaleY = static_cast<float>(m_Scale.GetConst().y);
            float transX = static_cast<float>(m_Translation.GetConst().x);
            float transY = static_cast<float>(m_Translation.GetConst().y);

            matrix = glm::mat3(
                scaleX * cosTheta, -scaleX * sinTheta, transX,
                scaleY * sinTheta, scaleY * cosTheta, transY,
                0.0f, 0.0f, 1.0f
            );

            m_Translation.SetDirty(false);
            m_Scale.SetDirty(false);
            m_Rotation.SetDirty(false);
        }
        return matrix;
    }


    const glm::dvec2& Transform2D::GetTranslation() const
    {
        return m_Translation.GetConst();
    }

    glm::dvec2& Transform2D::GetTranslationRef()
    {
        return m_Translation.Get();
    }

    const glm::dvec2& Transform2D::GetScale() const
    {
        return m_Scale.GetConst();
    }

    glm::dvec2& Transform2D::GetScaleRef()
    {
        return m_Scale.Get();
    }

    double Transform2D::GetRotation() const
    {
        return m_Rotation.GetConst();
    }

    void Transform2D::SetTranslation(const glm::dvec2& translation)
    {
        m_Translation.Set(translation);
    }

    void Transform2D::SetScale(const glm::dvec2& scale)
    {
        m_Scale.Set(scale);
    }

    void Transform2D::SetRotation(double rotation)
    {
        m_Rotation.Set(rotation);
    }

    bool Transform2D::IsDirty() const
    {
        return m_Translation.IsDirty() || m_Scale.IsDirty() || m_Rotation.IsDirty();
    }
}
