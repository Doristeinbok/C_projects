#include <stdio.h>
#include <stddef.h>

#include "hash_table.h"
#include "doubly_linked_list.h"


struct Hash
{
    hash_func_t hash_func;
    cmp_func_t comp_func;
    size_t hash_size;
    dlist_t **index_arr;
    const void* param;
};


hash_t *HashCreate(hash_func_t hash_func, cmp_func_t cmp_func, size_t hash_size, const void *param)
{
    hash_t *new_hash = NULL;
    new_hash = (hash_t*)malloc(sizeof(hash_t));
    if(NULL == new_hash)
    {
        return NULL;
    }

    new_hash->hash_func = hash_func;
    new_hash->comp_func = cmp_func;
    new_hash->param = param;
    new_hash->hash_size = hash_size;
    new_hash->index_arr = (dlist_t**)calloc(hash_size, sizeof(dlist_t*)); 
    if (NULL == new_hash->index_arr)
    {
        free(new_hash);
        return NULL;
    }
    

    return new_hash;
}


void HashDestroy(hash_t *hash)
{
    size_t i = 0;
    /* destroy every doubly list */
    for(i = 0; i < hash->hash_size; ++i)
    {
        if(NULL != hash->index_arr[i])
        {
            DListDestroy(hash->index_arr[i]);
        }
    }

    /* destroy index_arr and hash */
    free(hash->index_arr);
    free(hash);
}


int HashInsert(hash_t *hash, const void *data)
{
    /* 1. send the data (key) to hash function to receive index */
    size_t index = hash->hash_func(data);
    index = index % hash->hash_size;

    /* 2. if index point to NULL -> create doubly list */
    if(NULL == hash->index_arr[index])
    {
        hash->index_arr[index] = DListCreate();
        if(NULL == hash->index_arr[index])
        {
            return 1;
        }
    }

    /* 3. insert into the doubly list */
    DListInsert(DListBegin(hash->index_arr[index]), data);

    return 0;
}


void HashRemove(hash_t *hash, const void *data)
{
    size_t index = hash->hash_func(data);
    index = index % hash->hash_size;

    if(NULL != hash->index_arr[index])
    {
        DListRemove(DListFind(DListBegin(hash->index_arr[index]), DListEnd(hash->index_arr[index]), hash->comp_func, (void*)data));
    }
}


size_t HashSize(hash_t *hash)
{
    size_t size = 0;
    size_t i = 0;
    size_t hash_size = hash->hash_size;
    for(i = 0; i < hash_size; ++i)
    {
        if(hash->index_arr[i])
        {
            size += DListSize(hash->index_arr[i]);
        }
    }

    return size;
}


int HashIsEmpty(hash_t *hash)
{
    if(0 == HashSize(hash))
    {
        return 1;
    }
    return 0;
}


void *HashFind(hash_t *hash, const void *data)
{
    int index;
    index = hash->hash_func(data) % hash->hash_size;

    if(NULL != hash->index_arr[index])
    {
        return DListIterGetData(DListFind(
                    DListBegin(hash->index_arr[index]), 
                    DListEnd(hash->index_arr[index]), 
                    hash->comp_func, 
                    (void*)data
                ));
    }
    return NULL;
}

 
int HashForEach(hash_t *hash, hash_action_func_t action_func, const void *param)
{   
    size_t i = 0;
    for(i = 0; i < hash->hash_size; ++i)
    {
        if(hash->index_arr[i])
        {
            DListForEach(DListBegin(hash->index_arr[i]), 
                        DListEnd(hash->index_arr[i]), 
                        action_func,
                        (void*)param
            );
 
        }
    }
    return 0;
}
