#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "util.h"
#include "avl-tree.h"
#include "queue.h"
#include "stack.h"

struct avl_tree_item
{
    intptr_t key;
    intptr_t value;
    struct avl_tree *left;
    struct avl_tree *right;
    char balance:2;
};

struct avl_tree_body
{
    avl_tree_less less;
    int nodes;
    int stack_capacity;
    struct avl_tree *root;
};

enum avl_node_type { AVL_TREE, AVL_NODE };

struct avl_tree
{
    enum avl_node_type type;
    struct avl_tree_body *body;
    struct avl_tree_item item;
};

static
bool default_less(intptr_t a, intptr_t b)
{
    return a < b;
}

#define CHECK_TREE(tree)    assert(tree->type == AVL_TREE)
#define CHECK_ITEM(tree)    assert(tree->type == AVL_NODE)

struct avl_tree *avl_tree_create()
{
    struct avl_tree *tree = xmalloc(sizeof(*tree));
    struct avl_tree_body *body = xmalloc(sizeof(*body));
    
    tree->type = AVL_TREE;
    tree->body = body;
    
    body->less = default_less;
    body->nodes = 0;
    body->root = 0;
    body->stack_capacity = 4;

    return tree;
}

void avl_tree_destroy(struct avl_tree *tree)
{
    CHECK_TREE(tree);
    
    avl_tree_clear(tree);

    free(tree);
}

void avl_tree_clear(struct avl_tree *tree)
{
    CHECK_TREE(tree);
    
    if (!tree->body->root)
        return;

    struct stack *s = stack_create(tree->body->stack_capacity);
        
    struct avl_tree *current = tree->body->root;
    struct avl_tree *last_destroyed = 0;
        
    for (;;)
    {
        for (; current; current=current->item.left)
            stack_push(s, (intptr_t)current);
                
        if (!stack_peek(s, (intptr_t *) &current))
            break;
                
        if (current->item.right && last_destroyed != current->item.right)
        {
            current = current->item.right;
            continue;
        }
            
        stack_pop(s, (intptr_t *) &last_destroyed);
        free(last_destroyed);
        current = 0;
    }
    
    tree->body->stack_capacity = stack_capacity(s);

    stack_destroy(s);

    tree->body->nodes = 0;
}

void avl_tree_set_comp(struct avl_tree *tree, avl_tree_less less)
{
    CHECK_TREE(tree);
    tree->body->less = less;
}

int avl_tree_height(struct avl_tree *tree)
{
    CHECK_ITEM(tree);
    return 0;
}

intptr_t avl_tree_get_value(struct avl_tree *tree)
{
    CHECK_ITEM(tree);
    return tree->item.value;
}

void avl_tree_set_value(struct avl_tree *tree, intptr_t value)
{
    CHECK_ITEM(tree);
    tree->item.value = value;
}

struct avl_tree *avl_tree_search(struct avl_tree *tree, intptr_t key)
{
    CHECK_TREE(tree);
    
    avl_tree_less less = tree->body->less;
    
    for (struct avl_tree *root=tree->body->root; root; )
    {
        if (less(root->item.key, key))
            root = root->item.right;
        else if (less(key, root->item.key))
            root = root->item.left;
        else 
            return root;
    }

    return 0;
}

bool avl_tree_search_value(struct avl_tree *tree, intptr_t key, intptr_t *value)
{
    CHECK_TREE(tree);

    struct avl_tree *res = avl_tree_search(tree, key);
    
    if (!res)
        return false;
        
    *value = res->item.value;
    
    return true;
}

struct avl_tree *avl_tree_left(struct avl_tree *tree)
{
    CHECK_ITEM(tree);
    return tree->item.left;
}

struct avl_tree *avl_tree_right(struct avl_tree *tree)
{
    CHECK_ITEM(tree);
    return tree->item.right;
}

static 
struct avl_tree *new_tree(struct avl_tree *tree, intptr_t key, intptr_t value)
{
    struct avl_tree *ret = xmalloc(sizeof(struct avl_tree));
    
