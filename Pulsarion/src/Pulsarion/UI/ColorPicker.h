#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Widget.h"

namespace Pulsarion::UI
{
    class PULSARION_API ColorPicker4 : public Widget
    {
    public:
        ColorPicker4(const std::string& label, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        void Render() const override;

        const glm::vec4& GetColor() const;
        void SetColor(const glm::vec4& color);
        bool IsUpdated() const;
    private:
        std::string m_Label;
        mutable glm::vec4 m_Color;
        mutable bool m_IsUpdated;
    };
}
