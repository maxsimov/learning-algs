#pragma once


struct bin_tree
{
    int key;

    struct bin_tree *left;
    struct bin_tree *right;
};

struct bin_tree *bin_tree_create(int root_key);
void bin_tree_destroy(struct bin_tree *tree);

void bin_tree_add(struct bin_tree *tree, int value);

// searches and lookups 

enum bin_tree_visit_type 
{ 
    bin_tree_new_level,
    bin_tree_current_level, 
    bin_tree_end_level, 
    bin_tree_end_tree 
};

typedef void (*bin_tree_callback)(struct bin_tree *tree, void *context, 
                                  enum bin_tree_visit_type visit, int level);

void bin_tree_breadth_first(struct bin_tree *tree, bin_tree_callback func, 
                            void *context);

