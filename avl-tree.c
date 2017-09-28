#include <stdlib.h>
#include <stdio.h>

#include "avl-tree.h"
#include "queue.h"

struct avl_tree *avl_tree_create(int value)
{
    struct avl_tree *tree = malloc(sizeof(*tree));
    
    tree->left = tree->right = NULL;
    tree->balance = 0;
    tree->key = value;
    
    return tree;
}

void avl_tree_destroy(struct avl_tree *tree)
{
    if (!tree)
        return;

    avl_tree_destroy(tree->left);
    avl_tree_destroy(tree->right);
        
    free(tree);
}

void avl_tree_add(struct avl_tree *tree, int value)
{
    struct avl_tree *cur = tree;
    
    for (; ;)
    {
        if (value < cur->key)
        {
            if (!cur->left)
            {
                cur->left = avl_tree_create(value);
                break;
            }
            cur = cur->left;
        } else {
            if (!cur->right)
            {
                cur->right = avl_tree_create(value);
                break;
            }
            cur = cur->right;
        }
    }
}

void avl_tree_print(struct avl_tree *tree)
{
    struct queue que;
    
    if (tree == NULL)
        return;
    
    queue_init(&que);
    
    queue_enque(&que, tree);
    
    struct avl_tree *cur = NULL;
    
    while (queue_deque(&que, &cur))
    {
        if (cur->left)
            queue_enque(&que, cur->left);
        if (cur->right)
            queue_enque(&que, cur->right);
            
        
        
    }
}
