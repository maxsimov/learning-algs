#include <string.h>
#include <stdlib.h>
#include "merge_sort.h"

static
void merge(int a[], int middle, int len, int temp[])
{
    int lindex = 0;
    int rindex = middle;
    int oindex = 0;

    for (; oindex<len && lindex < middle && rindex < len; ++oindex)
    {
        if (a[lindex] < a[rindex])
            temp[oindex] = a[lindex++];
         else
            temp[oindex] = a[rindex++];
    }
    
    if (lindex < middle)
        memcpy(&temp[oindex], &a[lindex], (middle-lindex)*sizeof(int));
    
    if (rindex < len)
        memcpy(&temp[oindex], &a[rindex], (len-rindex)*sizeof(int));

    memcpy(a, temp, len*sizeof(int));
}

static
void merge_sort_int(int input[], int len, int temp[])
{
    if (len <= 1)
        return;
        
    int m = len/2;
    
    merge_sort_int(input, m, temp);
    merge_sort_int(input+m, len - m, temp);
    
    merge(input, m, len, temp);
}

int merge_sort(int input[], int len)
{
    int *temp = malloc(len*sizeof(int));
    
    if (!temp)
        return 0;
        
    if (!len)
        return 0;
    
    merge_sort_int(input, len, temp);
        
    free(temp);
    
    return 1;
}
