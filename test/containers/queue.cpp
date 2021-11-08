#include "mbed/containers/queue.h"

#include <gtest/gtest.h>

extern "C" {

typedef struct Message_ Message;
struct Message_ {
  char header;
  uint32_t value;
  char footer;
};

} // extern "C"

TEST(queue, create) {
  Message buffer[5];
  mbed_Queue queue = mbed_queue_create((uint8_t*)buffer, 5, sizeof(Message));
  ASSERT_EQ(0, mbed_queue_size(&queue));
  ASSERT_TRUE(mbed_queue_is_empty(&queue));
}

TEST(queue, push_back) {
  Message buffer[5];
  mbed_Queue queue = mbed_queue_create((uint8_t*)buffer, 5, sizeof(Message));
  Message msg;
  msg.header = 'a';
  msg.value = 42;
  msg.footer = 'b';
  mbed_queue_push_back(&queue, (uint8_t*)&msg);
  ASSERT_EQ(1, mbed_queue_size(&queue));
  ASSERT_FALSE(mbed_queue_is_empty(&queue));
  Message out;
  mbed_queue_pop_back(&queue, (uint8_t*)&out);
  ASSERT_EQ('a', out.header);
}
