#pragma once

typedef unsigned (*hash_func)(void *key);
typedef int (*hash_compare)(void *key1, void *key2);


struct hash_table *hash_create(hash_func hf, hash_compare comp, int size);
void hash_destroy(struct hash_table *h);

void hash_insert(struct hash_table *h, void *key, void *obj);
void *hash_delete(struct hash_table *h, void *key);
void *hash_lookup(struct hash_table *h, void *key);

unsigned jenkins_one_at_a_time_hash_str(void *key);
