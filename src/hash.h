#pragma once

typedef struct
{
    int key;
    int value;
    int used; // 标记是否已使用
} HashEntry;

typedef struct
{
    int size;
    HashEntry *table; // 使用连续数组存储
} HashTable;

HashTable *hash_create(int size);
void hash_destroy(HashTable *ht);
int hash_insert(HashTable *ht, int key, int value);
int hash_search(HashTable *ht, int key, int *value);
int hash_delete(HashTable *ht, int key);
unsigned int hash_func(HashTable *ht, int key);
