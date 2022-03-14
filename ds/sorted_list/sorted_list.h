#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h>
#include "doubly_linked_list.h"


typedef struct SortedList sorted_list_t;

typedef int (*is_before_func_t)(const void *new_elem, const void *curr_elem, const void *param);
typedef int (*act_func_t)(void *data, void *param);
/* typedef int (*match_func_t)(void *data, void *param); */

typedef struct
{
	dlist_iter_t d_list_iter;
	sorted_list_t *list;
} sorted_list_iter_t;

/* Create new list */
extern sorted_list_t *SortedListCreate(is_before_func_t is_before, const void *param);

/* Delete the list */
extern void SortedListDestroy(sorted_list_t *list);


extern sorted_list_iter_t SortedListBegin(sorted_list_t *list);
extern sorted_list_iter_t SortedListEnd(sorted_list_t *list);
extern sorted_list_iter_t SortedListIterNext(sorted_list_iter_t iter);
extern sorted_list_iter_t SortedListIterPrev(sorted_list_iter_t iter);
extern int SortedListIterIsEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2);
extern void* SortedListIterGetData(sorted_list_iter_t iter);


/* insert item to the list O(n) */
extern sorted_list_iter_t SortedListInsert(sorted_list_t *list, const void *item);


/* Remove item from the list */
extern void SortedListRemove(sorted_list_iter_t which);

extern sorted_list_iter_t SortedListFind(sorted_list_iter_t from, sorted_list_iter_t to, const void *what);

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, match_func_t is_match_func, void *param); 

extern int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, act_func_t action_func, void *param);

extern size_t SortedListSize(sorted_list_t *list);

/* Merge lists */ 
sorted_list_t *SortListMerge(sorted_list_t *dest_list, sorted_list_t *src_list);


#endif




