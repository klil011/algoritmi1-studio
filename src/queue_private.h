#ifndef UPO_QUEUE_PRIVATE_H
#define UPO_QUEUE_PRIVATE_H

#include <stddef.h>
#include <upo/queue.h>

/** \brief Defines the structure of each node of the singly-linked list implementing the queue. */
struct upo_queue_node_s
{
    void *data; /**< User-provided data. */
    struct upo_queue_node_s *next; /**< Pointer to the next node in the list. */
};
typedef struct upo_queue_node_s upo_queue_node_t;

/** \brief Defines the structure of the list implementing the stack. */
struct upo_queue_s
{
    upo_queue_node_t *head; /**< The front of the list. */
    upo_queue_node_t *tail; /**< The end of the list. */
    size_t size;    /**< The size of the list. This field allows to guarantee a constant complexity for the `size` operation. */
};


#endif  /* UPO_QUEUE_PRIVATE_H */