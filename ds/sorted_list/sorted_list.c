#include <stdio.h>
#include <assert.h>

#include "sorted_list.h"


struct SortedList
{
    is_before_func_t is_before;
    dlist_t *d_list;
    const void *param;
};


sorted_list_t *SortedListCreate(is_before_func_t is_before, const void *param)
{
	sorted_list_t *new_list = NULL;
	new_list = (sorted_list_t*)malloc(sizeof(sorted_list_t));
	if(NULL == new_list)
	{
		return NULL;
	}
	
	new_list->d_list = DListCreate();

	if(!new_list->d_list)
	{
		free(new_list);
		return NULL;
	}

	new_list->is_before = is_before;
	new_list->param = param;

	return new_list;
}


void SortedListDestroy(sorted_list_t *list)
{
	DListDestroy(list->d_list);
	free(list);
}


sorted_list_iter_t SortedListBegin(sorted_list_t *list)
{
	sorted_list_iter_t iter_begin;
	
	iter_begin.d_list_iter = DListBegin(list->d_list);
	
	return iter_begin;
}


sorted_list_iter_t SortedListEnd(sorted_list_t *list)
{
	sorted_list_iter_t iter;
	assert(list);

	iter.list = list;
	iter.d_list_iter = DListEnd(list->d_list);

	return iter;

}


sorted_list_iter_t SortedListIterNext(sorted_list_iter_t iter)
{
	iter.d_list_iter = DListIterNext(iter.d_list_iter);
	return iter;	
}

sorted_list_iter_t SortedListIterPrev(sorted_list_iter_t iter)
{
	iter.d_list_iter = DListIterPrev(iter.d_list_iter);	
	return iter;
}


int SortedListIterIsEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	return DListIterIsEqual(iter1.d_list_iter,iter2.d_list_iter);
}


void* SortedListIterGetData(sorted_list_iter_t iter)
{
	return DListIterGetData(iter.d_list_iter);
}


sorted_list_iter_t SortedListInsert(sorted_list_t *list, const void *item)
{	
	sorted_list_iter_t iter = SortedListBegin(list);
	sorted_list_iter_t iter_end = SortedListEnd(list);
	

	for(; !SortedListIterIsEqual(iter, iter_end); iter = SortedListIterNext(iter))
	{
		if(list->is_before(item, SortedListIterGetData(iter), list->param))
		{
			break;
		}
	} 
	DListInsert(iter.d_list_iter, item);
	return iter;
}


void SortedListRemove(sorted_list_iter_t which)
{
	DListRemove(which.d_list_iter);
}


sorted_list_iter_t SortedListFind(sorted_list_iter_t from, sorted_list_iter_t to, const void *what)
{
	for(; !SortedListIterIsEqual(from, to); from = SortedListIterNext(from))
	{
		if(SortedListIterGetData(from) == what)
		{
			return from;		
		}	
	}
	return from; 
}


sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, match_func_t is_match_func, void *param)
{
	for(; !SortedListIterIsEqual(from, to); from = SortedListIterNext(from))
	{
		if(is_match_func(SortedListIterGetData(from) ,param))
		{
			return from;
		}
	}
	return from;
}


int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, act_func_t action_func, void *param)
{
	return DListForEach(from.d_list_iter, to.d_list_iter, action_func, param);
}


size_t SortedListSize(sorted_list_t *list)
{
	return DListCount(list->d_list);
}


sorted_list_t *SortListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iter_t iter = SortedListBegin(src_list);
	
	for(; !SortedListIterIsEqual(iter, SortedListEnd(src_list)); iter = SortedListIterNext(iter))
	{
		SortedListInsert(dest_list, SortedListIterGetData(iter));
	}
	
	return dest_list;
}











