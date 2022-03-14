#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "doubly_linked_list.h"

struct DListNode {
    const void* data;
    struct DListNode* next;
    struct DListNode* prev;
};


struct DList 
{
    dnode_t head_sentinel;
    dnode_t tail_sentinel;
};


dlist_t *DListCreate()
{
	dlist_t *new_list = NULL;
	
	new_list = (dlist_t*)malloc(sizeof(dlist_t));
	if(NULL == new_list)
	{
		return NULL;
	}

	new_list->head_sentinel.prev = NULL;
	new_list->head_sentinel.next = &new_list->tail_sentinel;
	new_list->head_sentinel.data = NULL;

	new_list->tail_sentinel.prev = &new_list->head_sentinel;
	new_list->tail_sentinel.next = NULL;
	new_list->tail_sentinel.data = NULL;

	return new_list;
}


void DListDestroy(dlist_t *list)
{
	assert(list);

	while (!DListIterIsEqual(DListBegin(list), DListEnd(list)))
	{
		DListRemove(DListBegin(list));
	}
	
	free(list);
}


dlist_iter_t DListBegin(dlist_t *list)
{
	dlist_iter_t head_iter;

	assert(list);

	head_iter.list = list;
	head_iter.node = list->head_sentinel.next;

	return head_iter;
}


dlist_iter_t DListEnd(dlist_t *list)
{
	dlist_iter_t end_iter;

	assert(list);

	end_iter.list = list;
	end_iter.node = &list->tail_sentinel;

	return end_iter;
}

dlist_iter_t DListInsert(dlist_iter_t iter, const void *item)
{
	dnode_t* new_node = NULL;
    assert(iter.node);

    new_node = (dnode_t*)malloc(sizeof(dnode_t));
    if (NULL == new_node)
    {
    	return DListEnd(iter.list);
    }
    new_node->data = item;
    new_node->prev = iter.node->prev;
    new_node->next = iter.node;

    iter.node->prev->next = new_node;
    iter.node->prev = new_node;
    iter.node = new_node;

    return iter;
}


void DListRemove(dlist_iter_t iter)
{
	dnode_t *temp = iter.node;
 	if(NULL == temp)
   	{
        return;
    }

   	iter.node->prev->next = iter.node->next;
   	iter.node->next->prev = iter.node->prev;

 	free(iter.node);
}


size_t DListCount(dlist_t *list)
{
	size_t count = 0;
	dlist_iter_t from = DListBegin(list); 
	dlist_iter_t to = DListEnd(list); 

	assert(list);	

	for	(count = 0; !DListIterIsEqual(from, to) ; from = DListIterNext(from))
	{
		++count;
	}

	return count;
}


dlist_iter_t DListIterNext(dlist_iter_t iter)
{
	assert(iter.node);

	iter.node = iter.node->next;
	return iter;
}


dlist_iter_t DListIterPrev(dlist_iter_t iter)
{
	assert(iter.node);

	iter.node = iter.node->prev;
	return iter;
}


int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	assert(iter1.node && iter2.node);

	return iter1.node == iter2.node;
}


void* DListIterGetData(dlist_iter_t iter)
{
	assert(iter.node);

	return (void*)iter.node->data;
}


dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match_func, void *param)
{
	assert(from.node && to.node);

	for(; !DListIterIsEqual(from, to); from = DListIterNext(from))
	{
		if(is_match_func((void*)from.node->data, param))
		{
			return from;
		}
	}		
	return from;
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param)
{
	assert(from.node && to.node);

	for(; !DListIterIsEqual(from, to); from = DListIterNext(from))
	{
		if(action_func((void*)from.node->data, param))
		{
			return 0;
		}	
	}
	return 1;
}


size_t DListSize(dlist_t *list)
{
	size_t count = 0;
	dlist_iter_t from = DListBegin(list); 
	dlist_iter_t to = DListEnd(list); 

	assert(list);	

	for	(count = 0; !DListIterIsEqual(from, to); from = DListIterNext(from))
	{
		if(from.node)
		{
			++count;
		}
	}

	return count;
}



dlist_iter_t DListPushFront(dlist_t *list, const void *data)
{
	assert(list);

	return DListInsert(DListBegin(list), data);
}


dlist_iter_t DListPushBack(dlist_t *list, const void *data)
{
	assert(list);

	return DListInsert(DListEnd(list), data);
}


void *DListPopFront(dlist_t *list)
{
	void *removed_item = NULL;
	dlist_iter_t iter = DListBegin(list);

	assert(list);
	
	removed_item = (void*)iter.node->data;
	DListRemove(iter);

	return removed_item;
}


void *DListPopBack(dlist_t *list)
{
	void *removed_item = NULL;
	dlist_iter_t iter = DListIterPrev(DListEnd(list));

	assert(list);

	removed_item = (void*)iter.node->data;
	DListRemove(iter);	

	return removed_item;
}


dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t begin, dlist_iter_t end)
{
	/* disconnect list */
	dnode_t *last_node = NULL;
	last_node = end.node->prev;
	begin.node->prev->next = end.node;
	end.node->prev = begin.node->prev;
	
	
	/* connect list to new list */
	where.node->prev->next = begin.node;
	begin.node->prev = where.node->prev;
	where.node->prev = last_node;
	last_node->next = where.node;

	return end;	
}





