#pragma once

#include <stdint.h>
#include <stdbool.h>

struct stack *stack_create(int capacity);
void stack_destroy(struct stack *stack);
int stack_capacity(struct stack *stack);
void stack_push(struct stack *stack, intptr_t value);
bool stack_empty(struct stack *stack);
bool stack_pop(struct stack *stack, intptr_t *value);
bool stack_peek(struct stack *stack, intptr_t *value);
int stack_len(struct stack *stack);
intptr_t stack_top(struct stack *stack);
