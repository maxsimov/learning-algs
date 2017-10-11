#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"
#include "util.h"

void test_heap_min_1()
{
    int a[] = { 7, 3, 6, 1, 3 };
    const int len = sizeof(a)/sizeof(a[0]);
    
    printf("Test heap min 1\n");
    dump_array("before heapify()", a, len);
    heapify_min(a, len);
    dump_array(" after heapify()", a, len);
    
    printf("Ordering:");
    for (int clen=len; clen; )
    {
        int value = heap_pop_min(a, &clen);
        printf(" %d", value);
    }
    printf("\n");
}

void test_heap_min_2()
{
}


/*
void test_darray_3()
{
    struct darray *a = darray_create(16);
    
    const int defseed = 0x71AFDE51;
    const int maxnum = 1670232;

    printf("inserting %d items\n", maxnum);
    srandom(defseed);
    for (int i=0; i<maxnum; ++i)
        darray_add(a, random());
    printf("verify %d items\n", maxnum);
    srandom(defseed);
    for (int i=0; i<maxnum; ++i)
        if (darray_get(a, i) != random())
            {
                printf(" ! FAILED!\n");
                return;
            }
    printf("all %d values are correct!\n", maxnum);

    darray_destroy(a);
}

void test_darray_4()
{
    struct darray *a = darray_create(16);

    printf("darrary test 4\n");
    for (int i=0; i<17; ++i)
        darray_add(a, i);
    printf(" "); darray_dump(a); printf("\n");
    darray_truncate(a, 7);
    printf(" "); darray_dump(a); printf("\n");

    darray_destroy(a);
}
*/

int main(int argc, char *argv[])
{
    test_heap_min_1();

    return 0;
}
