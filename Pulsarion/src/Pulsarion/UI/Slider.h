#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Widget.h"

#include <imgui.h>
#include <array>

namespace Pulsarion::UI
{
    template<typename T, std::uint32_t Dimension>
    class Slider : public Widget
    {
    public:
        Slider(const std::string& text, const std::array<T, Dimension>& min, const std::array<T, Dimension>& max, const std::array<T, Dimension>& value)
            : m_Text(text), m_Min(min), m_Max(max), m_Value(value), m_Updated(false)
        {

        }

        ~Slider()
        {

        }

        void Render() const override
        {
            m_Updated = ImGui::SliderScalarN(m_Text.c_str(), GetImGuiDataType<T>(), m_Value.data(), Dimension, m_Min.data(), m_Max.data());
        }

        void SetText(const std::string& text)
        {
            m_Text = text;
        }

        const std::string& GetText() const
        {
            return m_Text;
        }


        const std::array<T, Dimension>& GetMin() const
        {
            return m_Min;
        }

        const std::array<T, Dimension>& GetMax() const
        {
            return m_Max;
        }

        void SetValue(const std::array<T, Dimension>& value)
        {
            m_Value = value;
        }

        const std::array<T, Dimension>& GetValue() const
        {
            return m_Value;
        }

        bool IsUpdated() const
        {
            return m_Updated;
        }
    protected:
        std::string m_Text;
        std::array<T, Dimension> m_Min;
        std::array<T, Dimension> m_Max;
        mutable std::array<T, Dimension> m_Value;
        mutable bool m_Updated;
    };

    using Slider1f = Slider<float, 1>;
    using Slider2f = Slider<float, 2>;
    using Slider3f = Slider<float, 3>;
    using Slider4f = Slider<float, 4>;
    using Slider1d = Slider<double, 1>;
    using Slider2d = Slider<double, 2>;
    using Slider3d = Slider<double, 3>;
    using Slider4d = Slider<double, 4>;
    using Slider1i = Slider<std::int32_t, 1>;
    using Slider2i = Slider<std::int32_t, 2>;
    using Slider3i = Slider<std::int32_t, 3>;
    using Slider4i = Slider<std::int32_t, 4>;
}
