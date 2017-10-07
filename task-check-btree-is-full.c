#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "bin-tree.h"

/* 
  http://www.geeksforgeeks.org/check-whether-binary-tree-full-binary-tree-not/
  
  Check whether a binary tree is a full binary tree or not
  A full binary tree is defined as a binary tree in which all nodes have 
  either zero or two child nodes. 
  Conversely, there is no node in a full binary tree, which has one child node. 
  More information about full binary trees can be found here.
  Let's have an example:
  
  Full
       1
      / \
     2   3
    / \
   4   5

 Not Full
       1
      / \
     2   3
    /
   4 

*/



bool is_full(struct bin_tree *tree)
{
    if (!tree->left && !tree->right)
        return true;
    if (!tree->left || !tree->right)
        return false;

    return is_full(tree->left) && is_full(tree->right);
}

void test_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(1, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->left = bin_tree_create(4, 0);
        tree->left->right = bin_tree_create(5, 0);
    tree->right = bin_tree_create(3, 0);

    bin_tree_display(tree);
    
    if (is_full(tree)) printf("Binary tree is full\n");
     else printf("Binary tree is not full\n");
    
    bin_tree_destroy(tree);
}

void test_2()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(1, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->left = bin_tree_create(4, 0);
    tree->right = bin_tree_create(3, 0);

    bin_tree_display(tree);
    
    if (is_full(tree)) printf("Binary tree is full\n");
     else printf("Binary tree is not full\n");
    
    bin_tree_destroy(tree);
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
