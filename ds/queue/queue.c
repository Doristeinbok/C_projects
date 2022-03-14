#include <stdio.h>
#include <assert.h>

#include "singly_linked_list.h"
#include "queue.h"


struct Queue 
{
	 slist_t *list;
};


queue_t *QueueCreate(void)
{
	queue_t *q = NULL;
	q = (queue_t*)malloc(sizeof(queue_t));
	if(NULL == q)
	{
		return NULL;
	}
	
	q->list = SListCreate();
	return q;
}



/*destroy queue*/



void QueueDestroy(queue_t *queue)
{
	assert(queue);
	SListDestroy(queue->list);
	queue->list = NULL;
	free(queue);
}


/* insert new item to back of the queue */

void QueueEnqueue(queue_t *queue, const void *val)
{
	assert(queue);
	SListInsert(SListEnd(queue->list), val);
}


/* pop item from the front of the queue*/

void QueueDequeue(queue_t *queue)
{
	assert(queue);
	SListRemove(SListBegin(queue->list));
}

/*get value of the front item of the queue*/

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	return SListIterGetData(SListBegin(queue->list));
}


/*return the sizeof queue*/

size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	return SListCount(queue->list);
}


/*check if queue is empty*/

int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	return SListIterIsEqual(SListBegin(queue->list), SListEnd(queue->list));
}



































