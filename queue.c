#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

struct queue
{
    int capacity;
    int head;
    int tail;
    intptr_t *data;
};

struct queue *queue_create(int capacity)
{
    struct queue *q = malloc(sizeof(*q));

    if (!q)
        return 0;
        
    q->data = malloc(sizeof(intptr_t[capacity]));
    
    if (!q->data)
    {
        free(q);
        return 0;
    }
    
    q->capacity = capacity;
    q->head = 0;
    q->tail = 0;

    return q;
}

void queue_destroy(struct queue *q)
{
    free(q->data);
    free(q);
}

void queue_enque(struct queue *queue, intptr_t value)
{
    queue->data[queue->tail++] = value;

    if (queue->tail == queue->capacity)
        queue->tail = 0;

    if (queue->head == queue->tail)
    {
        int new_capacity = queue->capacity*2;
        intptr_t *new_data = malloc(sizeof(intptr_t[new_capacity]));

        int elements_in_end = queue->capacity - queue->head;
        memcpy(new_data, &queue->data[queue->head], sizeof(intptr_t)*elements_in_end);
        memcpy(&new_data[elements_in_end], queue->data, sizeof(intptr_t)*queue->tail);
        
        free(queue->data);
        queue->data = new_data;
        queue->head = 0;
        queue->tail = queue->capacity;
        queue->capacity = new_capacity;
    }
}

bool queue_empty(struct queue *queue)
{
    return queue->tail == queue->head;
}

bool queue_deque(struct queue *queue, intptr_t *value)
{
    if (queue->tail == queue->head)
        return false;
        
    *value = queue->data[queue->head++];
    
    if (queue->head == queue->capacity)
        queue->head = 0;

    return true;
}

intptr_t queue_top(struct queue *queue)
{
    return queue->data[queue->head];
}

void queue_print(struct queue *queue)
{
    printf("{\n");
    printf("  capacity = %d\n", queue->capacity);
    printf("  head = %d\n", queue->head);
    printf("  tail = %d\n", queue->tail);
    printf("  data =");
    for (int i=queue->head; i != queue->tail; )
    {
        printf(" %d", (int) queue->data[i]);
        if (++i == queue->capacity)
            i = 0;
    }
    printf("\n");

    printf("}\n");
}
