#include <stdio.h>
#include "merge_sort.h"


void dump_array(const char *comment, int a[], int len)
{
    printf("%s {", comment);
    for (int i=0; i<len; ++i)
        printf(" %d", a[i]);
    printf(" }\n");
}

void test_merge_sort()
{
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

int main(int argc, char *argv[])
{
    test_merge_sort();
    return 0;
}