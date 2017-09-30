#include <stdlib.h>
#include "deque.h"
#include "bin-tree.h"

struct bin_tree *bin_tree_create(int root_key, void *data)
{
    struct bin_tree *tree = malloc(sizeof(struct bin_tree));

    tree->key = root_key;
    tree->data = data;
    tree->left = tree->right = 0;
    
    return tree;
}

static
void bin_tree_destroy_node(void *context, struct bin_tree *tree)
{
    free(tree);
}

void bin_tree_destroy(struct bin_tree *tree)
{
    bin_tree_DFS_postorder(tree, &bin_tree_destroy_node, 0);    
}

void bin_tree_display(struct bin_tree *tree)
{
    
}

void bin_tree_BFS(struct bin_tree *tree, bin_tree_bfs_callback visit, void *context)
{
    struct deque queue;
    
    if (!tree)
        return;
    
    int level = 0;
    int remaining_nodes = 1;
    int remaining_nodes_next = 0;
    
    deque_init(&queue);
    deque_push_back_ptr(&queue, tree);
    
    struct bin_tree *e;
    
    while (deque_pop_front_ptr(&queue, (void **)&e))
    {
        if (e->left) 
        {
            ++remaining_nodes_next;
            deque_push_back_ptr(&queue, e->left);
        }
        if (e->right) 
        {
            ++remaining_nodes_next;
            deque_push_back_ptr(&queue, e->right);
        }
        
        visit(context, e, level);
        
        if (--remaining_nodes == 0)
        {
            remaining_nodes = remaining_nodes_next;
            remaining_nodes_next = 0;
            ++level;
        }
    }
    
    deque_cleanup(&queue);
}

void bin_tree_DFS_preorder(struct bin_tree *tree, bin_tree_dfs_callback visit, 
                           void *context)
{
    struct deque stack;

    deque_init(&stack);
    
    deque_push_front_ptr(&stack, tree);
    
    struct bin_tree *e;
    
    while (deque_pop_front_ptr(&stack, (void **)&e))
    {
        if (e->right)
            deque_push_front_ptr(&stack, e->right);
        if (e->left)
            deque_push_front_ptr(&stack, e->left);
            
        visit(context, e);
    }
    
    deque_cleanup(&stack);
}

void bin_tree_DFS_inorder(struct bin_tree *tree, bin_tree_dfs_callback visit, 
                           void *context)
{
    struct deque stack;

    deque_init(&stack);
    struct bin_tree *tr = tree, *e = 0;

    for (;;)
    {
        while (tr)
        {
            deque_push_front_ptr(&stack, tr);
            tr = tr->left;
        }
        
        if (!deque_pop_front_ptr(&stack, (void **) &e))
            break;

        visit(context, e);
        
        tr = e->right;
    }
    
    deque_cleanup(&stack);
}

void bin_tree_DFS_postorder(struct bin_tree *tree, bin_tree_dfs_callback visit, 
                           void *context)
{
    struct deque stack;

    deque_init(&stack);

    struct bin_tree *current = tree;
    struct bin_tree *last_visited = 0;
    struct bin_tree *e;
    
    for (;;)
    {
        for (; current; current = current->left)
            deque_push_front_ptr(&stack, current);

        if (!deque_peek_front_ptr(&stack, (void **) &e))
            break;

        if (e->right && last_visited != e->right)
        {
            current = e->right;
            continue;
        }
        
        deque_pop_front_ptr(&stack, (void **) &last_visited);
        visit(context, last_visited);        
    }
    
    deque_cleanup(&stack);
}
