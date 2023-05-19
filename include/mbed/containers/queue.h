/**
 * @file
 * @brief Double ended queue header file
 */

#ifndef MBED_QUEUE_H
#define MBED_QUEUE_H

/**
 * @brief Double ended queue
 * @defgroup queue_api Queue APIs
 * @ingroup containers
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define UNUSED(x) ((void)x)

/**
 * @brief Simple double ended queue implementation
 * 
 */
typedef struct mbed_Queue_ mbed_Queue;

struct mbed_Queue_ {
  uint8_t* buffer; //  non-owning pointer to underlying buffer
  size_t element_size; /// byte size of one element
  size_t capacity; /// capacity in number of elements
  volatile size_t size; /// number of elements in the queue
  volatile size_t front; /// index
  volatile size_t back; /// index
};

/**
 * @brief Constructor for a mbed_Queue
 * 
 * @param buffer pointer to buffer that the queue shall use (queue will not take ownership)
 * @param buffer_size size of the passed buffer
 * @param element_size byte size of the elements that shall be stored in the queue
 * @return mbed_Queue 
 */
mbed_Queue mbed_queue_create(uint8_t* buffer, size_t buffer_size, size_t element_size);

/**
 * @param self pointer to mbed_Queue instance
 * @return number of elements in the queue
 */
size_t mbed_queue_size(mbed_Queue* self);

/**
 * @param self pointer to mbed_Queue instance
 * @return true queue can not store another element
 * @return false queue can store another element
 */
bool mbed_queue_is_full(mbed_Queue* self);

bool mbed_queue_is_empty(mbed_Queue* self);

/**
 * @brief copies an element to the back of the queue
 * 
 * @param self pointer to mbed_Queue instance
 * @param element pointer to element to be copied
 * @return pointer to where the element was copied
 */
uint8_t* mbed_queue_push_back(mbed_Queue* self, uint8_t* element);

/**
 * @brief copies an element to the front of the queue
 *
 * @param self pointer to mbed_Queue instance
 * @param element pointer to element to be copied
 * @return pointer to where the element was copied
 */
uint8_t* mbed_queue_push_front(mbed_Queue* self, uint8_t* element);

/**
 * @brief copies an element from the queue to the provided location
 * 
 * @param self pointer to mbed_Queue instance
 * @param element_out pointer to where element will be copied
 * @return true if successful
 * @return false if queue is empty
 */
bool mbed_queue_pop_back(mbed_Queue* self, uint8_t* element_out);

bool mbed_queue_pop_front(mbed_Queue* self, uint8_t* element_out);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif // MBED_QUEUE_H
