#pragma once
#include <stdbool.h>

struct darray *darray_create(int capacity);
void darray_destroy(struct darray *a);

int *darray_data(struct darray *a);
int darray_get(struct darray *a, int index);
void darray_set(struct darray *a, int index, int value);
int darray_length(struct darray *a);
bool darray_add(struct darray *a, int value);
bool darray_remove_last(struct darray *a, int *value);
void darray_truncate(struct darray *a, int newlen);
void darray_clear(struct darray *a);
void darray_copy(struct darray *dst, struct darray *src);
void darray_merge(struct darray *dst, struct darray *src);
int darray_to_buffer(struct darray *a, int *data, int maxlen);
void darray_print(struct darray *a);
void darray_dump(struct darray *a);
