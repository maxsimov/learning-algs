#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef unsigned (*hash_func)(void *key);
typedef int (*hash_compare)(void *key1, void *key2);


struct hash_table *hash_create(hash_func hf, hash_compare comp, int size);
void hash_destroy(struct hash_table *h);

void hash_insert(struct hash_table *h, void *key, void *obj);
void hash_insert_int(struct hash_table *h, void *key, uintptr_t value);
void *hash_delete(struct hash_table *h, void *key);
void *hash_lookup(struct hash_table *h, void *key);
bool hash_lookup_int(struct hash_table *h, void *key, uintptr_t *value);

unsigned jenkins_one_at_a_time_hash_str(void *key);
