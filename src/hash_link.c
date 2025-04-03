#include "hash_link.h"
#include <stdlib.h>


// 创建LinkedHashTable
LinkedHashTable *hash_link_create(int size)
{
    LinkedHashTable *hash = (LinkedHashTable *)malloc(sizeof(LinkedHashTable));
    if (!hash)
        return NULL;
    hash->size = size;
    hash->table = (LinkedHashEntry **)calloc(size, sizeof(LinkedHashEntry *));
    if (!hash->table)
    {
        free(hash);
        return NULL;
    }
    return hash;
}

// 释放内存
void hash_link_destroy(LinkedHashTable *ht)
{
    if (ht)
    {
        // 释放每个位置的链表
        for (int i = 0; i < ht->size; i++)
        {
            LinkedHashEntry *cur = ht->table[i];
            while (cur)
            {
                LinkedHashEntry *temp = cur;
                cur = cur->next;
                free(temp);
                
            }
        }
        free(ht->table);
        free(ht);
    }
}

// 哈希函数
unsigned int hash_link_func(LinkedHashTable *ht, int key)
{
    return (unsigned int)key % ht->size;
}

// 插入
int hash_link_insert(LinkedHashTable *ht, int key, int value)
{
    if (!ht)
        return -1;
    unsigned int index = hash_link_func(ht, key);
    LinkedHashEntry *entry = (LinkedHashEntry *)malloc(sizeof(LinkedHashEntry));
    if (!entry)
        return -1;
    entry->key = key;
    entry->value = value;
    entry->next = ht->table[index];
    ht->table[index] = entry;
    return 1;
}

// 查找指定键的值
int hash_link_search(LinkedHashTable *ht, int key, int *value)
{
    if (!ht || !value)
        return -1;
    unsigned int index = hash_func(ht, key);
    LinkedHashEntry *head = ht->table[index];
    while (head)
    {
        if (head->key == key)
        {
            *value = head->value;
            return 1;
        }
        head = head->next;
    }

    return -1;
}

// 删除指定键值对
int hash_link_delete(LinkedHashTable *ht, int key)
{
    if (!ht)
        return -1;
    unsigned int index = hash_func(ht, key);
    LinkedHashEntry *cur = ht->table[index];
    LinkedHashEntry *pre = NULL;
    while (cur)
    {
        if (cur->key == key)
        {
            if (!pre)
            {
                ht->table[index] = cur->next;
            }
            else
            {
                pre->next = cur->next;
            }
            free(cur);
            return 1;
        }
        pre = cur;
        cur = cur->next;
    }
    return -1;
}