    ret->type = AVL_NODE;
    ret->body = tree->body;
    ret->item.key = key;
    ret->item.value = value;
    ret->item.left = 0;
    ret->item.right = 0;
    ret->item.balance = 0;
    
    ++tree->body->nodes;
    
    return ret;
}

static
void change_parent(struct avl_tree *old_root, struct avl_tree *root, struct avl_tree *parent)
{
    if (!parent)
    {
        root->body->root = root;
        return;
    }
    
    if (parent->item.left == old_root)
        parent->item.left = root;
    else if (parent->item.right == old_root)
        parent->item.right = root;
    else
        assert(false);
}

/*
           X +2                    Z
          / \                     / \
         t1  Z +1    ->          X  t3
            / \                 / \
           t2  t3              t1 t2

 http://oopweb.com/Algorithms/Documents/AvlTrees/Volume/AvlTrees.htm
 Case 1: X=+2 Z=+1 -> X=0 X=0 (insertion)
 Case 2: X=+2 Z=0  -> X=+1 Z=-1 (deletion)

*/
static
struct avl_tree *rotate_left(struct avl_tree *x)
{
    struct avl_tree *z = x->item.right;
    
    assert(z);
    
    x->item.right = z->item.left;
    z->item.left = x;
    
    if (z->item.balance == 0)
    {
        z->item.balance = -1;
        x->item.balance = 1;        
    } else {
        x->item.balance = 0;
        z->item.balance = 0;
    }
    
    return z;
}

/*
     X              Z 0
    / \            / \
   Z   t3   ->    t1  X 0
  / \                / \
 t1  t2             t2  t3

 http://oopweb.com/Algorithms/Documents/AvlTrees/Volume/AvlTrees.htm
 Case 1: X=-2 Z=-1 -> X=0 X=0 (insertion)
 Case 2: X=-2 Z=0  -> X=-1 Z=+1 (deletion)

*/
static
struct avl_tree *rotate_right(struct avl_tree *x)
{
    struct avl_tree *z = x->item.left;
    
    assert(z);
    
    x->item.left = z->item.right;
    z->item.right = x;
    
    if (z->item.balance == 0)
    {
        x->item.balance = -1;
        z->item.balance = 1;
    } else {
        x->item.balance = 0;
        z->item.balance = 0;
    }
    
    return z;
}

/*
     -2X               X               Y
      / \             / \            /   \
    +1Z  t4          Y  t4          Z     X
    / \      ->     / \     ->     /\     /\
   t1  Y+1         Z  t3          t1 t2  t3 t4
      / \         / \
     t2  t3      t1 t2
     
    case1: X=-2  Y=1   Z=+1      X=0  Y=0  Z=-1
    case2: X=-2  Y=0   Z=+1  =>  X=0  Y=0  Z=0
    case3: X=-2  Y=-1  Z=+1      X=1  Y=0  Z=0

*/


static
struct avl_tree *rotate_left_right(struct avl_tree *x)
{
    struct avl_tree *z = x->item.left;
    assert(z);

    struct avl_tree *y = z->item.right;
    assert(y);
    
    z->item.right = y->item.left;
    x->item.left  = y->item.right;
    y->item.left  = z;
    y->item.right = x;
    
    if (y->item.balance == 0)
    {
        z->item.balance = 0;
        x->item.balance = 0;
        
    } 
    else if (y->item.balance == 1)
    {
        x->item.balance = 0;
        z->item.balance = -1;
        y->item.balance = 0;
    } 
    else if (y->item.balance == -1)
    {
        x->item.balance = 1;
        z->item.balance = 0;
        y->item.balance = 0;
    }
    else assert (false);

    return y;
}

