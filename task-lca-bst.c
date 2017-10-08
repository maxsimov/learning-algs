#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "bin-tree.h"
#include "deque.h"
#include "hash.h"

/* 
  http://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/
  
  Given values of two values n1 and n2 in a Binary Search Tree, find the Lowest 
  Common Ancestor (LCA). You may assume that both the values exist in the tree.

           20
          /  \
         8    22
        / \ 
       4   12
          /   \
         10   14

*/

struct bin_tree *find_lca(struct bin_tree *tree, int n1, int n2)
{
    if (!tree)
        return 0;
    
    if (n1 < tree->key && n2 < tree->key)
        return find_lca(tree->left, n1, n2);

    if (n1 > tree->key && n2 > tree->key)
        return find_lca(tree->right, n1, n2);

    return tree;
}

struct bin_tree *find_lca_it(struct bin_tree *tree, int n1, int n2)
{
    while (tree)
    {
        if (n1 < tree->key && n2 < tree->key)
            tree = tree->left;
        else if (n1 > tree->key && n2 > tree->key)
            tree = tree->right;
        else 
            break;
    }

    return tree;
}

void find_lca_util(struct bin_tree *tree, int n1, int n2)
{
    printf("-----------------------------\n");
    bin_tree_display(tree);
    
    struct bin_tree *lca = find_lca_it(tree, n1, n2);
    if (lca)
        printf("LCA for %d and %d is %d\n", n1, n2, lca->key);
    else
        printf("LCA for %d and %d not found\n", n1, n2);
}

void test_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(20, 0);
    tree->left = bin_tree_create(8, 0);
        tree->left->left = bin_tree_create(4, 0);
        tree->left->right = bin_tree_create(12, 0);
            tree->left->right->left = bin_tree_create(10, 0);
            tree->left->right->right = bin_tree_create(14, 0);
    tree->right = bin_tree_create(22, 0);

    find_lca_util(tree, 10, 14);
    find_lca_util(tree, 14, 8);
    find_lca_util(tree, 10, 22);
    bin_tree_destroy(tree);
}


int main(int argc, char *argv[])
{
    test_1();

    return 0;
}
