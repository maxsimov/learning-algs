#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "deque.h"
#include "util.h"

#define MIN_CAPACITY 4

void deque_init(struct deque *q)
{
    q->items = malloc(sizeof(union deque_item)*MIN_CAPACITY);
    q->capacity = MIN_CAPACITY;
    q->head = q->tail = 0;
}

void deque_cleanup(struct deque *q)
{
    if (q == NULL)
        return;
        
    free(q->items);
    q->items = 0;
    q->capacity = 0;
    q->head = q->tail = 0;
}

void deque_clear(struct deque *q)
{
    q->head = q->tail = 0;
}

int deque_length(struct deque *q)
{
    int len = (q->tail - q->head);
    
    if (len < 0)
        len += q->capacity;

    return len;
}

int deque_empty(struct deque *q)
{
    return deque_length(q) == 0;
}

void deque_swap(struct deque *a, struct deque *b)
{
    SWAP(*a, *b);
}

static
void _deque_extend(struct deque *q)
{
    int new_capacity = q->capacity*2;
    union deque_item *new_items = malloc(sizeof(union deque_item)*new_capacity);

    int headtoend = q->capacity - q->head;        
    memcpy(new_items, &q->items[q->head], sizeof(union deque_item)*headtoend);
    memcpy(&new_items[headtoend], q->items, sizeof(union deque_item)*q->head);
        
    free(q->items);
    q->items = new_items;
    q->head = 0;
    q->tail = q->capacity;

    q->capacity = new_capacity;
}

static
union deque_item *_deque_push_back(struct deque *q)
{
    union deque_item *new_item = &q->items[q->tail];
    
    q->tail = (q->tail + 1) % q->capacity;
    
    if (q->head == q->tail)
    {
        _deque_extend(q);
        new_item = &q->items[q->tail - 1];
    }
    
    return new_item;
}

static
union deque_item *_deque_push_front(struct deque *q)
{
    q->head = q->head ? q->head-1 : q->capacity-1;

    union deque_item *new_item = &q->items[q->head];

    if (q->head == q->tail)
    {
        _deque_extend(q);
        new_item = &q->items[0];
    }

    return new_item;
}

static
union deque_item *_deque_pop_front(struct deque *q)
{
    if (q->head == q->tail)
        return 0;
    
    union deque_item *item = &q->items[q->head];
    
    q->head = (q->head + 1) % q->capacity;
    
    return item;
}

static
union deque_item *_deque_peek_front(struct deque *q)
{
    if (q->head == q->tail)
        return 0;
    
    return &q->items[q->head];
}

static
union deque_item *_deque_pop_back(struct deque *q)
{
    if (q->head == q->tail)
        return 0;
        
    q->tail = q->tail ? q->tail-1 : q->capacity-1;

    return &q->items[q->tail];
}

static 
void _deque_rebalance(struct deque *q)
{
    int len = (q->tail - q->head);
    
    if (len < 0)
        len += q->capacity;
        
    if (len >= q->capacity/2)
        return;
        
    int new_capacity = q->capacity/2;
    
    if (new_capacity < MIN_CAPACITY)
        return;
    
    union deque_item *new_items = malloc(sizeof(union deque_item)*new_capacity);
    
    if (q->head < q->tail)
    {
        memcpy(new_items, &q->items[q->head], sizeof(union deque_item)*(q->tail - q->head));
    } else {
        int lenbeforeend = q->capacity - q->head;
        memcpy(new_items, &q->items[q->head], sizeof(union deque_item)*lenbeforeend);
        memcpy(&new_items[lenbeforeend], &q->items[0], sizeof(union deque_item)*q->tail);
    }
    
    free(q->items);
    q->items = new_items;
    q->head = 0;
    q->tail = len;

    q->capacity = new_capacity;
}

void deque_push_back_int(struct deque *q, int value)
{
    union deque_item *item = _deque_push_back(q);
    item->value = value;
}

void deque_push_back_ptr(struct deque *q, void *data)
{
    union deque_item *item = _deque_push_back(q);
    item->data = data;
}

void deque_push_front_int(struct deque *q, int value)
{
    union deque_item *item = _deque_push_front(q);
    item->value = value;
}

void deque_push_front_ptr(struct deque *q, void *data)
{
    union deque_item *item = _deque_push_front(q);
    item->data = data;
}

bool deque_pop_front_int(struct deque *q, int *value)
{
    union deque_item *item = _deque_pop_front(q);
    
    if (!item)
        return false;
        
    *value = item->value;
    
    _deque_rebalance(q);
    
    return true;
}

bool deque_pop_front_ptr(struct deque *q, void **data)
{
    union deque_item *item = _deque_pop_front(q);
    
    if (!item)
        return false;
        
    *data = item->data;
    
    _deque_rebalance(q);
    
    return true;
}

bool deque_peek_front_ptr(struct deque *q, void **data)
{
    union deque_item *item = _deque_peek_front(q);
    
    if (!item)
        return false;
        
    *data = item->data;

    return true;
}

bool deque_pop_back_int(struct deque *q, int *value)
{
    union deque_item *item = _deque_pop_back(q);
    
    if (!item)
        return false;
        
    *value = item->value;
    
    _deque_rebalance(q);
    
    return true;

}

bool deque_pop_back_ptr(struct deque *q, void **data)
{
    union deque_item *item = _deque_pop_back(q);
    
    if (!item)
        return false;
        
    *data = item->data;
    
    _deque_rebalance(q);
    
    return true;
}

void deque_copy(struct deque *dst, struct deque *src)
{
    if (dst->capacity <= deque_length(src))
    {
        free(dst->items);
        
        int new_capacity = src->capacity*2;
        dst->items = malloc(sizeof(union deque_item)*new_capacity);
        dst->capacity = new_capacity;
        dst->head = dst->tail = 0;
    } else {
        dst->head = dst->tail = 0;
    }

    if (src->head < src->tail)
    {
        dst->tail = src->tail - src->head;
        memcpy(dst->items, &src->items[src->head], sizeof(union deque_item)*(dst->tail));
    } else {
        int lenbeforeend = src->capacity - src->head;
        memcpy(dst->items, &src->items[src->head], sizeof(union deque_item)*lenbeforeend);
        memcpy(&dst->items[lenbeforeend], &src->items[0], sizeof(union deque_item)*src->tail);
        dst->tail = lenbeforeend + src->tail;
    }
}

void deque_dump(struct deque *q, void (*p)(union deque_item *item))
{
    printf("Q {");
    for (int cur=q->head; cur != q->tail; cur = (cur+1) % q->capacity )
    {
        printf(" ");
        p(&q->items[cur]);
    }
    printf(" }\n");
}