/*
  http://oopweb.com/Algorithms/Documents/AvlTrees/Volume/AvlTrees.htm

            X                 X                    Y
           / \               / \                  / \
          t1  Z     ->      t1  Y    ->          X   Z
             / \               / \              / |  | \
            Y   t4            t2  Z            t1 t2 t3 t4
           / \                   / \
          t2 t3                 t3 t4

    case1: X=+2  Y=+1  Z=-1      X=-1  Y=0  Z=0
    case2: X=+2  Y=0   Z=-1  =>  X =0  Y=0  Z=0
    case3: X=+2  Y=-1  Z=-1      X =0  Y=0  Z=1

*/

static
struct avl_tree *rotate_right_left(struct avl_tree *x)
{
    struct avl_tree *z = x->item.right;
    assert(z);

    struct avl_tree *y = z->item.left;
    assert(y);
    
    x->item.right = y->item.left;
    z->item.left = y->item.right;
    y->item.left = x;
    y->item.right = z;
    
    if (y->item.balance == 0)
    {
        x->item.balance = 0;
        z->item.balance = 0;
    }
    else if (y->item.balance == 1)
    {
        x->item.balance = -1;
        z->item.balance = 0;
        y->item.balance = 0;
    }
    else if (y->item.balance == -1)
    {
        x->item.balance = 0;
        z->item.balance = 1;
        y->item.balance = 0;
    }
    else assert (false);
    
    return y;
}

void avl_tree_insert(struct avl_tree *tree, intptr_t key, intptr_t value)
{
    CHECK_TREE(tree);
    
    if (!tree->body->root)
    {
        tree->body->root = new_tree(tree, key, value);
        return;
    }

    avl_tree_less less = tree->body->less;
    
    struct stack *s = stack_create(tree->body->stack_capacity);

    // find place where to insert
    struct avl_tree *changed_tree = 0;
    
    for (struct avl_tree *root=tree->body->root; ; )
    {
        stack_push(s, (intptr_t)root);
        
        if (less(root->item.key, key))
        {
            if (root->item.right)
            {
                root = root->item.right;
                continue;
            }

            changed_tree = new_tree(tree, key, value);
            root->item.right = changed_tree;
        } else {
            if (root->item.left)
            {
                root = root->item.left;
                continue;
            }
            changed_tree = new_tree(tree, key, value);
            root->item.left = changed_tree;
        }
        break;
    }
    
    assert(changed_tree);
    
    // propage balance factors and rebalance if needed
    struct avl_tree *root = 0;
    
    while (stack_pop(s, (intptr_t *) &root))
    {
        if (changed_tree == root->item.left)
        {
            if (root->item.balance == 1)
            {
                root->item.balance = 0;
                break;
            }
            
            if (root->item.balance == 0)
            {
                root->item.balance = -1;
                changed_tree = root;
                continue;
            }

            if (root->item.balance == -1)
            {
                struct avl_tree *new_root;
                
                assert(changed_tree->item.balance != 0);
                
                if (changed_tree->item.balance == -1)
                    new_root = rotate_right(root);
                else
                    new_root = rotate_left_right(root);
                    
                struct avl_tree *parent = 0;
                stack_pop(s, (intptr_t *) &parent);
                change_parent(root, new_root, parent);
                break;
            }
        } 
        else if (changed_tree == root->item.right)
        {
            if (root->item.balance == -1)
            {
                root->item.balance = 0;
                break;
            }

            if (root->item.balance == 0)
            {
                root->item.balance = 1;
                changed_tree = root;
                continue;
            }
            if (root->item.balance == 1)
            {
                struct avl_tree *new_root;

                assert(changed_tree->item.balance != 0);

                if (changed_tree->item.balance == 1)
                    new_root = rotate_left(root);
                else
                    new_root = rotate_right_left(root);
                    
                struct avl_tree *parent = 0;
                stack_pop(s, (intptr_t *) &parent);
                change_parent(root, new_root, parent);
                break;
            }
        }
        else assert(false);
    }
    
    stack_destroy(s);
}

