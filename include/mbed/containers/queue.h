#ifndef MBED_QUEUE_H
#define MBED_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct mbed_Queue_ mbed_Queue;

struct mbed_Queue_ {
  uint8_t* buffer;
  size_t element_size; // byte size of one element
  size_t capacity; // capacity in number of elements
  volatile size_t size; // number of elements in the queue
  volatile size_t front; // index
  volatile size_t back; // index
};

mbed_Queue mbed_queue_create(uint8_t* buffer, size_t buffer_size, size_t element_size);

size_t mbed_queue_size(mbed_Queue* self);

bool mbed_queue_is_full(mbed_Queue* self);

bool mbed_queue_is_empty(mbed_Queue* self);

uint8_t* mbed_queue_push_back(mbed_Queue* self, uint8_t* element);

uint8_t* mbed_queue_push_front(mbed_Queue* self, uint8_t* element);

bool mbed_queue_pop_back(mbed_Queue* self, uint8_t* element_out);

bool mbed_queue_pop_front(mbed_Queue* self, uint8_t* element_out);

#ifdef __cplusplus
}
#endif

#endif // MBED_QUEUE_H
