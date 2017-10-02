#include <stdlib.h>
#include <stdio.h>
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

static
void calc_height(void *context, struct bin_tree *tree, int level, int breadth_index)
{
    int *max_level = (int *)context;
    
    if (level > *max_level)
        *max_level = level;
}

int bin_tree_height(struct bin_tree *tree)
{
    int height = 0;
    
    bin_tree_BFS(tree, calc_height, &height);
    
    return height;
}

struct bin_tree_display_context
{
    char buf[128];
    char *sbeg;
    char *send;
};

void bin_tree_display_increase(struct bin_tree_display_context *ctx, char c)
{
    int maxlen = ctx->send - ctx->sbeg;
    
    if (maxlen < 4)
        return;
        
    ctx->sbeg[0] = c;
    ctx->sbeg[1] = ' ';
    ctx->sbeg[2] = ' ';
    ctx->sbeg[3] = 0;
    
    ctx->sbeg += 3;
}

void bin_tree_display_descrease(struct bin_tree_display_context *ctx)
{
    int maxdec = ctx->sbeg - ctx->buf;
    
    if (maxdec > 3)
        maxdec = 3;
        
    ctx->sbeg -= 3;
    ctx->sbeg[0] = 0;
}

void _bin_tree_display(struct bin_tree *tree, 
                       struct bin_tree_display_context *ctx)
{
    printf("%d\n", tree->key);
    
    if (tree->left)
    {
        printf("%sL--", ctx->buf);
        bin_tree_display_increase(ctx, tree->right ? '|' : ' ');
        _bin_tree_display(tree->left, ctx);
        bin_tree_display_descrease(ctx);
    }
    if (tree->right)
    {
        printf( "%sR--", ctx->buf);
        bin_tree_display_increase(ctx, ' ');
        _bin_tree_display(tree->right, ctx);
        bin_tree_display_descrease(ctx);
    }
}

void bin_tree_display(struct bin_tree *tree)
{
    struct bin_tree_display_context ctx;

    ctx.sbeg = ctx.buf;
    ctx.send = &ctx.buf[sizeof(ctx.buf)/sizeof(ctx.buf[0])-1];
    
    *ctx.sbeg = 0;
    *ctx.send = 0;
    
    _bin_tree_display(tree, &ctx);
}

static
void _bin_tree_BFS(struct bin_tree *tree, bin_tree_bfs_callback visit, 
                   void *context, int full)
{
    struct deque queue;
    
    if (!tree)
        return;
    
    int level = 0;
    int remaining_nodes = 1;
    int remaining_nodes_next = 0;
    int breadth_index = 0;
    
    deque_init(&queue);
    deque_push_back_ptr(&queue, tree);
    
    struct bin_tree *e;
    
    while (deque_pop_front_ptr(&queue, (void **)&e))
    {
        if (e)
        {
            ++remaining_nodes_next;
            deque_push_back_ptr(&queue, e->left);
            
            ++remaining_nodes_next;
            deque_push_back_ptr(&queue, e->right);
        }
        
        if (e || full)
            visit(context, e, level, breadth_index);
            
        breadth_index++;
        
        if (--remaining_nodes == 0)
        {
            remaining_nodes = remaining_nodes_next;
            remaining_nodes_next = 0;
            breadth_index = 0;
            ++level;
        }
    }
    
    deque_cleanup(&queue);
}

void bin_tree_BFS(struct bin_tree *tree, bin_tree_bfs_callback visit, void *context)
{
    _bin_tree_BFS(tree, visit, context, 0);
}

void bin_tree_BFS_full(struct bin_tree *tree, bin_tree_bfs_callback visit, 
                       void *context)
{
    _bin_tree_BFS(tree, visit, context, 1);
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

struct bin_tree *_bin_tree_random(int nodes, int max_value)
{
    if (!nodes)
        return 0;
        
    struct bin_tree *root = bin_tree_create(random() % max_value, 0);

    if (--nodes == 0)
        return root;

    int left_nodes = random() % nodes;
    int right_nodes = nodes - left_nodes;

    root->left = _bin_tree_random(left_nodes, max_value);
    root->right = _bin_tree_random(right_nodes, max_value);
    
    return root;
}

struct bin_tree *bin_tree_random(unsigned seed, int nodes, int max_value)
{
    srandom(seed);
    
    return _bin_tree_random(nodes, max_value);
}
