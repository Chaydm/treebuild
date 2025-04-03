#include "hash.h"
#include <stdlib.h>

// 创建hashtable
HashTable *hash_create(int size)
{
    HashTable *hash = (HashTable *)malloc(sizeof(HashTable));
    if (!hash)
        return NULL;
    hash->size = size;
    hash->table = (HashEntry *)calloc(size, sizeof(HashEntry));
    if (!hash->table)
    {
        free(hash);
        return NULL;
    }
    return hash;
}

// 释放内存
void hash_destroy(HashTable *ht)
{
    if (ht)
    {
        free(ht->table);
        free(ht);
    }
}

// 哈希函数
unsigned int hash_func(HashTable *ht, int key)
{
    return (unsigned int)key % ht->size;
}

// 插入
int hash_insert(HashTable *ht, int key, int value)
{
    if (!ht)
        return -1;
    unsigned int index = hash_func(ht, key);
    for (int i = 0; i < ht->size; i++)
    {
        unsigned int cur = (index + i) % ht->size;
        if (ht->table[cur].used)
            continue;
        ht->table[cur].key = key;
        ht->table[cur].value = value;
        ht->table[cur].used = 1;
        return 1;
    }
    return -1;
}

// 查找指定键的值
int hash_search(HashTable *ht, int key, int *value)
{
    if (!ht || !value)
        return -1;
    unsigned int index = hash_func(ht, key);
    for (int i = 0; i < ht->size; i++)
    {
        unsigned int cur = (index + i) % ht->size;
        if (!ht->table[cur].used)
            return -1;
        if (ht->table[cur].key == key)
        {
            *value = ht->table[cur].value;
            return 1;
        }
    }
    return -1;
}

// 删除指定键值对
int hash_delete(HashTable *ht, int key)
{
    if (!ht)
        return -1;
    unsigned int index = hash_func(ht, key);
    for (int i = 0; i < ht->size; i++)
    {
        unsigned int cur = (index + i) % ht->size;
        if (!ht->table[cur].used)
            return -1;
        if (ht->table[cur].key == key)
        {
            ht->table[cur].used = 0;
            return 1;
        }
    }
    return -1;
}
