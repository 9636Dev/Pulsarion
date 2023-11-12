#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Widget.h"

namespace Pulsarion::UI
{
    // TODO: Rewrite using click and hover callbacks
    class Button : public Widget
    {
    public:
        Button(const std::string& text);
        ~Button();

        void Render() const override;
        void SetText(const std::string& text);
        const std::string& GetText() const;
        bool IsPressed() const;
    private:
        std::string m_Text;
        mutable bool m_Pressed;
    };
}
