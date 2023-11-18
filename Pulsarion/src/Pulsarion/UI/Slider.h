#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Widget.h"

#include <array>
#include <vector>

namespace Pulsarion::UI
{
    bool PULSARION_API SliderScaleN(const std::string& text, void* data, const void* min, const void* max, const std::uint32_t dimension, const DataType dataType);

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
            m_Updated = SliderScaleN(m_Text, m_Value.data(), m_Min.data(), m_Max.data(), Dimension, GetDataType<T>());
        }

        void SetText(const std::string& text)
        {
            m_Text = text;
        }

        const std::string& GetText() const
        {
            return m_Text;
        }

        T Get(const std::uint32_t index) const
        {
            return m_Value[index];
        }

        T Set(const std::uint32_t index, const T value)
        {
            T oldValue = m_Value[index];
            m_Value[index] = value;
            m_Updated = true;
            return oldValue;
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
