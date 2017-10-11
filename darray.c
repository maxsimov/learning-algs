#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "darray.h"

struct darray
{
    int *data;
    int len;
    int capacity;
};

struct darray *darray_create(int capacity)
{
    struct darray *a = malloc(sizeof(*a));
    a->data = malloc(sizeof(*a->data)*capacity);
    a->len = 0;
    a->capacity = capacity;

    return a;
}

void darray_destroy(struct darray *a)
{
    free(a->data);
    free(a);
}

int *darray_data(struct darray *a)
{
    return a->data;
}

void _optimize_space(struct darray *a)
{
    if (a->capacity <= 16)
        return;
    
    int freespace = a->capacity - a->len;
    
    if ((freespace-a->len) < 16)
        return;
        
    freespace = a->len;
    if (freespace < 16)
        freespace = 16;
        
    int *nd = realloc(a->data, freespace*sizeof(a->data[0]));
    
    if (!nd)
        return;
        
    a->capacity = freespace;
    a->data = nd;
}

int darray_get(struct darray *a, int index)
{
    if (index < a->len)
        return a->data[index];
    
    return -1;
}

void darray_set(struct darray *a, int index, int value)
{
    if (index < a->len)
        a->data[index] = value;
}

int darray_length(struct darray *a)
{
    return a->len;    
}

bool _darray_add_capacity(struct darray *a, int newcapacity)
{
    int *newdata = realloc(a->data, sizeof(a->data[0])*newcapacity);
    if (!newdata)
        return false;
    a->capacity = newcapacity;
    a->data = newdata;
    
    return true;
}

bool darray_add(struct darray *a, int value)
{
    if (a->len == a->capacity)
    {
        if (!_darray_add_capacity(a, a->capacity*2))
            return false;
    }
    
    a->data[a->len++] = value;
    return true;
}

bool darray_remove_last(struct darray *a, int *value)
{
    if (!a->len)
        return false;
    
    a->len--;
    
    if (value)
        *value = a->data[a->len];
        
    _optimize_space(a);
    
    return true;
}

void darray_truncate(struct darray *a, int newlen)
{
    if (newlen > a->len)
        return;
    a->len = newlen;
    _optimize_space(a);
}

void darray_clear(struct darray *a)
{
    a->len = 0;
    _optimize_space(a);
}

void darray_copy(struct darray *dst, struct darray *src)
{
    free(dst->data);
    dst->len = src->len;
    dst->capacity = src->capacity;
    dst->data = malloc(sizeof(dst->data[0])*src->capacity);
    memcpy(dst->data, src->data, dst->data[0]*dst->len);
}

void darray_merge(struct darray *dst, struct darray *src)
{
    int newlen = dst->len + src->len;
    if (newlen > dst->capacity)
    {
        int maxcap = dst->capacity < src->capacity ? src->capacity : dst->capacity;

        if (_darray_add_capacity(dst, maxcap*2))
            return;
    }
    
    memcpy(&dst->data[dst->len], src->data, src->len);
    dst->len = newlen;
}

int darray_to_buffer(struct darray *a, int *data, int maxlen)
{
    int len = a->len < maxlen ? a->len : maxlen;
    
    memcpy(data, a->data, len*sizeof(a->data[0]));
    
    return a->len;
}

void darray_print(struct darray *a)
{
    printf("{");
    for (int i=0; i<a->len; ++i)
        printf(" %d", a->data[i]);
    printf(" }");
}

void darray_dump(struct darray *a)
{
    printf("{");
    printf(" capacity=%d len=%d", a->capacity, a->len);
    printf(" {");
    for (int i=0; i<a->len; ++i)
        printf(" %d", a->data[i]);
    printf(" }");
    printf(" }");
    
}
