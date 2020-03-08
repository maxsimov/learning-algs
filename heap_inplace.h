#pragma once

struct heap *heap_create(int size);
void heap_destroy(struct heap *h);
void heap_build(struct heap *h, int *nums, int indexBase);
int heap_top(struct heap *h);
void heap_shift(struct heap *h);
void heap_dump(struct heap *h);
