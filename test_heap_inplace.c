#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "heap_inplace.h"
#include "util.h"

int heap_top(struct heap *h);
void heap_replace_shift(struct heap *h);


void test_heap_min_1()
{
    int a[] = { 9, 7, 3, 6, 1, 3, 2 };
    const int len = sizeof(a)/sizeof(a[0]);

    struct heap *h = heap_create(len-2);

    heap_build(h, a, 1);
    printf("After building\n");
    heap_dump(h);
    printf("Top: %d\n", heap_top(h));

    heap_shift(h);
    printf("After shift\n");
    heap_dump(h);
    printf("Top: %d\n", heap_top(h));

    heap_destroy(h);
}

int main(int argc, char *argv[])
{
    test_heap_min_1();

    return 0;
}
