#pragma once
#include <stdbool.h>

union deque_item
{
    void *data;
    int value;
};

struct deque
{
    union deque_item *items;
    int capacity;
    int head;
    int tail;
};

void deque_init(struct deque *q);
void deque_cleanup(struct deque *q);

void deque_clear(struct deque *q);
int deque_length(struct deque *q);
int deque_empty(struct deque *q);
void deque_swap(struct deque *a, struct deque *b);
void deque_copy(struct deque *dst, struct deque *src);

// queue support
void deque_push_back_int(struct deque *q, int value);
bool deque_pop_front_int(struct deque *q, int *value);

void deque_push_back_ptr(struct deque *q, void *data);
bool deque_pop_front_ptr(struct deque *q, void **data);
bool deque_peek_front_ptr(struct deque *q, void **data);

// stack support
void deque_push_front_int(struct deque *q, int value);
void deque_push_front_ptr(struct deque *q, void *data);

// complementary 
bool deque_pop_back_int(struct deque *q, int *value);
bool deque_pop_back_ptr(struct deque *q, void **data);

void deque_dump(struct deque *q, void (*p)(union deque_item *item));
