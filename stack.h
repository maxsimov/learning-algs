#pragma once

#include <stdint.h>
#include <stdbool.h>

struct stack
{
    int capacity;
    int position;
    int *data;
};

struct stack *stack_create(int capacity);
void stack_destroy(struct stack *stack);
void stack_push(struct stack *stack, intptr_t value);
bool stack_empty(struct stack *stack);
bool stack_pop(struct stack *stack, intptr_t *value);
intptr_t stack_top(struct stack *stack);
