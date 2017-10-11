#pragma once

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static
inline void swap_detail(void* p1, void* p2, void* tmp, size_t sz)
{
   memcpy(tmp, p1, sz);
   memcpy(p1, p2, sz);
   memcpy(p2 , tmp, sz);
}

#define SWAP(a, b) \
        swap_detail(&(a), &(b), \
         (char[(sizeof(a) == sizeof(b)) ? (ptrdiff_t)sizeof(a) : -1]){0}, \
         sizeof(a))

void dump_array(const char *name, int a[], int len);
