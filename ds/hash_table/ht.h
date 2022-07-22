#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h>

typedef int (*cmp_func_t)(void *curr_data, void *requested_data);
typedef size_t (*hash_func_t)(const void *new_elem);
typedef int (*hash_action_func_t)(void *data, void *action_param); /* SUCCESS = 0, FAIL = 1*/

typedef struct Hash hash_t;

/* Create new hash table*/
hash_t *HashCreate(hash_func_t hash_func, cmp_func_t cmp_func, size_t hash_size);

/* Destroy hash table*/
extern void HashDestroy(hash_t *hash);

/* Insert a new data - 0 if succes, 1 fail */
extern int HashInsert(hash_t *hash, const void *data);

/* Remove a data from hash table */
extern void HashRemove(hash_t *hash, const void *data);

/* Number of element in table in total */
extern size_t HashSize(hash_t *hash);

/* If hash table is Empty return 1 */
extern int HashIsEmpty(hash_t *hash);

/* Find a data in the table  */
extern const void *HashFind(hash_t *hash, const void *data);

/* Execute operation on each element in table */
extern int HashForEach(hash_t *hash, hash_action_func_t action_func, void *action_param);


extern float HashLoad(hash_t *hash);
#endif
