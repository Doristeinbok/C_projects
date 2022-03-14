#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "singly_linked_list.h"

struct SList
{
	snode_t *head;
	snode_t *tail;
};


struct SListNode {
	const void *data;
	struct SListNode* next;
};


slist_t *SListCreate()
{
	slist_t *new_list = NULL;
	new_list = (slist_t*)malloc(sizeof(slist_t));
	if (NULL == new_list)
	{
		return NULL;
	}
	
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->head = (snode_t*)malloc(sizeof(snode_t));
	if (NULL == new_list->head)
	{
		free(new_list);
		return NULL;
	}
	
	new_list->tail = new_list->head;
	
	new_list->head->next = NULL;
	new_list->head->data = NULL;

	return new_list;
}	


void SListDestroy(slist_t *list)
{
	slist_iter_t iter;
	for	(iter = SListBegin(list); !SListIterIsEqual(iter, SListEnd(list)); SListRemove(iter));
	free(list->head);
	free(list);
}


slist_iter_t SListBegin(slist_t *list)
{
	slist_iter_t head_iter;
	assert(list);

	head_iter.node = list->head;
	head_iter.list = list;
	return head_iter;
}


slist_iter_t SListEnd(slist_t *list)
{
	slist_iter_t iter;
	assert(list);
	
	iter.node = list->tail;
	iter.list = list;
	return iter;
}


slist_iter_t SListIterNext(slist_iter_t iter)
{
	assert(iter.node);
	iter.node = iter.node->next;
	return iter;
}


void SListInsert(slist_iter_t iter, const void *item)
{
    snode_t* new_node = NULL;
    assert(iter.node);
    new_node = (snode_t*)malloc(sizeof(snode_t));

    new_node->data = iter.node->data;
    new_node->next = iter.node->next;
    iter.node->next = new_node;
    iter.node->data = item;
    
    if (NULL == new_node->next)
    {
    	iter.list->tail = new_node;
    }
}


size_t SListCount(slist_t *list)
{
	size_t count = 0;
	slist_iter_t iter; 
	assert(list);	
	for	(iter = SListBegin(list), count = 0; !SListIterIsEqual(iter, SListEnd(list)) ; iter = SListIterNext(iter), ++count);
	return count;
}


void *SListIterGetData(slist_iter_t iter)
{
	return (void*)iter.node->data;
}

int SListIterIsEqual(slist_iter_t iter1, slist_iter_t iter2)
{
	return iter1.node == iter2.node;
}

void SListRemove(slist_iter_t iter)
{
	snode_t *temp = iter.node->next;
 	if(NULL == iter.node->next)
   	{
        return;
    }
 	iter.node->data = iter.node->next->data;
 	iter.node->next = iter.node->next->next;
 	
 	free(temp);
 	
	/* pointing the pointer tail in list to the new node in case it is the last node (pointing to NULL )*/
    if (NULL == iter.node->next)
    {
    	iter.list->tail = iter.node;
    }
}


slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match_func, void *param)
{
	assert(from.node && to.node);
	for	(; !SListIterIsEqual(from, to); from = SListIterNext(from))
	{
		if (is_match_func(from.node->data, param))
		{
			return from;
		}
	}
	return from;
}


int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param)
{
	assert(from.node && to.node);
	for	(; !SListIterIsEqual(from, to); from = SListIterNext(from))
	{
		if(!action_func((void *)from.node->data, param))
		{
			return 0;
		}
	}
	return 1;
}


