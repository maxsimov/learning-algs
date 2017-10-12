#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "util.h"
/* 
  Merge k Sorted Lists
  Source: https://leetcode.com/problems/merge-k-sorted-lists/description/
  
  Merge k sorted linked lists and return it as one sorted list.
  Analyze and describe its complexity.
  

*/

struct ListNode 
{
    int val;
    struct ListNode *next;
};

void sift_down(struct ListNode** lists, int listsSize, int root)
{
    for (int child=(2*root+2); child<listsSize; child=(2*root+2))
    {
        int swap_index = root;
            
        if (lists[swap_index]->val > lists[child]->val)
            swap_index = child;
                
        ++child;
        if (child < listsSize && lists[swap_index]->val > lists[child]->val)
            swap_index = child;
                
        if (swap_index == root)
            break;
                
        SWAP(lists[swap_index], lists[root]);
        root = swap_index;
    }
}

void advance_list(struct ListNode** lists, int *listsSize)
{
    lists[0] = lists[0]->next;
    
    if (!lists[0])
    {
        if (!--(*listsSize))
            return;

        lists[0] = lists[*listsSize];
    }

    sift_down(lists, *listsSize, 0);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) 
{
    if (listsSize < 0)
        return 0;

    if (listsSize == 1)
        return lists[0];
    
    // heapify
    for (int parent=(listsSize-2)/2; parent>=0; parent--)
        sift_down(lists, listsSize, parent);
        
    struct ListNode *head = lists[0];
    struct ListNode *tail = lists[0];
    
    advance_list(lists, &listsSize);

    while (listsSize)
    {
        tail->next = lists[0];
        tail = lists[0];
        advance_list(lists, &listsSize);
    }
    
    tail->next = 0;

    return head;
}

struct ListNode *create_list(int input[], int n)
{
    if (n < 1)
        return 0;
    
    struct ListNode *root = malloc(sizeof(*root));
    struct ListNode *tail = root;
    struct ListNode *entry;

    root->val = input[0];
    root->next = 0;
    
    for (int i=1; i<n; ++i)
    {
        entry = malloc(sizeof(*entry));
        entry->val = input[i];
        entry->next = 0;
        
        tail->next = entry;
        tail = entry;
    }
    
    return root;
}

void destroy_list(struct ListNode *list)
{
    while (list)
    {
        struct ListNode *next = list->next;
        free(list);
        list = next;
    }
}

void print_list(struct ListNode *list)
{
    for ( ; list; list=list->next)
    {
        printf(" %d", list->val);
    }
}

void merge_K_lists_driver()
{
    struct ListNode *lists[3];    
    
    lists[0] = create_list( (int[]){ 3, 6, 8, 9, 13 }, 5);
    lists[1] = create_list( (int[]){ 7, 10, 11, 16 }, 4);
    lists[2] = create_list( (int[]){ 1, 7, 8 }, 3);
    
    printf("Merging 3 lists\n");
    for (int i=0; i<sizeof(lists)/sizeof(lists[0]); ++i)
    {
        printf("a[%d] ={", i);
        print_list(lists[i]);
        printf(" }\n");
    }
    
    struct ListNode *result = mergeKLists(lists, 3);
    
    if (!result)
        printf("Merge failed!\n");

    printf("merged ={");
    print_list(result);
    printf(" }\n");
    
    destroy_list(result);
}

int main(int argc, char *argv[])
{
    merge_K_lists_driver();

    return 0;
}
