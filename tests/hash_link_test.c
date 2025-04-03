#include <stdio.h>
#include "src/hash_link.h"

void test_hash_create()
{
    // create
    LinkedHashTable *ht = hash_link_create(10);
    if (!ht)
    {
        fprintf(stderr, "create table faild\n");
    }

    // inset
    for (int i = 0; i < 100; i++)
    {
        hash_link_insert(ht, i, i * i);
    }

    //remove
    for (int i = 0; i < 10; i++)
    {
        hash_link_delete(ht, i * i - i);
    }
    
    //search
    for (int i = 0; i < 100; i++)
    {
        int value;
        int status = hash_link_search(ht, i, &value);
        if (status == 1)
        {
            printf("key = %d,value = %d \n", i, value);
        }
        else
        {
            printf("key =%d,value can not find\n", i);
        }
    }
    hash_link_destroy(ht);
}

int main(){
    test_hash_create();
    printf("test passed");
}