#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "stack.h"
#include "util.h"

struct stack *stack_create(int capacity)
{
    struct stack *stack = xmalloc(sizeof *stack);
    
    stack->capacity = capacity;
    stack->position = 0;
    stack->data = xmalloc(sizeof(stack->data[0])*capacity); 
    
    return stack;
}

void stack_destroy(struct stack *stack)
{
    free(stack->data);
    free(stack);
}

void stack_push(struct stack *stack, intptr_t value)
{
    if (stack->position >= stack->capacity)
    {
        stack->capacity = stack->capacity*2;
        stack->data = realloc(stack->data, stack->capacity);
        assert(stack->data);
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

intptr_t stack_top(struct stack *stack)
{
    return stack->data[stack->position-1];
}

