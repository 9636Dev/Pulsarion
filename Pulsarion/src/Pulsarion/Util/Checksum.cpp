#include "Pulsarionpch.h"
#include "Checksum.h"

namespace Pulsarion
{
    std::uint32_t Checksum::CRC32(const std::byte* data, std::size_t size)
    {
        static const std::array<uint32_t, 256> CRC32Table = GenerateCRC32Table();

        std::uint32_t crc = 0xFFFFFFFF;
        for (std::size_t i = 0; i < size; ++i)
        {
            crc = (crc >> 8) ^ CRC32Table[(crc ^ static_cast<std::uint8_t>(data[i])) & 0xFF];
        }
        return crc ^ 0xFFFFFFFF;
    }

    bool Checksum::ValidateCRC32(const std::byte* data, std::size_t size, std::uint32_t checksum)
    {
        return CRC32(data, size) == checksum;
    }

    std::array<uint32_t, 256> Checksum::GenerateCRC32Table()
    {
        std::array<uint32_t, 256> table;
        for (std::uint32_t i = 0; i < 256; ++i)
        {
            std::uint32_t crc = i;
            for (std::uint32_t j = 0; j < 8; ++j)
            {
                crc = (crc & 1) ? (crc >> 1) ^ 0xEDB88320 : crc >> 1;
            }
            table[i] = crc;
        }
        return table;
    }
}
