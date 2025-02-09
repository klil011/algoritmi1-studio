#include "queue_private.h"
#include <stdio.h>
#include <stdlib.h>

upo_queue_node_t* upo_queue_node_create(void *data) {

    upo_queue_node_t *node = malloc(sizeof(upo_queue_node_t));
    if (node == NULL)
    {
        perror("Unable to create a node stack");
        abort();
    }

    node->data = data;
    node->next = NULL;

    return node;
}

upo_queue_t upo_queue_create() {

    upo_queue_t queue = malloc(sizeof(upo_queue_t));
    if (queue == NULL)
    {
        perror("Unable to create a stack");
        abort();
    }

    queue->head = NULL;
    queue->tail = NULL;

    queue->size = 0;

    return queue;
}

void upo_queue_destroy(upo_queue_t queue, int destroy_data) {
    
    if (queue != NULL)
    {
        upo_queue_clear(queue, destroy_data);
        free(queue);
    }
}

void upo_queue_enqueue(upo_queue_t queue, void *data) {

    if(queue != NULL) {
        
        upo_queue_node_t *nodo = upo_queue_node_create(data);
        if(queue->head == NULL) {       /*  caso in cui la coda fosse vuota  */
            
            queue->head = nodo;
            queue->tail = nodo;

            queue->size++;
            return;
        }

        upo_queue_node_t *tmp = queue->tail;
        tmp->next = nodo;
        queue->tail = nodo;

        queue->size++;
    }
}

void upo_queue_dequeue(upo_queue_t queue, int destroy_data) {

    if(queue != NULL  && !upo_queue_is_empty(queue)) {
        upo_queue_node_t *tmp = queue->head;

        if(upo_queue_size(queue) == 1) {        /*  caso in qui ci fosse un solo elemento nella coda  */
            queue->head = queue->tail = NULL;        
        }

        queue->head = queue->head->next;
        if(destroy_data != 0 && tmp->data != NULL) {
            free(tmp->data);
        }

        free(tmp);
        queue->size--;
    }
}

void *upo_queue_peek(const upo_queue_t queue) {
    
    if(queue != NULL) {
        return queue->head->data;
    }

    return NULL;
}

size_t upo_queue_size(const upo_queue_t queue) {
    
    if(queue == NULL || queue->tail == NULL) {
        return 0;
    }

    return queue->size;
}

int upo_queue_is_empty(const upo_queue_t queue) {

    if(upo_queue_size(queue) == 0) {
        return 1;
    }

    return 0;
}

void upo_queue_clear(upo_queue_t queue, int destroy_data) {

    while(queue->head != NULL) {
            upo_queue_dequeue(queue, destroy_data);
    }
    
}

