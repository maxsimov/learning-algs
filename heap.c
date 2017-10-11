#include <stdbool.h>
#include "heap.h"
#include "util.h"

static inline
bool less(int a, int b, bool lt)
{
    if (lt)
        return a < b;
    else
        return b < a;
}

static inline
int left_child(int i)
{
    return 2*i+1;
}

static inline
int right_child(int i)
{
    return 2*i+2;
}

static inline
int parent(int i)
{
    return (i-1)/2;
}

static
void _sift_up(int *data, int len, bool lt)
{
    if (len < 2)
        return;
        
    int child = len-1;

    for (int root=parent(child); root>=0; root=parent(child))
    {
        if (less(data[child], data[root], lt))
            SWAP(data[child], data[root]);
        else
            break;
            
        child = root;
    }
}

static
void _sift_down(int *data, int len, int root, bool lt)
{
    for (int child=left_child(root); child<len; child=left_child(root))
    {
        int swap_index = root;
        
        if (less(data[root], data[child], lt))
            swap_index = child;

        ++child;
        if (child < len && less(data[swap_index], data[child], lt))
            swap_index = child;

        if (swap_index == root)
            break;
            
        SWAP(data[root], data[swap_index]);
        root = swap_index;
    }
}

static
void _heapify(int *data, int len, bool lt)
{
    if (len < 2)
        return;
        
    for (int i=parent(len-1); i>=0; i--)
        _sift_down(data, len, i, lt);
}

static
int _heap_pop(int *data, int *len, bool lt)
{
    int value = data[0];
    
    data[0] = data[*len - 1];
    (*len)--;
    _sift_down(data, *len, 0, lt);

    return value;
}

void heapify_min(int *data, int len)
{
    _heapify(data, len, false);
}

int heap_pop_min(int *data, int *len)
{
    return _heap_pop(data, len, false);
}

void sift_up_min(int *data, int len)
{
    _sift_up(data, len, false);
}

void sift_down_min(int *data, int len)
{
    _sift_down(data, len, 0, false);
}

void heapify_max(int *data, int len)
{
    _heapify(data, len, true);
}

int heap_pop_max(int *data, int *len)
{
    return _heap_pop(data, len, true);
}

void sift_up_max(int *data, int len)
{
    _sift_up(data, len, true);
}

void sift_down_max(int *data, int len)
{
    _sift_down(data, len, 0, true);
}
