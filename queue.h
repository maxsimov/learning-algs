#pragma once

#include <stdint.h>
#include <stdbool.h>

struct queue *queue_create(int capacity);
void queue_destroy(struct queue *queue);
void queue_enque(struct queue *queue, intptr_t value);
bool queue_empty(struct queue *queue);
bool queue_deque(struct queue *queue, intptr_t *value);
intptr_t queue_top(struct queue *queue);
void queue_print(struct queue *queue);
