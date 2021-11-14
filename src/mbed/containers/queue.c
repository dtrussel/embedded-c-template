#include "mbed/containers/queue.h"

#include <string.h>

mbed_Queue mbed_queue_create(uint8_t* buffer, const size_t buffer_size, const size_t element_size) {
    mbed_Queue ret;
    ret.buffer = buffer;
    ret.element_size = element_size;
    ret.capacity = buffer_size;
    ret.size = 0;
    ret.front = 0;
    ret.back = 0;
    return ret;
}

size_t mbed_queue_size(mbed_Queue* self) {
  return self->size;
}

bool mbed_queue_is_full(mbed_Queue* self) {
  return self->size >= self->capacity;
}

bool mbed_queue_is_empty(mbed_Queue* self) {
  return 0 == self->size;
}

static void increment_back(mbed_Queue* self) {
  size_t next = self->back + 1;
  if (next == self->capacity) {
    next = 0;
  }
  self->back = next;
}

static void decrement_back(mbed_Queue* self) {
  size_t next = self->back - 1;
  if (next > self->capacity) {
    next = self->capacity - 1;
  }
  self->back = next;
}

static void increment_front(mbed_Queue* self) {
  size_t next = self->front + 1;
  if (next == self->capacity) {
    next = 0;
  }
  self->front = next;
}

static void decrement_front(mbed_Queue* self) {
  size_t next = self->front - 1;
  if (next > self->capacity) {
    next = self->capacity - 1;
  }
  self->front = next;
}

uint8_t* mbed_queue_push_back(mbed_Queue* self, uint8_t* element) {
  if (mbed_queue_is_full(self)) {
    return NULL;
  }
  const size_t offset = self->back * self->element_size;
  uint8_t* destination = self->buffer + offset;
  memcpy(destination, element, self->element_size);
  increment_back(self);
  self->size++;
  return destination;
}

uint8_t* mbed_queue_push_front(mbed_Queue* self, uint8_t* element) {
  if (mbed_queue_is_full(self)) {
    return NULL;
  }
  decrement_front(self);
  const size_t offset = self->front * self->element_size;
  uint8_t* destination = self->buffer + offset;
  memcpy(destination, element, self->element_size);
  self->size++;
  return element;
}

bool mbed_queue_pop_back(mbed_Queue* self, uint8_t* element_out){
  if (mbed_queue_is_empty(self)) {
    return false;
  }
  decrement_back(self);
  const size_t offset = self->back * self->element_size;
  uint8_t* source = self->buffer + offset;
  memcpy(element_out, source, self->element_size);
  self->size--;
  return true;
}

bool mbed_queue_pop_front(mbed_Queue* self, uint8_t* element_out){
  if (mbed_queue_is_empty(self)) {
    return false;
  }
  const size_t offset = self->front * self->element_size;
  uint8_t* source = self->buffer + offset;
  memcpy(element_out, source, self->element_size);
  increment_front(self);
  self->size--;
  return true;
}
