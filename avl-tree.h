#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef bool (*avl_tree_less)(intptr_t a, intptr_t b);

struct avl_tree *avl_tree_create();
void avl_tree_set_comp(struct avl_tree *tree, avl_tree_less less);
void avl_tree_destroy(struct avl_tree *tree);
void avl_tree_clear(struct avl_tree *tree);
void avl_tree_display(struct avl_tree *tree);
void avl_tree_display_ascii(struct avl_tree *tree);
int avl_tree_height(struct avl_tree *tree);
intptr_t avl_tree_get_value(struct avl_tree *tree);
void avl_tree_set_value(struct avl_tree *tree, intptr_t value);
struct avl_tree *avl_tree_search(struct avl_tree *tree, intptr_t key);
bool avl_tree_search_value(struct avl_tree *tree, intptr_t key, intptr_t *value);

struct avl_tree *avl_tree_left(struct avl_tree *tree);
struct avl_tree *avl_tree_right(struct avl_tree *tree);
void avl_tree_insert(struct avl_tree *tree, intptr_t key, intptr_t value);
void avl_tree_delete(struct avl_tree *tree,intptr_t key);
struct avl_tree *avl_tree_clone(struct avl_tree *tree);

struct avl_tree *avl_tree_random(unsigned seed, int nodes, int min_value, int max_value);
