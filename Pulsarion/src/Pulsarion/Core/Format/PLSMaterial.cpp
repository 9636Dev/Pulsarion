#include "Pulsarionpch.h"
#include "PLSMaterial.h"

// =============================
// File Format
// =============================
// Header
// uint32_t - Signature (PLSm)
// uint32_t - Version
// uint32_t - Material name length
// uint32_t - Texture name length (0 if no texture)
// =============================
// Material Data
// char* - Material name
// char* - Texture name
// float * 3 - Diffuse color
// =============================
// Footer
// uint32_t - CRC32 Checksum
// EOF - uint8_t - 0xFF
// =============================
