#include <stdio.h>
#include "util.h"

void dump_array(const char *name, int a[], int len)
{
    printf("%s {", name);
    for (int i=0; i<len; ++i)
        printf(" %d", a[i]);
    printf(" }\n");
}
