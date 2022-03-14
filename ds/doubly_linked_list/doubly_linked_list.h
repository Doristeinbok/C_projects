#ifndef __SINGLY_LIST_H__
#define __SINGLY_LIST_H__

#include <stdlib.h>


typedef struct DList dlist_t;
typedef struct DListNode dnode_t;

typedef int (*action_func_t)(void *data, void *param);
typedef int (*match_func_t)(void *data, void *param);

typedef struct
{
	dnode_t* node;
	dlist_t* list;
} dlist_iter_t;


/* Create new list */
extern dlist_t *DListCreate();

/* Delete the list */
extern void DListDestroy(dlist_t *list);

extern dlist_iter_t DListBegin(dlist_t *list);
extern dlist_iter_t DListEnd(dlist_t *list);
extern dlist_iter_t DListInsert(dlist_iter_t iter, const void *item);
extern void DListRemove(dlist_iter_t iter);
extern size_t DListCount(dlist_t *list);

extern dlist_iter_t DListIterNext(dlist_iter_t iter);
extern dlist_iter_t DListIterPrev(dlist_iter_t iter);
extern int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2);
extern void* DListIterGetData(dlist_iter_t iter);

extern dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match_func, void *param);
int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param);


/* ----------- UPDATE -------------- */
size_t DListSize(dlist_t *list);

dlist_iter_t DListPushFront(dlist_t *list, const void *data);
dlist_iter_t DListPushBack(dlist_t *list, const void *data);
void *DListPopFront(dlist_t *list);
void *DListPopBack(dlist_t *list);

/* Cuts & pastes the range between begin and end into the list before 
   the element referred to by where.
   Returns iterator to the last spliced element.
   O(1) */

dlist_iter_t DListSplice(dlist_iter_t where, 
                         dlist_iter_t begin, 
                         dlist_iter_t end);



#endif
