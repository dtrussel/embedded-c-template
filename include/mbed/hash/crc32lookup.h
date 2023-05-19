/**
 * @file
 * @brief CRC32 lookup header file
 */

#ifndef MBED_CRC32_H
#define MBED_CRC32_H

/**
 * @brief Double ended queue
 * @defgroup crc32lookup_api CRC32 APIs
 * @ingroup hash
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Lookup based implementation of CRC32 using polynomial 0x04C11DB7
 * 
 * @param buffer pointer to byte array
 * @param length length of byte array
 * @param init initial value of CRC32
 * @return CRC32 value
 */
uint32_t mbed_crc32lookup(const uint8_t* buffer, size_t length, uint32_t init);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif // MBED_CRC32_H
