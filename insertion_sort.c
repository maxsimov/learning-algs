#include "insertion_sort.h"

#define SWAP(a,b) \
    do { int temp=a; a=b; b=temp; } while (0)

void insertion_sort(int input[], int len)
{
    for (int i=1; i<len; ++i)
    {
        for (int j=i; j>0; --j)
        {
            if (input[j] < input[j-1])
                SWAP(input[j], input[j-1]);
            else
                break;
        }
    }
}
