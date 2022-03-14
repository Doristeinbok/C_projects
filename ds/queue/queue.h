#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include "queue.h"


typedef struct Queue queue_t;

/*creat new queue*/
extern queue_t *QueueCreate(void);

/*destroy queue*/
extern void QueueDestroy(queue_t *queue);

/* insert new item to back of the queue */
extern void QueueEnqueue(queue_t *queue, const void *val); 

/* pop item from the front of the queue*/
extern void QueueDequeue(queue_t *queue); 

/*get value of the front item of the queue*/
extern void *QueuePeek(const queue_t *queue); 

/*return the sizeof queue*/
extern size_t QueueSize(const queue_t *queue);

/*check if queue is empty*/
extern int QueueIsEmpty(const queue_t *queue);	/* return value empty - 1, not empty - 0 */




#endif	
