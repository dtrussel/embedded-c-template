
#include "mbed/hash/crc32lookup.h"

#include <gtest/gtest.h>

TEST(crc32lookup, abcd) {
  const uint8_t message[4] = { 0x61, 0x62, 0x63, 0x64 };
  const auto crc32 = mbed_crc32lookup(message, sizeof(message), 0xFFFFFFFF);
  ASSERT_EQ(0xC2B3CCB4, crc32);
}
