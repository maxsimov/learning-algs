#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "bin-tree.h"
#include "deque.h"
#include "hash.h"

/* 
  http://www.geeksforgeeks.org/bottom-view-binary-tree/
  
  Given a Binary Tree, we need to print the bottom view from left to right. 
  A node x is there in output if x is the bottommost node at its horizontal 
  distance. Horizontal distance of left child of a node x is equal to horizontal 
  distance of x minus 1, and that of right child is 
  horizontal distance of x plus 1.

                      20
                    /    \
                  8      22
                /   \      \
              5      3      25
                    / \      
                  10    14
  If there are multiple bottom-most nodes for a horizontal distance from root, 
  then print the later one in level traversal.

*/

unsigned hash_distance(void *key)
{
    return (unsigned)key;
}

int hash_distance_compare(void *key1, void *key2)
{
    return (unsigned)key1 == (unsigned)key2;
}

void print_bottom_line(struct bin_tree *tree)
{
    struct deque bottom_view;
    struct deque tree_traversal;
    struct deque tree_distance;
    struct hash_table *ht;
    
    deque_init(&bottom_view);
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
    
    printf("Bottom:");
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
    deque_cleanup(&bottom_view);
}

void test_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(20, 0);
    tree->left = bin_tree_create(8, 0);
        tree->left->left = bin_tree_create(5, 0);
        tree->left->right = bin_tree_create(3, 0);
            tree->left->right->left = bin_tree_create(10, 0);
            tree->left->right->right = bin_tree_create(14, 0);
    tree->right = bin_tree_create(22, 0);
        tree->right->right = bin_tree_create(25, 0);

    bin_tree_display(tree);
    print_bottom_line(tree);

    bin_tree_destroy(tree);
}

void test_2()
{
    struct bin_tree *tree;

    tree = bin_tree_create(20, 0);
    tree->left = bin_tree_create(8, 0);
        tree->left->left = bin_tree_create(5, 0);
        tree->left->right = bin_tree_create(3, 0);
            tree->left->right->left = bin_tree_create(10, 0);
            tree->left->right->right = bin_tree_create(14, 0);
    tree->right = bin_tree_create(22, 0);
        tree->right->left = bin_tree_create(4, 0);
        tree->right->right = bin_tree_create(25, 0);
    
    bin_tree_display(tree);
    print_bottom_line(tree);

    bin_tree_destroy(tree);
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
