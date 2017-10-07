#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "stack.h"

bool stack_init(struct stack *stack, int capacity)
{
    stack->capacity = capacity;
    stack->position = 0;
    stack->data = malloc(capacity*sizeof(stack->data[0])); 
    
    return stack->data;
}

void stack_cleanup(struct stack *stack)
{
    free(stack->data);
}

void stack_push(struct stack *stack, int value)
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

bool stack_pop(struct stack *stack, int *value)
{
    if (stack->position == 0)
        return false;

    *value = stack->data[--stack->position];

    return true;
}

int stack_top(struct stack *stack)
{
    return stack->data[stack->position-1];
}

