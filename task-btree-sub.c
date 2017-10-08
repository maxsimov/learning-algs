#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "bin-tree.h"
#include "deque.h"
#include "hash.h"

/* 
  http://www.geeksforgeeks.org/check-binary-tree-subtree-another-binary-tree-set-2/
  
  Given two binary trees, check if the first tree is subtree of the second one. 
  A subtree of a tree T is a tree S consisting of a node in T and 
  all of its descendants in T.

  The subtree corresponding to the root node is the entire tree; the subtree 
  corresponding to any other node is called a proper subtree.

 Tree1
          x 
        /    \
      a       b
       \
        c


        Tree2
              z
            /   \
          x      e
        /    \     \
      a       b      k
       \
        c
*/

bool is_identical(struct bin_tree *tree, struct bin_tree *pattern)
{
    if (tree->key != pattern->key)
        return false;
        
    if (pattern->left)
    {
        if (!tree->left)
            return false;
        if (!is_identical(tree->left, pattern->left))
            return false;
    }
    
    if (pattern->right) 
    {
        if (!tree->right)
            return false;
        if (!is_identical(tree->right, pattern->right))
            return false;
    }
    
    return true;
}

bool is_subtree(struct bin_tree *tree, struct bin_tree *pattern)
{
    if (is_identical(tree, pattern))
        return true;
        
    if (tree->left && is_subtree(tree->left, pattern))
        return true;
        
    if (tree->right && is_subtree(tree->right, pattern))
        return true;
        
    return false;
}


void is_subtree_engine(struct bin_tree *tree1, struct bin_tree *tree2)
{
    printf("-----------------------------\n");
    printf(" Tree 1\n");
    bin_tree_display(tree1);
    printf(" Tree 2\n");
    bin_tree_display(tree2);
    
    if (is_subtree(tree1, tree2)) printf("Tree2 is a subtree of Tree1\n");
     else printf("Tree2 is NOT a subtree of Tree1\n");
}

void test_1()
{
    struct bin_tree *tree, *tree1, *tree2;
    
    tree = bin_tree_create('z', 0);
    tree->left = bin_tree_create('x', 0);
        tree->left->left = bin_tree_create('a', 0);
            tree->left->left->right = bin_tree_create('c', 0);
        tree->left->right = bin_tree_create('b', 0);
    tree->right = bin_tree_create('e', 0);
        tree->right->right = bin_tree_create('k', 0);
    tree1 = tree;

    tree = bin_tree_create('x', 0);
    tree->left = bin_tree_create('a', 0);
        tree->left->right = bin_tree_create('c', 0);
    tree->right = bin_tree_create('b', 0);
    tree2 = tree;

    is_subtree_engine(tree1, tree2);

    bin_tree_destroy(tree1);
    bin_tree_destroy(tree2);
}

int main(int argc, char *argv[])
{
    test_1();

    return 0;
}
