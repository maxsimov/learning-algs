#include <assert.h>
#include "util.h"
#include "rb-tree.h"
#include "stack.h"

/*
  Used materials from 
  http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx

*/


struct rb_stats
{
    int new_red_nodes;
    int red_to_black;
    int insertions;
    int deletions;
    int lookups;
};

struct rb_tree
{
    struct rb_item *root;
    int nodes;
    rb_tree_less less;
    struct rb_stats stats;
    int stack_capacity;
};

struct rb_item
{
    bool red;
    intptr_t key;
    intptr_t value;
    struct rb_item *link[2];
    struct rb_tree *tree;
};

static
bool default_less(intptr_t a, intptr_t b)
{
    return a < b;   
}

static
struct rb_item *make_red_node(struct rb_tree *tree, intptr_t key, intptr_t value)
{
    struct rb_item *item = xmalloc(sizeof *item);
    
    item->red = true;
    item->key = key;
    item->value = value;
    item->link[0] = 0;
    item->link[1] = 0;
    item->tree = tree;
    
    tree->nodes++;
    tree->stats.new_red_nodes++;
    
    return item;
}

static
void make_black(struct rb_item *item)
{
    if (item->red)
    {
        item->red = false;
        item->tree->stats.red_to_black++;
    }
}

static
bool pop(struct stack *s, struct rb_item **item)
{
    bool ret = stack_pop(s, (intptr_t *) item);
    
    if (!ret)
        return false;

    assert(*item);

    return true;
}

static
void unwind(struct stack *s, struct rb_item **item)
{
    bool ret = pop(s, item);
    assert(ret);
}

static
void push(struct stack *s, struct rb_item *item)
{
    stack_push(s, (intptr_t)item);
}

static
bool is_red(struct rb_item *item)
{
    return item != 0 && item->red;
}

// main

struct rb_tree *rb_tree_create()
{
    struct rb_tree *tree = xmalloc(sizeof *tree);
    
    tree->root = 0;
    tree->nodes = 0;
    tree->less = default_less;
    memset(&tree->stats, 0, sizeof tree->stats);
    tree->stack_capacity = 4;
    
    return tree;
}

void rb_tree_destroy(struct rb_tree *tree)
{
    rb_tree_clear(tree);
    xfree(tree);
}

void rb_tree_clear(struct rb_tree *tree)
{
}

void rb_tree_set_less(struct rb_tree *tree, rb_tree_less less)
{
    tree->less = less;
}

struct rb_item *rb_tree_search(struct rb_tree *tree, intptr_t key)
{
    return 0;    
}

bool rb_tree_search_value(struct rb_tree *tree, intptr_t key, intptr_t *value)
{
    struct rb_item *item = rb_tree_search(tree, key);
    if (!item)
        return false;
    *value = item->value;
    return true;
}

intptr_t rb_tree_get_value(struct rb_item *item)
{
    return item->value;
}

void rb_tree_set_value(struct rb_item *item, intptr_t value)
{
    item->value = value;    
}

static
void fix_tree_after_insert(struct rb_item *parent, struct stack *s)
{
    for (;;)
    {
        if (!is_red(parent))
            break;
            
        struct rb_item *grant_parent = 0;
        
        if (!pop(s,  &grant_parent))
            break;
            
        
        
    }   
}

void rb_tree_insert(struct rb_tree *tree, intptr_t key, intptr_t value)
{
    if (!tree->root)
    {
        tree->root = make_red_node(tree, key, value);
        make_black(tree->root);
        return;
    }
    
    struct stack *s = stack_create(tree->stack_capacity);
    
    bool dir = 0;
    for (struct rb_item *root=tree->root; root; root=root->link[dir])
        dir = tree->less(key, root->key), push(s, root);

    struct rb_item *parent = 0;
    unwind(s, &parent);
    parent->link[dir] = make_red_node(tree, key, value);

    fix_tree_after_insert(parent, s);    

    tree->stack_capacity = stack_capacity(s);
    stack_destroy(s);
}

bool rb_tree_delete(struct rb_tree *tree, intptr_t key)
{
    return false;    
}

bool rb_tree_check(struct rb_tree *tree, char *str, size_t size)
{
    return false;
}
