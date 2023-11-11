#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Widget.h"

namespace Pulsarion::UI
{
    class PULSARION_API Text : public Widget
    {
    public:
        Text(const std::string& text);
        ~Text();

        void SetText(const std::string& text);
        const std::string& GetText() const;

        void SetColor(const glm::vec4& color);
        const glm::vec4& GetColor() const;

        void Render() const override;
    private:
        std::string m_Text;
        glm::vec4 m_Color;
    };
}
