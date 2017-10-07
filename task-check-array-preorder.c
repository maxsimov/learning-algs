#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "bin-tree.h"
#include "stack.h"

/* 
  http://www.geeksforgeeks.org/check-if-a-given-array-can-represent-preorder-traversal-of-binary-search-tree/
  
  Given an array of numbers, return true if given array can represent preorder 
  traversal of a Binary Search Tree, else return false. 
  Expected time complexity is O(n).
  
  Let's have an example:
          5
         / \
        /   \
       /     \
      /       \
     3         8
    / \       / \ 
   2   4     7   9
            /
           6
  
  Seq1: 5 3 2 4 8 7 6 9
  Seq2: 5 9 2 4 8 7 3 6
          5
         / \
        /   \
       /     \
      /       \
     2+        9+
    / \       / \ 
   2   4+     8+   9
            /
           7+
  
  
   2, 4, 1
   
      2
     / \
    1   4
 
  2 1 4
   

*/



static 
void dump(const int input[], int size)
{
    for (int i=0; i<size; ++i)
        printf(" %d", input[i]);
}

bool check_and_insert(struct bin_tree *tree, int key)
{
    for (;;)
    {
        if (key < tree->key)
        {
            if (tree->left)
            {
                tree = tree->left;
                continue;
            }

            if (tree->right)
                return false;
            
            tree->left = bin_tree_create(key, 0);
            return true;
        }
        
        if (tree->right)
        {
            tree = tree->right;
            continue;
        }

        tree->right = bin_tree_create(key, 0);
        return true;
    }
    
    return false;
}

bool check_if_preorder_tree(const int input[], int size)
{
    if (size < 1)
        return false;
        
    struct bin_tree *tree = bin_tree_create(input[0], 0);
    
    for (int i=1; i<size; ++i)
        if (!check_and_insert(tree, input[i]))
        {
            bin_tree_destroy(tree);
            return false;
        }
            
    bin_tree_destroy(tree);
    return true;
}


// solution 2: using stack



bool check_if_preorder_tree2_worker(struct stack *stack,
                                    const int *begin, const int *end)
{
    if (begin == end)
        return true;
        
    int lowerBound = INT_MIN;
    
    for (;begin != end; ++begin)
    {
        int next = *begin;

        if (next < lowerBound)
            return false;
        
        while (!stack_empty(stack) && stack_top(stack) < next)
            stack_pop(stack, &lowerBound);
        
        stack_push(stack, next);
    }
    
    return true;
}

bool check_if_preorder_tree2(const int input[], int size)
{
    if (size < 1)
        return true;

    struct stack stack;
    
    bool s = stack_init(&stack, 16);
    assert(s);
    if (!s)
        return false;

    s = check_if_preorder_tree2_worker(&stack, input, input + size);

    stack_cleanup(&stack);
        
    return s;
}

void check_preorder(const char *msg, const int input[], int size)
{
    printf("Checking %s:", msg);
    dump(input, size);
    printf("\n");
    
    bool result = check_if_preorder_tree2(input, size);
    
    if (result)
        printf("Yes: Array can represent Preorder Traversal of Binary Search Tree\n");
    else
        printf("No: Array cannot represent Preorder Traversal of Binary Search Tree\n");
}

void test_1()
{
    int input[] = {2, 4, 3};

    check_preorder(
        "Example 1, should return true",
        input,
        sizeof(input)/sizeof(input[0])
        );
}

void test_2()
{
    int input[] = {2, 4, 1};

    check_preorder(
        "Example 2, should return false",
        input,
        sizeof(input)/sizeof(input[0])
        );
}

void test_3()
{
    int input[] = {40, 30, 35, 80, 100};

    check_preorder(
        "Example 3, should return true",
        input,
        sizeof(input)/sizeof(input[0])
        );
}

void test_4()
{
    int input[] = {40, 30, 35, 20, 80, 100};

    check_preorder(
        "Example 4, should return false",
        input,
        sizeof(input)/sizeof(input[0])
        );
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}
