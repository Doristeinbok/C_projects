#ifndef __SINGLY_LIST_H__
#define __SINGLY_LIST_H__

#include <stdlib.h>

typedef struct SList slist_t;

typedef struct SListNode snode_t;

typedef struct
{
	snode_t* node;
	slist_t* list;
} slist_iter_t;

typedef int (*action_func_t)(void *data, void *param);
typedef int (*match_func_t)(const void *data, void *param);


/* Create new list */
extern slist_t *SListCreate();

/* Delete the list */
extern void SListDestroy(slist_t *list);

/* Add a new item to the list */
extern void SListInsert(slist_iter_t iter, const void *item);

/* Return number of nodes in list */	
extern size_t SListCount(slist_t *list);

/* Return iterator that points to the first node */
extern slist_iter_t SListBegin(slist_t *list);

/* Return iterator that points to the node after last item */
extern slist_iter_t SListEnd(slist_t *list);

/* Return next iterator */
extern slist_iter_t SListIterNext(slist_iter_t iter);

/* Remove data after iterator */
extern void SListRemove(slist_iter_t iter);

/* Return 1/0 if iterators are equals/not respectively */
extern int SListIterIsEqual(slist_iter_t iter1, slist_iter_t iter2);

/* Return data of node pointed by iter */
extern void *SListIterGetData(slist_iter_t iter);


extern slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match_func, void *param);


extern int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param);



#endif
