#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

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

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) 
{
    struct ListNode *result = malloc(sizeof(*result));
    
    result->val = 0;
    result->next = 0;
    
    return result;
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

    for (int i=0; i<sizeof(lists)/sizeof(lists[0]); ++i)
        destroy_list(lists[i]);
}

int main(int argc, char *argv[])
{
    merge_K_lists_driver();

    return 0;
}
