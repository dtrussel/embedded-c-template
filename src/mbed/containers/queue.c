#include "mbed/containers/queue.h"

#include <string.h>

mbed_Queue mbed_queue_create(uint8_t* buffer, const size_t buffer_size, const size_t element_size) {
    mbed_Queue ret;
    ret.buffer = buffer;
    ret.capacity = buffer_size;
    ret.front = 0;
    ret.back = 0;
    ret.element_size = element_size;
    return ret;
}

size_t mbed_queue_size(mbed_Queue* self){
  const bool is_wrapped_around = self->back < self->front;
  size_t ret;
  if (is_wrapped_around) {
    ret = self->capacity - (self->front - self->back);
  } else {
    ret =  self->back - self->front; 
  }
  return ret;
}

bool mbed_queue_is_full(mbed_Queue* self) {
  return mbed_queue_size(self) == self->capacity;
}

bool mbed_queue_is_empty(mbed_Queue* self) {
  return self->back == self->front;
}

#define INCREMENT(queue, index) queue->index = (queue->index + 1) % queue->capacity
#define DECREMENT(queue, index) queue->index = (queue->capacity + queue->index - 1) % queue->capacity

uint8_t* mbed_queue_push_back(mbed_Queue* self, uint8_t* element) {
  if (mbed_queue_is_full(self)) {
    return NULL;
  }
  size_t offset = self->back * self->element_size;
  INCREMENT(self, back);
  uint8_t* destination = self->buffer + offset;
  memcpy(destination, element, self->element_size);
  return destination;
}

uint8_t* mbed_queue_push_front(mbed_Queue* self, uint8_t* element) {
  if (mbed_queue_is_full(self)) {
    return NULL;
  }
  DECREMENT(self, front);
  size_t offset = self->front * self->element_size;
  uint8_t* destination = self->buffer + offset;
  memcpy(destination, element, self->element_size);
  return element;
}

bool mbed_queue_pop_back(mbed_Queue* self, uint8_t* element_out){
  if (mbed_queue_is_empty(self)) {
    return false;
  }
  DECREMENT(self, back);
  size_t offset = self->back * self->element_size;
  uint8_t* source = self->buffer + offset;
  memcpy(element_out, source, self->element_size);
  return true;
}

bool mbed_queue_pop_front(mbed_Queue* self, uint8_t* element_out){
  if (mbed_queue_is_empty(self)) {
    return false;
  }
  size_t offset = self->front * self->element_size;
  INCREMENT(self, front);
  uint8_t* source = self->buffer + offset;
  memcpy(element_out, source, self->element_size);
  return true;
}
