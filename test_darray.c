#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "darray.h"

void test_darray_1()
{
    struct darray *a = darray_create(16);

    printf("darrary test 1\n");
    printf(" "); darray_dump(a); printf("\n");
    darray_add(a, 2);
    printf(" "); darray_dump(a); printf("\n");

    darray_destroy(a);
}

void test_darray_2()
{
    struct darray *a = darray_create(16);

    printf("darrary test 1\n");
    printf(" "); darray_dump(a); printf("\n");
    for (int i=0; i<17; ++i)
        darray_add(a, i);
    printf(" "); darray_dump(a); printf("\n");

    darray_destroy(a);
}

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

int main(int argc, char *argv[])
{
    test_darray_1();
    test_darray_2();
    test_darray_3();
    test_darray_4();
    
    return 0;
}