void avl_tree_delete(struct avl_tree *tree, intptr_t key)
{
    CHECK_TREE(tree);
    
    if (!tree->body->root)
        return;

    avl_tree_less less = tree->body->less;
    
    struct stack *s = stack_create(tree->body->stack_capacity);

    // find place where to delete
    struct avl_tree *node_for_deletion = 0;
    
    for (struct avl_tree *root=tree->body->root; root; )
    {
        stack_push(s, (intptr_t)root);

        if (root->item.key == key)
        {
            node_for_deletion = root;
            break;
        }
        
        if (less(root->item.key, key))
            root = root->item.right;
        else
            root = root->item.left;
    }
    
    if (!node_for_deletion)
        goto fail1;
        
    

fail1:
    stack_destroy(s);
}

struct avl_tree *avl_tree_clone(struct avl_tree *tree)
{
    return 0;
}

struct avl_tree *avl_tree_random(unsigned seed, int nodes, int min_value, int max_value)
{
    if (!nodes)
        return 0;
    
    srandom(seed);
    
    struct avl_tree *tree = avl_tree_create();
    unsigned range = max_value - min_value;
    
    for (int i=0; i<nodes; ++i)
    {
        int value = min_value + (random() % range);
        
        avl_tree_insert(tree, value, 0);
    }

    return tree;
}

struct avl_tree_display_context
{
    char buf[128];
    char *sbeg;
    char *send;
    bool display_ascii;
};

static
void avl_tree_display_context_init(struct avl_tree_display_context *ctx)
{
    ctx->sbeg = ctx->buf;
    ctx->send = &ctx->buf[sizeof(ctx->buf)/sizeof(ctx->buf[0])-1];
    ctx->display_ascii = false;
    
    *ctx->sbeg = 0;
    *ctx->send = 0;
}

void avl_tree_display_increase(struct avl_tree_display_context *ctx, char c)
{
    int maxlen = ctx->send - ctx->sbeg;
    
    if (maxlen < 5)
        return;
        
    ctx->sbeg[0] = ' ';
    ctx->sbeg[1] = c;
    ctx->sbeg[2] = ' ';
    ctx->sbeg[3] = ' ';
    ctx->sbeg[4] = 0;
    
    ctx->sbeg += 4;
}

void avl_tree_display_descrease(struct avl_tree_display_context *ctx)
{
    int maxdec = ctx->sbeg - ctx->buf;
    
    if (maxdec > 4)
        maxdec = 4;
        
    ctx->sbeg -= maxdec;
    ctx->sbeg[0] = 0;
}

void _avl_tree_display(struct avl_tree *tree, 
                       struct avl_tree_display_context *ctx)
{
    CHECK_ITEM(tree);

    if (ctx->display_ascii && isascii(tree->item.key)) printf("(%c) [%d]\n", (int)tree->item.key, tree->item.balance);
     else printf("(%d) [%d]\n", (int)tree->item.key, tree->item.balance);
    
    if (tree->item.left)
    {
        printf("%s |\n", ctx->buf);
        printf("%s L--", ctx->buf);
        avl_tree_display_increase(ctx, tree->item.right ? '|' : ' ');
        _avl_tree_display(tree->item.left, ctx);
        avl_tree_display_descrease(ctx);
    }
    if (tree->item.right)
    {
        printf("%s |\n", ctx->buf);
        printf("%s R--", ctx->buf);
        avl_tree_display_increase(ctx, ' ');
        _avl_tree_display(tree->item.right, ctx);
        avl_tree_display_descrease(ctx);
    }
}

void avl_tree_display(struct avl_tree *tree)
{
    CHECK_TREE(tree);
    
    if (!tree->body->root)
    {
        printf("Empty tree!\n");
        return;
    }

    struct avl_tree_display_context ctx;
    
    avl_tree_display_context_init(&ctx);
    
    _avl_tree_display(tree->body->root, &ctx);
}

void avl_tree_display_ascii(struct avl_tree *tree)
{
    CHECK_TREE(tree);
    
    if (!tree->body->root)
    {
        printf("Empty tree!\n");
        return;
    }

    struct avl_tree_display_context ctx;

    avl_tree_display_context_init(&ctx);

    ctx.display_ascii = true;
    _avl_tree_display(tree->body->root, &ctx);
}
