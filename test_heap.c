#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "darray.h"
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
    struct darray *a = darray_create(16);
    
    const int defseed = 0x71AFDE51;
    const int len = 1670232;

    printf("Checking if heapify_min alway produces growing sequence\n");
    printf("generating %d items in array\n", len);
    srandom(defseed);
    for (int i=0; i<len; ++i)
        darray_add(a, random() - RAND_MAX/2);

    printf("heapify min them!\n");
    
    int *data = darray_data(a);
    heapify_min(data, len);

    int min_value = INT_MIN;
    int heap_len = len;
    
    for (int value=heap_pop_min(data, &heap_len); heap_len; 
         value=heap_pop_min(data, &heap_len))
    {
        if (value < min_value)
        {
            printf("Heap returns values not in the sortered order!! min=%d new=%d\n", min_value, value);
            return;
        }
        min_value = value;
    }
    
    printf("Test passed!\n");

    darray_destroy(a);
}

void test_heap_min_3()
{
    struct darray *a = darray_create(16);
    
    const int defseed = 0x71AFDE51;
    const int len1 = 1670232;
    const int len2 = 2380232;

    printf("Checking if heapify_min/heap_push_min alway produces growing sequence\n");
    printf("generating %d items in array\n", len1);
    srandom(defseed);
    for (int i=0; i<len1; ++i)
        darray_add(a, random() - RAND_MAX/2);

    printf("heapify min them!\n");
    
    heapify_min(darray_data(a), len1);
    
    printf("adding %d items via heap_push_min\n", len2);

    // heap_push_min
    int max_len = len1+len2;
    int len = len1;

    darray_add(a, 0);
    while (heap_push_min(darray_data(a), &len, max_len, random() - RAND_MAX/2))
        darray_add(a, 0);
        
    printf("checking ...\n");

    int min_value = INT_MIN;
    int heap_len = max_len;

    int *data = darray_data(a);
    
    for (int value=heap_pop_min(data, &heap_len); heap_len; 
         value=heap_pop_min(data, &heap_len))
    {
        if (value < min_value)
        {
            printf("Heap returns values not in the sortered order!! min=%d new=%d\n", min_value, value);
            return;
        }
        min_value = value;
    }
    
    printf("Test passed!\n");

    darray_destroy(a);
}

void test_heap_max_1()
{
    int a[] = { 3, 7, 6, 1, 3 };
    const int len = sizeof(a)/sizeof(a[0]);
    
    printf("Test heap max 1\n");
    dump_array("before heapify()", a, len);
    heapify_max(a, len);
    dump_array(" after heapify()", a, len);
    
    printf("Ordering:");
    for (int clen=len; clen; )
    {
        int value = heap_pop_max(a, &clen);
        printf(" %d", value);
    }
    printf("\n");
}

void test_heap_max_2()
{
    struct darray *a = darray_create(16);
    
    const int defseed = 0x71AFDE51;
    const int len = 1670232;

    printf("Checking if heapify_max alway produces decreasing sequence\n");
    printf("generating %d items in array\n", len);
    srandom(defseed);
    for (int i=0; i<len; ++i)
        darray_add(a, random() - RAND_MAX/2);

    printf("heapify max them!\n");
    
    int *data = darray_data(a);
    heapify_max(data, len);

    int max_value = INT_MAX;
    int heap_len = len;
    
    for (int value=heap_pop_max(data, &heap_len); heap_len; 
         value=heap_pop_max(data, &heap_len))
    {
        if (value > max_value)
        {
            printf("Heap returns values not in the sortered order!! max=%d new=%d\n", max_value, value);
            return;
        }
        max_value = value;
    }
    
    printf("Test passed!\n");

    darray_destroy(a);
}

int main(int argc, char *argv[])
{
    test_heap_min_1();
    test_heap_min_2();
    test_heap_min_3();

    test_heap_max_1();
    test_heap_max_2();

    return 0;
}
