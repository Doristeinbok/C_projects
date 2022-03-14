#include <stdio.h>
#include <string.h>

#include "queue.h"


int main()
{
	queue_t *queue = NULL;
	
	int a = 5;
	char b [15] = "Dumbeldore";
	int c = 100;
	
	queue = QueueCreate();
	
	printf("testing...\n");
	
	if(!(QueueSize(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(QueueIsEmpty(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	QueueEnqueue(queue, &a);
	
	if(!(QueueSize(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)QueuePeek(queue) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	QueueEnqueue(queue, b);
	QueueDequeue(queue);
	
	if(!(strcmp((char*)QueuePeek(queue),"Dumbeldore") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	QueueEnqueue(queue, &c);
	
	if(!(strcmp((char*)QueuePeek(queue),"Dumbeldore") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(QueueSize(queue) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(QueueIsEmpty(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	QueueDestroy(queue);
	
	printf("all is good!\n");

	return 0;
}
