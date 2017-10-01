#include <stdio.h>
#include <string.h>
#include "hash.h"

union obj_data {
    int value;
};


struct obj_for_hash
{
    char *key;
    union obj_data data;
};

int hash_str_cmp(void *key1, void *key2)
{
    return strcmp(key1, key2) == 0;
}

void test_hash_1()
{
    struct obj_for_hash obj[] = {
        { "Enigma",  { 3 } },
        { "Allei", { 5 } },
        { "Maxtel", { 6 } },
    };
    
    struct hash_table *ht = hash_create(jenkins_one_at_a_time_hash_str, hash_str_cmp, 2);
    
    for (int i=0; i<sizeof(obj)/sizeof(obj[0]); ++i)
    {
        printf(" inserting %s -> %d\n", obj[i].key, obj[i].data.value);
        hash_insert(ht, obj[i].key, &obj[i].data);
    }

    for (int i=0; i<sizeof(obj)/sizeof(obj[0]); ++i)
    {
        union obj_data *data = hash_lookup(ht, obj[i].key);
        
        printf("lookup %s ->", obj[i].key);
        
        if (!data)
        {
            printf(" null\n");
            continue;
        }
        
        printf(" %d\n", data->value);
    }

    hash_destroy(ht);
}

int main(int argc, char *argv[])
{
    test_hash_1();
    return 0;
}