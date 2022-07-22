#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>

typedef int (*compare_func_t)(const void *new_elem, const void *curr_elem, const void *param);
typedef int (*action_func_t)(void *data, const void *param);

typedef struct BST bst_t;
typedef struct BSTNode bst_node_t;

typedef struct
{
    bst_t *bst;
    bst_node_t *node;
} bst_iter_t;

extern bst_t *BstCreate(compare_func_t cmp_func, const void *param);

extern void BstDestroy(bst_t *bst);

extern size_t BstSize(bst_t *bst);

extern int BstIsEmpty(bst_t *bst);

extern bst_iter_t BstInsert(bst_t *bst, const void *data);

extern void BstRemove(bst_iter_t iter);

extern bst_iter_t BstBegin(bst_t *bst);
extern bst_iter_t BstEnd(bst_t *bst);
extern bst_iter_t BstIterNext(bst_iter_t iter);
extern bst_iter_t BstIterPrev(bst_iter_t iter);

extern int BstIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);

extern void *BstIterGetData(bst_iter_t iter);

extern bst_iter_t BstFind(bst_t *bst, const void *data);

extern int BstForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, const void *param);


#endif
