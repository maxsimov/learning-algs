#pragma once

struct avl_tree
{
    struct avl_tree *left;
    struct avl_tree *right;
    int balance;
    
    int key;
};

struct avl_tree *avl_tree_create(int value);
void avl_tree_destroy(struct avl_tree *tree);

void avl_tree_add(struct avl_tree *tree, int value);
void avl_tree_print(struct avl_tree *tree);

bool avl_tree_remove(struct avl_tree *tree, int value);
struct avl_tree *avl_tree_find(struct avl_tree *tree, int value);
