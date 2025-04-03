#pragma once

typedef struct _LinkedHashEntry {
    int key;
    int value;
    struct _LinkedHashEntry *next; 
} LinkedHashEntry;

typedef struct LinkedHashTable {
    int size;
    LinkedHashEntry **table; // 使用连续数组存储
} LinkedHashTable;

LinkedHashTable *hash_link_create(int size);
void hash_link_destroy(LinkedHashTable *ht);
int hash_link_insert(LinkedHashTable *ht, int key, int value);
int hash_link_search(LinkedHashTable *ht, int key, int *value);
int hash_link_delete(LinkedHashTable *ht, int key);
unsigned int hash_link_func(LinkedHashTable *ht, int key);
