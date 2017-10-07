#pragma once

struct stack
{
    int *data;
    int capacity;
    int position;
};

bool stack_init(struct stack *stack, int capacity);
void stack_cleanup(struct stack *stack);
void stack_push(struct stack *stack, int value);
bool stack_empty(struct stack *stack);
bool stack_pop(struct stack *stack, int *value);
int stack_top(struct stack *stack);
