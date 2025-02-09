#ifndef UPO_QUEUE_H
#define UPO_QUEUE_H

#include <stddef.h>

/** \brief Declares the Queue type. */
typedef struct upo_queue_s* upo_queue_t;

/**
 * \brief Creates a new queue.
 *
 * \return A queue.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
upo_queue_t upo_queue_create();

/**
 * \brief Destroys the given queue.
 *
 * \param queue The queue to destroy.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in this queue must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_queue_destroy(upo_queue_t queue, int destroy_data);

/**
 * \brief Removes all elements from the given queue.
 *
 * \param queue The queue.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in this stack must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_queue_clear(upo_queue_t queue, int destroy_data);

/**
 * \brief Insert the given elemente into the given queue.
 *
 * \param queue The queue.
 * \param data The new element.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_queue_enqueue(upo_queue_t queue, void * data);

/**
 * \brief Remove the next element from the given queue.
 *
 * \param queue The queue.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in this stack must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_queue_dequeue(upo_queue_t queue, int destroy_data);

/**
 * \brief Returns the next element from the given queue.
 *
 * \param queue The queue.
 * \return The element stored on the top of the stack, or `NULL` if the stack is
 *  empty.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
void *upo_queue_peek(const upo_queue_t queue);

/**
 * \brief Returns the number of elements stored in the given queue.
 *
 * \param queue The queue.
 * \return The number of elements stored in the queue, or `0` otherwise.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
size_t upo_queue_size(const upo_queue_t queue);

/**
 * \brief Tells if the given queue is empty.
 *
 * \param queue The queue.
 * \return `1` if the queue is empty or `0` otherwise.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
int upo_queue_is_empty(const upo_queue_t queue);
#endif  /* UPO_QUEUE_H */