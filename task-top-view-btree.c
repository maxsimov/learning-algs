#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "bin-tree.h"
#include "deque.h"
#include "hash.h"

/* 
  http://www.geeksforgeeks.org/print-nodes-top-view-binary-tree/
  
  Top view of a binary tree is the set of nodes visible when the tree is viewed 
  from the top. Given a binary tree, print the top view of it. The output nodes 
  can be printed in any order. Expected time complexity is O(n)

  A node x is there in output if x is the topmost node at its horizontal 
  distance. Horizontal distance of left child of a node x is equal to horizontal 
  distance of x minus 1, and that of right child is horizontal distance 
  of x plus 1.

       1
    /     \
   2       3
  /  \    / \
 4    5  6   7
Top view of the above binary tree is
4 2 1 3 7

        1
      /   \
    2       3
      \   
        4  
          \
            5
             \
               6
Top view of the above binary tree is
2 1 3 6

*/

unsigned hash_distance(void *key)
{
    return (uintptr_t)key;
}

int hash_distance_compare(void *key1, void *key2)
{
    return key1 == key2;
}

void print_top_line(struct bin_tree *tree)
{
    struct deque tree_traversal;
    struct deque tree_distance;
    struct hash_table *ht;
    
    deque_init(&tree_traversal);
    deque_init(&tree_distance);
    ht = hash_create(hash_distance, hash_distance_compare, 32);

    int nodes_in_level = 1;
    int nodes_in_level_next = 0;
    int level = 0;
    int horizontal_distance;
    int lower_bound = INT_MAX;
    int upper_bound = INT_MIN;
    
    deque_push_back_ptr(&tree_traversal, tree);
    deque_push_back_int(&tree_distance, 0);
    
    struct bin_tree *node;
    
    while (deque_pop_front_ptr(&tree_traversal, (void **) &node))
    {
        deque_pop_front_int(&tree_distance, &horizontal_distance);
        if (horizontal_distance > upper_bound)
            upper_bound = horizontal_distance;
        if (horizontal_distance < lower_bound)
            lower_bound = horizontal_distance;
        
        if (!hash_lookup(ht, (void *)horizontal_distance))
            hash_insert(ht, (void *)horizontal_distance, node);
        
        if (node->left)
        {
            deque_push_back_ptr(&tree_traversal, node->left);
            deque_push_back_int(&tree_distance, horizontal_distance-1);
            nodes_in_level_next++;
        }
        
        if (node->right)
        {
            deque_push_back_ptr(&tree_traversal, node->right);
            deque_push_back_int(&tree_distance, horizontal_distance+1);
            nodes_in_level_next++;
        }

        if (--nodes_in_level == 0)
        {
            level++;
            nodes_in_level = nodes_in_level_next;
            nodes_in_level_next = 0;
        }
    }
    
    printf("Top:");
    for (int i=lower_bound; i<=upper_bound; ++i)
    {
        struct bin_tree *n = hash_lookup(ht, (void *)i);
        
        if (!n)
            continue;
        
        printf(" %d", n->key);
    }
    printf("\n");
    
    hash_destroy(ht);
    deque_cleanup(&tree_distance);
    deque_cleanup(&tree_traversal);
}

void test_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(1, 0);
    tree->left = bin_tree_create(2,0);
        tree->left->left = bin_tree_create(4, 0);
        tree->left->right = bin_tree_create(5, 0);
    tree->right = bin_tree_create(3, 0);
        tree->right->left = bin_tree_create(6, 0);
        tree->right->right = bin_tree_create(7, 0);

    bin_tree_display(tree);
    print_top_line(tree);

    bin_tree_destroy(tree);
}

void test_2()
{
    struct bin_tree *tree;

    tree = bin_tree_create(1, 0);
    tree->left = bin_tree_create(2,0);
        tree->left->right = bin_tree_create(4, 0);
            tree->left->right->right = bin_tree_create(5, 0);
                tree->left->right->right->right = bin_tree_create(6, 0);
    tree->right = bin_tree_create(3, 0);

    bin_tree_display(tree);
    print_top_line(tree);

    bin_tree_destroy(tree);
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
