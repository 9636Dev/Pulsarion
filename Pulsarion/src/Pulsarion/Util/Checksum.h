#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include <cstddef>
#include <cstdint>
#include <array>

namespace Pulsarion
{
    class PULSARION_API Checksum
    {
    public:
        static std::uint32_t CRC32(const std::byte* data, std::size_t size);
        static bool ValidateCRC32(const std::byte* data, std::size_t size, std::uint32_t checksum);
    private:
        static std::array<uint32_t, 256> GenerateCRC32Table();
    };
}
