#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "stack.h"
#include "util.h"

struct stack
{
    int capacity;
    int position;
    intptr_t *data;
};

struct stack *stack_create(int capacity)
{
    struct stack *stack = xmalloc(sizeof *stack);
    
    stack->capacity = capacity;
    stack->position = 0;
    stack->data = xmalloc(sizeof(intptr_t[capacity])); 
    
    return stack;
}

void stack_destroy(struct stack *stack)
{
    free(stack->data);
    free(stack);
}

int stack_len(struct stack *stack)
{
    return stack->position;
}

void stack_push(struct stack *stack, intptr_t value)
{
    if (stack->position >= stack->capacity)
    {
        stack->capacity = stack->capacity*2;
        stack->data = xrealloc(stack->data, sizeof(intptr_t[stack->capacity]));
    }
    
    stack->data[stack->position++] = value;
}

bool stack_empty(struct stack *stack)
{
    return stack->position == 0;
}

bool stack_pop(struct stack *stack, intptr_t *value)
{
    if (stack->position == 0)
        return false;

    *value = stack->data[--stack->position];

    return true;
}

bool stack_peek(struct stack *stack, intptr_t *value)
{
    if (stack->position == 0)
        return false;

    *value = stack->data[stack->position-1];

    return true;
}

intptr_t stack_top(struct stack *stack)
{
    return stack->data[stack->position-1];
}

int stack_capacity(struct stack *stack)
{
    return stack->capacity;
}
