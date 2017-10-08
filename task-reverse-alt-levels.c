#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "bin-tree.h"
#include "deque.h"
#include "hash.h"
#include "util.h"

/* 
  http://www.geeksforgeeks.org/reverse-alternate-levels-binary-tree/
  
  Given a Perfect Binary Tree, reverse the alternate level nodes of the binary tree.
  
Given tree: 
                 a
               /   \
              /     \
             /       \ 
            /         \
           b           c
         /  \         /  \
        d    e       f     g
       / \  / \     / \   / \
       h  i j  k    l  m  n  o 

Modified tree:
  	           a
            /     \
           c       b
         /  \     /  \
        d    e    f    g
       / \  / \  / \  / \
      o  n m  l k  j  i  h 
*/

void reverse_nodes(struct bin_tree *tree1, struct bin_tree *tree2, int level)
{
    if ((level%2) == 0)
        SWAP(tree1->key, tree2->key);
        
    if (tree1->left && tree2->right)
        reverse_nodes(tree1->left, tree2->right, level + 1);
    if (tree1->right && tree2->left)
        reverse_nodes(tree1->right, tree2->left, level + 1);
}

void reverse_nodes_engine(struct bin_tree *tree)
{
    printf("-----------------------------\n");
    printf(" Before\n");
    bin_tree_display_asscii(tree);

    reverse_nodes(tree->left, tree->right, 2);

    printf(" After\n");
    bin_tree_display_asscii(tree);
}

void test_1()
{
    struct bin_tree *tree;

    tree = bin_tree_create_perfect('a', 4);

    reverse_nodes_engine(tree);
    bin_tree_destroy(tree);
}

int main(int argc, char *argv[])
{
    test_1();

    return 0;
}
