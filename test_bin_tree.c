#include <stdio.h>
#include <stdlib.h>
#include "bin-tree.h"

void test_basic_bfs_traversal_1_visit(void *context, struct bin_tree *tree, 
                                      int level, int breadth_index)
{
    printf(" %d", tree->key);
}

void test_basic_dfs_traversal_1_visit(void *context, struct bin_tree *tree)
{
    printf(" %d", tree->key);
}

void test_basic_traversal_1()
{
    struct bin_tree *tree;
    
    printf("Basic traversal 1\n");
    
    tree = bin_tree_create(5, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->right = bin_tree_create(1, 0);
    tree->right = bin_tree_create(6, 0);

    printf(" BFS:");
    bin_tree_BFS(tree, test_basic_bfs_traversal_1_visit, 0);
    printf("\n");

    printf(" DFS preorder:");
    bin_tree_DFS_preorder(tree, test_basic_dfs_traversal_1_visit, 0);
    printf("\n");

    printf(" DFS inorder:");
    bin_tree_DFS_inorder(tree, test_basic_dfs_traversal_1_visit, 0);
    printf("\n");

    printf(" DFS postorder:");
    bin_tree_DFS_postorder(tree, test_basic_dfs_traversal_1_visit, 0);
    printf("\n");
    
    printf(" Tree Height: %d\n", bin_tree_height(tree));
    bin_tree_display(tree);
    
    bin_tree_destroy(tree);
    
}

void test_display_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(5, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->right = bin_tree_create(1, 0);
    tree->right = bin_tree_create(6, 0);
        tree->right->right = bin_tree_create(7, 0);

    printf(" Tree Height: %d\n", bin_tree_height(tree));
    bin_tree_display(tree);
    
    bin_tree_destroy(tree);
    
}

void test_random_tree_1()
{
    struct bin_tree *tree = bin_tree_random(0x38FADE61, 100, 99);

    printf("Generate random tree ...\n");
    printf(" Tree Height: %d\n", bin_tree_height(tree));
    bin_tree_display(tree);
    
    bin_tree_destroy(tree);
}

void test_bfs()
{
    test_basic_traversal_1();
    test_display_1();
    test_random_tree_1();    
}

int main(int argc, char *argv[])
{
    test_bfs();
    
    return 0;
}
