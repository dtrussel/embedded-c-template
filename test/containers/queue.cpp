#include "mbed/containers/queue.h"

#include <gtest/gtest.h>

namespace queue {

extern "C" {

typedef struct Message_ Message;
struct Message_ {
  char header;
  uint32_t value;
  char footer;
};

} // extern "C"

constexpr size_t QUEUE_SIZE = 7;

struct QueueTest : ::testing::Test {

  void SetUp() override {
     queue_ = mbed_queue_create((uint8_t*)buffer_, QUEUE_SIZE, sizeof(Message));
  }

  Message buffer_[QUEUE_SIZE];
  mbed_Queue queue_;
};

TEST_F(QueueTest, create) {
  ASSERT_EQ(0, mbed_queue_size(&queue_));
  ASSERT_TRUE(mbed_queue_is_empty(&queue_));
}

TEST_F(QueueTest, push_back_and_pop_back) {
  Message msg;
  msg.header = 'a';
  msg.value = 42;
  msg.footer = 'b';
  uint8_t* inserted = mbed_queue_push_back(&queue_, (uint8_t*)&msg);
  ASSERT_NE(nullptr, inserted);
  ASSERT_EQ(1, mbed_queue_size(&queue_));
  ASSERT_FALSE(mbed_queue_is_empty(&queue_));
  Message out;
  ASSERT_TRUE(mbed_queue_pop_back(&queue_, (uint8_t*)&out));
  ASSERT_TRUE(mbed_queue_is_empty(&queue_));
  ASSERT_EQ('a', out.header);
  ASSERT_EQ(42, out.value);
  ASSERT_EQ('b', out.footer);
}

TEST_F(QueueTest, push_front_and_pop_front) {
  Message msg;
  msg.header = 'a';
  msg.value = 42;
  msg.footer = 'b';
  uint8_t* inserted = mbed_queue_push_front(&queue_, (uint8_t*)&msg);
  ASSERT_NE(nullptr, inserted);
  ASSERT_EQ(1, mbed_queue_size(&queue_));
  ASSERT_FALSE(mbed_queue_is_empty(&queue_));
  Message out;
  ASSERT_TRUE(mbed_queue_pop_front(&queue_, (uint8_t*)&out));
  ASSERT_EQ('a', out.header);
  ASSERT_EQ(42, out.value);
  ASSERT_EQ('b', out.footer);
}

TEST_F(QueueTest, push_back_and_pop_front) {
  Message msg;
  msg.header = 'a';
  msg.value = 42;
  msg.footer = 'b';
  uint8_t* inserted = mbed_queue_push_back(&queue_, (uint8_t*)&msg);
  ASSERT_NE(nullptr, inserted);
  ASSERT_EQ(1, mbed_queue_size(&queue_));
  ASSERT_FALSE(mbed_queue_is_empty(&queue_));
  Message out;
  ASSERT_TRUE(mbed_queue_pop_front(&queue_, (uint8_t*)&out));
  ASSERT_EQ('a', out.header);
  ASSERT_EQ(42, out.value);
  ASSERT_EQ('b', out.footer);
}

TEST_F(QueueTest, push_front_and_pop_back) {
  Message msg;
  msg.header = 'a';
  msg.value = 42;
  msg.footer = 'b';
  uint8_t* inserted = mbed_queue_push_back(&queue_, (uint8_t*)&msg);
  ASSERT_NE(nullptr, inserted);
  ASSERT_EQ(1, mbed_queue_size(&queue_));
  ASSERT_FALSE(mbed_queue_is_empty(&queue_));
  Message out;
  ASSERT_TRUE(mbed_queue_pop_back(&queue_, (uint8_t*)&out));
  ASSERT_EQ('a', out.header);
  ASSERT_EQ(42, out.value);
  ASSERT_EQ('b', out.footer);
}

TEST_F(QueueTest, push_back_until_full_then_pop_back_until_empty) {
  Message msg;
  msg.header = 'a';
  msg.footer = 'b';
  for (uint32_t iter = 0; iter < QUEUE_SIZE; ++iter) {
    msg.value = iter;
    uint8_t* inserted = mbed_queue_push_back(&queue_, (uint8_t*)&msg);
    ASSERT_NE(nullptr, inserted);
    ASSERT_EQ(1 + iter, mbed_queue_size(&queue_));
    ASSERT_FALSE(mbed_queue_is_empty(&queue_));
  }
  ASSERT_TRUE(mbed_queue_is_full(&queue_));
  Message out;
  for (uint32_t iter = QUEUE_SIZE; iter > 0; --iter) {
    ASSERT_TRUE(mbed_queue_pop_back(&queue_, (uint8_t*)&out));
    ASSERT_EQ('a', out.header);
    ASSERT_EQ(iter - 1, out.value);
    ASSERT_EQ('b', out.footer);
    ASSERT_EQ(iter - 1, mbed_queue_size(&queue_));
  }
  ASSERT_TRUE(mbed_queue_is_empty(&queue_));
}

TEST_F(QueueTest, push_back_until_full_then_pop_front_until_empty) {
  Message msg;
  msg.header = 'a';
  msg.footer = 'b';
  for (uint32_t iter = 0; iter < QUEUE_SIZE; ++iter) {
    msg.value = iter;
    uint8_t* inserted = mbed_queue_push_back(&queue_, (uint8_t*)&msg);
    ASSERT_NE(nullptr, inserted);
    ASSERT_EQ(1 + iter, mbed_queue_size(&queue_));
    ASSERT_FALSE(mbed_queue_is_empty(&queue_));
  }
  ASSERT_TRUE(mbed_queue_is_full(&queue_));
  Message out;
  for (uint32_t iter = 0; iter < QUEUE_SIZE; ++iter) {
    ASSERT_TRUE(mbed_queue_pop_front(&queue_, (uint8_t*)&out));
    ASSERT_EQ('a', out.header);
    ASSERT_EQ(iter, out.value);
    ASSERT_EQ('b', out.footer);
    ASSERT_EQ(QUEUE_SIZE - iter - 1, mbed_queue_size(&queue_));
  }
  ASSERT_TRUE(mbed_queue_is_empty(&queue_));
}

TEST_F(QueueTest, alternate_push_back_and_pop_front_until_wrapped_twice) {
  Message msg;
  msg.header = 'a';
  msg.footer = 'b';
  for (uint32_t iter = 0; iter < QUEUE_SIZE * 2; ++iter) {
    msg.value = iter;
    uint8_t* inserted = mbed_queue_push_back(&queue_, (uint8_t*)&msg);
    ASSERT_NE(nullptr, inserted);
    ASSERT_EQ(1, mbed_queue_size(&queue_));
    ASSERT_FALSE(mbed_queue_is_empty(&queue_));
    ASSERT_FALSE(mbed_queue_is_full(&queue_));
    Message out;
    ASSERT_TRUE(mbed_queue_pop_front(&queue_, (uint8_t*)&out));
    ASSERT_EQ('a', out.header);
    ASSERT_EQ(iter, out.value);
    ASSERT_EQ('b', out.footer);
    ASSERT_EQ(0, mbed_queue_size(&queue_));
    ASSERT_TRUE(mbed_queue_is_empty(&queue_));
    ASSERT_FALSE(mbed_queue_is_full(&queue_));
  }
}

} // namespace queue
