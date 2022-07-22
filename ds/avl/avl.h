#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>

typedef int (*compare_func_t)(const void *new_elem, const void *curr_elem, const void *param);
typedef int (*action_func_t)(void *data, const void *param); /* SUCCES = 0, FAIL = 1*/

typedef enum Traversal {IN_ORDER, PRE_ORDER, POST_ORDER} traversal_t;

typedef struct AVL avl_t;

/* Create new AVL*/
extern avl_t *AvlCreate(compare_func_t cmp_func, const void *param);

/* Destroy AVL*/
extern void AvlDestroy(avl_t *avl);

/* Size of AVL*/
extern size_t AvlSize(const avl_t *avl);

/* Height of root */
extern size_t AvlHeight(const avl_t *avl); 

/* If AVL is Empty return 1  */
extern int AvlIsEmpty(const avl_t *avl);

/* Insert a new node - 0 if succes, 1 fail */
extern int AvlInsert(avl_t *avl, const void *data); 

/* Remove a node  */
extern void AvlRemove(avl_t *avl, const void *data); 

/* Find a node in AVL  */
extern const void *AvlFind(avl_t *avl, const void *data);

extern int AvlForEach(avl_t *avl, action_func_t action_func, const void *param, traversal_t order);

#endif

