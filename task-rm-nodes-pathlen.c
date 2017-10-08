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

unsigned hash_f(void *n)
{
    struct bin_tree *tree = (struct bin_tree *)n;
    return tree->key;
}

int hash_cmp(void *key1, void *key2)
{
    return key1 == key2;
}

int calc_path(struct bin_tree *tree, struct hash_table *ht, int path)
{
    int left_path=0, right_path=0;
    
    if (tree->left)
        left_path = calc_path(tree->left, ht, path+1);
        
    if (tree->right)
        right_path = calc_path(tree->right, ht, path+1);
    
    int max_path = left_path < right_path ? right_path : left_path;
    if (max_path < path)
        max_path = path;

    uintptr_t stored_path;

    if (!hash_lookup_int(ht, tree, &stored_path) || stored_path < max_path)
        hash_insert_int(ht, tree, max_path);

     return max_path;
}

struct bin_tree *delete_nodes(struct bin_tree *tree, struct hash_table *ht, 
                              int pathlen)
{
    if (!tree)
        return 0;
        
    tree->left = delete_nodes(tree->left, ht, pathlen);
    tree->right = delete_nodes(tree->right, ht, pathlen);

    if (tree->left || tree->right)
        return tree;
        
    uintptr_t stored_path;

    if (hash_lookup_int(ht, tree, &stored_path) && stored_path >= pathlen)
        return tree;
        
    free(tree);
    
    return 0;
}

struct bin_tree *delete_nodes_ifpath_lt(struct bin_tree *tree, int pathlen)
{
    struct hash_table *ht = hash_create(hash_f, hash_cmp, 16);
    
    calc_path(tree, ht, 1);
    struct bin_tree *ret = delete_nodes(tree, ht, pathlen);
    
    hash_destroy(ht);
    
    return ret;
}

void delete_nodes_ifpath_lt_engine(struct bin_tree *tree, int pathlen)
{
    printf("-----------------------------\n");
    bin_tree_display(tree);
    printf("Deleting nodes if they are not on path %d\n", pathlen);
    tree = delete_nodes_ifpath_lt(tree, pathlen);
    
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
    
    delete_nodes_ifpath_lt_engine(tree, 4);
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
    
    delete_nodes_ifpath_lt_engine(tree, 5);
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
