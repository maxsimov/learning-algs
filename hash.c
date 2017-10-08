#include <stdlib.h>
#include "hash.h"

struct hash_bucket
{
    struct hash_bucket *next;
    
    void *key;
    void *obj;
};

struct hash_table
{
    hash_func hf;
    hash_compare hc;
    
    struct hash_bucket **buckets;
    int size;
};

struct hash_table *hash_create(hash_func hf, hash_compare comp, int size)
{
    struct hash_table *ht = malloc(sizeof(struct hash_table));
    
    if (!ht)
        return 0;
        
    ht->buckets = malloc(sizeof(struct hash_bucket *)*size);
    
    if (!ht->buckets)
    {
        free(ht);
        return 0;
    }
    
    ht->hf = hf;
    ht->hc = comp;
    ht->size = size;
    
    for (int i=0; i<size; ++i)
        ht->buckets[i] = 0;
        
    return ht;
}

void hash_destroy(struct hash_table *h)
{
    if (!h)
        return;
        
    for (int i=0; i<h->size; ++i)
    {
        struct hash_bucket *cur = h->buckets[i];
        
        while (cur)
        {
            struct hash_bucket *next = cur->next;
            free(cur);
            cur = next;
        }
    }
    
    free(h->buckets);
    free(h);
}

static
struct hash_bucket *_hash_create_new_bucket(void *key, void *obj)
{
    struct hash_bucket *b = malloc(sizeof(struct hash_bucket));
    b->next = 0;
    b->key = key;
    b->obj = obj;
    
    return b;
}

void hash_insert(struct hash_table *ht, void *key, void *obj)
{
    unsigned hash = (*ht->hf)(key);
    int index = hash % ht->size;
    
    if (ht->buckets[index])
    {
        struct hash_bucket *cur = ht->buckets[index];
        struct hash_bucket *last = cur;
        
        while (cur)
        {
            last = cur;
            
            if ( (*ht->hc)(key, cur->key) )
            {
                cur->key = key;
                cur->obj = obj;
                return;
            }
            
            cur = cur->next;
        }
        
        last->next = _hash_create_new_bucket(key, obj);
    } else {
        ht->buckets[index] = _hash_create_new_bucket(key, obj);
    }
}

void hash_insert_int(struct hash_table *h, void *key, uintptr_t value)
{
    hash_insert(h, key, (void *)value);
}

void *hash_delete(struct hash_table *ht, void *key)
{
    unsigned hash = (*ht->hf)(key);
    int index = hash % ht->size;

    if (!ht->buckets[index])
        return 0;
        
    struct hash_bucket **prev = &ht->buckets[index];
    struct hash_bucket *cur = *prev;
    
    while (cur)
    {
        if ( (*ht->hc)(key, cur->key) )
        {
            *prev = cur->next;
            void *obj = cur->obj;
            free(cur);
            
            return obj;
        }
        
        prev = &cur->next;
        cur = cur->next;
    }

    return 0;    
}

struct hash_bucket *_hash_lookup(struct hash_table *ht, void *key)
{
    unsigned hash = (*ht->hf)(key);
    int index = hash % ht->size;

    if (!ht->buckets[index])
        return 0;
        
    struct hash_bucket *cur = ht->buckets[index];
    
    while (cur)
    {
        if ( (*ht->hc)(key, cur->key) )
            return cur;
        cur = cur->next;
    }

    return 0;    
}

void *hash_lookup(struct hash_table *ht, void *key)
{
    struct hash_bucket *b = _hash_lookup(ht, key);
    
    return b ? b->obj : 0;
}

bool hash_lookup_int(struct hash_table *h, void *key, uintptr_t *value)
{
    struct hash_bucket *b = _hash_lookup(h, key);
    
    if (!b)
        return false;
    
    *value = (uintptr_t)b->obj;
    
    return true;
}

unsigned jenkins_one_at_a_time_hash_str(void *key)
{
    const unsigned char *str = (const unsigned char *)key;
    
    unsigned hash = 0;
    
    while (*str)
    {
        hash += *str++;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
 
  return hash;
}
