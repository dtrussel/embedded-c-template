#ifndef MBED_CRC32_H
#define MBED_CRC32_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

uint32_t mbed_crc32lookup(const uint8_t* buffer, size_t length, uint32_t init);

#ifdef __cplusplus
}
#endif

#endif