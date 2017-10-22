#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef bool (*rb_tree_less)(intptr_t a, intptr_t b);

struct rb_tree *rb_tree_create();
void rb_tree_destroy(struct rb_tree *tree);
void rb_tree_clear(struct rb_tree *tree);

void rb_tree_set_less(struct rb_tree *tree, rb_tree_less less);
struct rb_item *rb_tree_search(struct rb_tree *tree, intptr_t key);
bool rb_tree_search_value(struct rb_tree *tree, intptr_t key, intptr_t *value);
intptr_t rb_tree_get_value(struct rb_item *item);
void rb_tree_set_value(struct rb_item *item, intptr_t value);
void rb_tree_insert(struct rb_tree *tree, intptr_t key, intptr_t value);
bool rb_tree_delete(struct rb_tree *tree, intptr_t key);
bool rb_tree_check(struct rb_tree *tree, char *str, size_t size);
