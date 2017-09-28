#include "bin-tree.h"

struct bin_tree *bin_tree_create(int root_key)
{
    struct bin_tree *tree = malloc(sizeof(struct bin_tree));

    tree->key = root_key;
    tree->left = tree->right = 0;
    
    return tree;
}

void bin_tree_destroy(struct bin_tree *tree)
{
    
}

void bin_tree_add(struct bin_tree *tree, int value);
