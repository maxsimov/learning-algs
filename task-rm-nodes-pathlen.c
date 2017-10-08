#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "bin-tree.h"
#include "deque.h"
#include "hash.h"

/* 
  http://www.geeksforgeeks.org/remove-nodes-root-leaf-paths-length-k/
  
  Given a Binary Tree and a number k, remove all nodes that lie only on root 
  to leaf path(s) of length smaller than k. If a node X lies on multiple 
  root-to-leaf paths and if any of the paths has path length >= k, then X 
  is not deleted from Binary Tree. In other words a node is deleted if all 
  paths going through it have lengths smaller than k.

               1
           /      \
         2          3
      /     \         \
    4         5        6
  /                   /
 7                   8 
 Input: Root of above Binary Tree
       k = 4

 Output: The tree should be changed to following  
           1
        /     \
      2          3
     /             \
   4                 6
 /                  /
7                  8
 There are 3 paths 
 i) 1->2->4->7      path length = 4
 ii) 1->2->5        path length = 3
 iii) 1->3->6->8    path length = 4 
 There is only one path " 1->2->5 " of length smaller than 4.  
 The node 5 is the only node that lies only on this path, so 
 node 5 is removed.
 Nodes 2 and 1 are not removed as they are parts of other paths
 of length 4 as well.

 If k is 5 or greater than 5, then whole tree is deleted. 

 If k is 3 or less than 3, then nothing is deleted.
*/

struct bin_tree *delete_nodes(struct bin_tree *tree, int path, int max_path)
{
    if (!tree)
        return 0;

    tree->left = delete_nodes(tree->left, path+1, max_path);
    tree->right = delete_nodes(tree->right, path+1, max_path);

    if (tree->left || tree->right || path >= max_path)
        return tree;
    
    free(tree);
    return 0;
}

void delete_nodes_engine(struct bin_tree *tree, int pathlen)
{
    printf("-----------------------------\n");
    bin_tree_display(tree);
    printf("Deleting nodes if they are not on path %d\n", pathlen);
    tree = delete_nodes(tree, 1, pathlen);
    
    if (tree)
    {
        bin_tree_display(tree);
        bin_tree_destroy(tree);
    } else {
        printf("Empty tree!\n");
    }
}

void test_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(1, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->left = bin_tree_create(4, 0);
            tree->left->left->left = bin_tree_create(7, 0);
        tree->left->right = bin_tree_create(5, 0);
    tree->right = bin_tree_create(3, 0);
        tree->right->right = bin_tree_create(6, 0);
            tree->right->right->left = bin_tree_create(8, 0);
    
    delete_nodes_engine(tree, 4);
}

void test_2()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(1, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->left = bin_tree_create(4, 0);
            tree->left->left->left = bin_tree_create(7, 0);
        tree->left->right = bin_tree_create(5, 0);
    tree->right = bin_tree_create(3, 0);
        tree->right->right = bin_tree_create(6, 0);
            tree->right->right->left = bin_tree_create(8, 0);
    
    delete_nodes_engine(tree, 5);
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
