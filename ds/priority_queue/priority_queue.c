#include <stdio.h>
#include <assert.h>

#include "priority_queue.h"


struct Pri_Queue
{
    sorted_list_t *sorted_list;
};


pri_queue_t *PriQueueCreate(compare_func_t cmp_func, const void *param)
{
	pri_queue_t *new_queue = NULL;
	new_queue = (pri_queue_t*)malloc(sizeof(pri_queue_t));
	if(!new_queue)
	{
		return NULL;
	}
	
	new_queue->sorted_list = SortedListCreate(cmp_func, param);
 
 	return new_queue;
}


void PriQueueDestroy(pri_queue_t *pri_queue)
{
	assert(pri_queue);

	SortedListDestroy(pri_queue->sorted_list);
	free(pri_queue);
}


void *PriQueuePeek(const pri_queue_t *pri_queue)
{
	assert(pri_queue);

	return SortedListIterGetData(SortedListBegin(pri_queue->sorted_list));
}


size_t PriQueueSize(const pri_queue_t *pri_queue)
{
	assert(pri_queue);

	return SortedListSize(pri_queue->sorted_list);
}


int PriQueueIsEmpty(const pri_queue_t *pri_queue)	/* return value empty - 1, not empty - 0 */
{
	assert(pri_queue);

	if(SortedListSize(pri_queue->sorted_list) == 0)
	{
		return 1;
	}
	return 0;
}


int PriQueueEnqueue(pri_queue_t *pri_queue, const void *data)
{
	assert(pri_queue);

	SortedListInsert(pri_queue->sorted_list, data);
	return 0;
}


void PriQueueDequeue(pri_queue_t *pri_queue)
{
	assert(pri_queue);

	SortedListRemove(SortedListBegin(pri_queue->sorted_list));
}


void PriQueueClear(pri_queue_t *pri_queue)
{
	assert(pri_queue);

	while(!PriQueueIsEmpty(pri_queue))
	{
		PriQueueDequeue(pri_queue);
	}	
}


void PriQueueErase(pri_queue_t *pri_queue, is_match_t match_func, const void *param)
{
	sorted_list_iter_t iter = SortedListBegin(pri_queue->sorted_list);

	assert(pri_queue);
	
	while(!SortedListIterIsEqual(iter,SortedListEnd(pri_queue->sorted_list)))
	{
		if(match_func(SortedListIterGetData(iter), param)){
			SortedListRemove(iter);
			return;
		}
		iter = SortedListIterNext(iter);
	}
}










