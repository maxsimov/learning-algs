#include "quick_sort.h"

static 
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static
void partition(int input[], int len, int *lindex_o, int *rindex_o)
{
    int lx = 0;
    int mx = 0;
    int ri = len - 1;
    int pivot = input[ri];

    while (mx <= ri)
    {
        if (input[mx] < pivot)
        {
            swap(&input[lx], &input[mx]);
            ++lx;
            ++mx;
            continue;
        }
        
        if (input[mx] == pivot)
        {
            ++mx;
            continue;
        }
        
        swap(&input[mx], &input[ri]);
        --ri;
    }
    
    *lindex_o = lx;
    *rindex_o = mx;
}


void quick_sort(int input[], int len)
{
    if (len < 2)
        return;
    
    int lindex, rindex;
    
    partition(input, len, &lindex, &rindex);
    quick_sort(input, lindex);
    quick_sort(&input[rindex], len-rindex);
}
