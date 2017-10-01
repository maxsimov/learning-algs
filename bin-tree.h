#pragma once

struct bin_tree
{
    int key;
    void *data;

    struct bin_tree *left;
    struct bin_tree *right;
};

struct bin_tree *bin_tree_create(int root_key, void *data);
void bin_tree_destroy(struct bin_tree *tree);
void bin_tree_display(struct bin_tree *tree);

typedef void (*bin_tree_bfs_callback)(void *context, struct bin_tree *tree, 
                                      int level, int breadth_index);

void bin_tree_BFS(struct bin_tree *tree, bin_tree_bfs_callback visit, 
                  void *context);

void bin_tree_BFS_full(struct bin_tree *tree, bin_tree_bfs_callback visit, 
                       void *context);

typedef void (*bin_tree_dfs_callback)(void *context, struct bin_tree *tree);

void bin_tree_DFS_preorder(struct bin_tree *tree, bin_tree_dfs_callback visit, 
                           void *context);
void bin_tree_DFS_inorder(struct bin_tree *tree, bin_tree_dfs_callback visit, 
                           void *context);
void bin_tree_DFS_postorder(struct bin_tree *tree, bin_tree_dfs_callback visit, 
                           void *context);

int bin_tree_height(struct bin_tree *tree);
