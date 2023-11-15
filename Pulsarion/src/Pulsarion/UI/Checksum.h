#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

namespace Pulsarion
{
    class Checksum
    {
    public:
        static std::uint32_t CRC32(const std::uint8_t* data, std::size_t size);
        static sbool CRC32IsValid(const std::uint8_t* data, std::size_t size, std::uint32_t checksum);
    private:
        static std::array<uint32_t, 256> GenerateCRC32Table();
    };
}