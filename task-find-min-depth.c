#include <stdio.h>
#include <stdio.h>
#include "bin-tree.h"

/* 
  http://www.geeksforgeeks.org/find-minimum-depth-of-a-binary-tree/
  
  Given a binary tree, find its minimum depth. 
  The minimum depth is the number of nodes along the shortest path
   from root node down to the nearest leaf node.

*/

int find_min_depth(struct bin_tree *tree)
{
    if (!tree->left && !tree->right)
        return 1;

    if (!tree->left)
        return 1 + find_min_depth(tree->right);

    if (!tree->right)
        return 1 + find_min_depth(tree->left);

    int left_min_depth = find_min_depth(tree->left);
    int right_min_depth = find_min_depth(tree->right);
    
    int min_depth = 
        left_min_depth < right_min_depth ? left_min_depth : right_min_depth;
    
    return 1 + min_depth;
}

void test_find_min_depth_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(5, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->right = bin_tree_create(1, 0);
    tree->right = bin_tree_create(6, 0);

    printf("Find min depth in simple tree ...\n");

    bin_tree_display(tree);
    
    printf("Min depth = %d\n", find_min_depth(tree));

    bin_tree_destroy(tree);
}

void test_find_min_depth_2()
{
    struct bin_tree *tree = bin_tree_random(0xAEFE89AE, 10, 100);

    printf("Find min depth in random tree 2...\n");
    bin_tree_display(tree);

    printf("Min depth = %d\n", find_min_depth(tree));

    bin_tree_destroy(tree);
}

void test_find_min_depth_3()
{
    struct bin_tree *tree = bin_tree_random(0xAEFE89AE, 100, 100);

    printf("Find min depth in random tree 3...\n");
    bin_tree_display(tree);

    printf("Min depth = %d\n", find_min_depth(tree));

    bin_tree_destroy(tree);
}

int main(int argc, char *argv[])
{
    test_find_min_depth_1();
    test_find_min_depth_2();
    test_find_min_depth_3();

    return 0;
}
