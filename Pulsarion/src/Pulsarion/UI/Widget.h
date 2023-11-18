#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

namespace Pulsarion::UI
{
    enum class DataType
    {
        Float,
        Double,
        Int32,
    };

    template<typename T>
    inline DataType GetDataType()
    {
        return DataType::Int32;
    }

    template<>
    inline DataType GetDataType<float>() { return DataType::Float; }
    template<>
    inline DataType GetDataType<double>() { return DataType::Double; }
    template<>
    inline DataType GetDataType<std::int32_t>() { return DataType::Int32; }


    class PULSARION_API Widget
    {
    public:
        virtual ~Widget() = default;

        virtual void Render() const = 0;
    };
}
