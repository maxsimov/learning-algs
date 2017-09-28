#include <stdio.h>
#include "merge_sort.h"
#include "quick_sort.h"


void dump_array(const char *comment, int a[], int len)
{
    printf("%s {", comment);
    for (int i=0; i<len; ++i)
        printf(" %d", a[i]);
    printf(" }\n");
}

void test_merge_sort()
{
    printf("merge sort...\n");
    {
        int a[] = { 3, 9, 1, 7, 5 };
        int len = sizeof(a)/ sizeof(a[0]);
        dump_array("before", a, len);
        merge_sort(a, len);
        dump_array(" after", a, len);
    }

    {
        int a[] = { 9, 1 };
        int len = sizeof(a)/ sizeof(a[0]);
        dump_array("before", a, len);
        merge_sort(a, len);
        dump_array(" after", a, len);
    }

    {
        int a[] = { 9, 1, 3 };
        int len = sizeof(a)/ sizeof(a[0]);
        dump_array("before", a, len);
        merge_sort(a, len);
        dump_array(" after", a, len);
    }
    
}

void test_quick_sort()
{
    printf("quick sort...\n");
    {
        int a[] = { 4, 8, 2, 7, 5 };
        int len = sizeof(a)/ sizeof(a[0]);
        dump_array("before", a, len);
        quick_sort(a, len);
        dump_array(" after", a, len);
    }

    {
        int a[] = { 6, 2 };
        int len = sizeof(a)/ sizeof(a[0]);
        dump_array("before", a, len);
        quick_sort(a, len);
        dump_array(" after", a, len);
    }

    {
        int a[] = { 8, 2, 5 };
        int len = sizeof(a)/ sizeof(a[0]);
        dump_array("before", a, len);
        quick_sort(a, len);
        dump_array(" after", a, len);
    }
    
}

int main(int argc, char *argv[])
{
    test_merge_sort();
    test_quick_sort();
    return 0;
}