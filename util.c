#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void dump_array(const char *name, int a[], int len)
{
    printf("%s {", name);
    for (int i=0; i<len; ++i)
        printf(" %d", a[i]);
    printf(" }\n");
}

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    
    if (!ptr)
        die("out of memory");
        
    return ptr;
}

void die(const char *msg)
{
    printf("Fatal error: %s\n", msg);
    exit(2);
}
