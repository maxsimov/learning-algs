#include <stdlib.h>
#include <stdio.h>
#include "heap_inplace.h"

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct heap
{
    int *nums; 
    int *index;
    int *rindex;
    int  size;
    int indexBase;
};

struct heap *heap_create(int size)
{
  struct heap *h = malloc(sizeof(struct heap) + sizeof(int)*size*2);
  h->size = size;
  h->index = (int *)(h+1);
  h->rindex = h->index + size;

  return h;
}

void heap_destroy(struct heap *h)
{
    free(h);
}

void heap_heapify(struct heap *h, int root)
{
    int *nums = h->nums;
    int *index = h->index;
    int *rindex = h->rindex;
    int size = h->size;
    
    for (;;)
    {
        int left = 2*root+1;
        int right = 2*root+2;
        int minIdx = root;
   
        if (left < size && nums[index[minIdx]] > nums[index[left]])
            minIdx = left;
        if (right < size && nums[index[minIdx]] > nums[index[right]])
            minIdx = right;
    
        if (minIdx != root)
        {
            swap(&index[minIdx], &index[root]);
            rindex[index[minIdx] % size] = minIdx;
            rindex[index[root]   % size] = root;
        }    
        
        if (root == minIdx)
            break;
        
        root = minIdx;
    }
}

void heap_build(struct heap *h, int *nums, int indexBase)
{
    int *index = h->index;
    int *rindex = h->rindex;
    int size = h->size;

    h->nums = nums;
    h->indexBase = indexBase;

    for (int i=0; i<size; i++)
    {
        rindex[(i + indexBase) % size] = i;
        index[i] = i + indexBase;
    }

    printf("Initial:\n");
    heap_dump(h);
    
    for (int root=size/2-1; root >= 0; root--)
    {
        heap_heapify(h, root);
          printf("Root: %d\n", root);
          heap_dump(h);
    }
}

int heap_top(struct heap *h)
{
    return h->nums[h->index[0]];
}

void heap_shift(struct heap *h)
{
    int *nums = h->nums;
    int *index = h->index;
    int *rindex = h->rindex;
    int size = h->size;

    int root = rindex[h->indexBase % size];
    int prevValue = nums[index[root]];
    index[root] = h->indexBase + size;
    rindex[h->indexBase % size] = root;
    h->indexBase++;    
        
    int curValue = nums[index[root]];
    
    if (curValue > prevValue)
    {
        heap_heapify(h, root);
    } else {
        for (;;)
        {
            root = (root-1)/2;
            heap_heapify(h, root);
            if (root == 0)
                break;
        }
    }
}

void heap_dump(struct heap *h)
{
    printf("{\n");
    printf("  size: %d\n", h->size);
    printf("  indexBase: %d\n", h->indexBase);
    printf("  data: [");
    for (int i=0; i<h->size; i++)
      printf(" %d", h->nums[h->index[i]]);
    printf("]\n");
    printf("  index: [");
    for (int i=0; i<h->size; i++)
      printf(" %d", h->index[i]);
    printf("]\n");
    printf("  rindex: [");
    for (int i=0; i<h->size; i++)
      printf(" %d", h->rindex[i]);
    printf("]\n");
    printf("  mapping v2p: [");
    for (int i=0; i<h->size; i++)
      printf(" %d->%d", i, h->index[i]);
    printf("]\n");
    printf("  mapping p2v: [");
    for (int i=0; i<h->size; i++)
      printf(" %d->%d", h->indexBase+i, h->rindex[(h->indexBase+i) % h->size]);
    printf("]\n");

    printf("}\n");
}
