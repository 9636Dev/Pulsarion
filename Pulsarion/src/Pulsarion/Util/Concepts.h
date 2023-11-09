#pragma once

namespace Pulsarion::Util
{
    template<typename T>
    concept GLType = std::same_as<T, std::uint32_t> || std::same_as<T, std::int32_t> || std::same_as<T, float> || std::same_as<T, std::uint16_t> || std::same_as<T, std::int16_t> || std::same_as<T, std::uint8_t> || std::same_as<T, std::int8_t>;
}
