#include <stdio.h>

#include "priority_queue.h"


int Compare(const void *new_elem, const void *curr_elem, const void *param);
int MatchFunc(const void *curr_item, const void *param);


void test1(void);

int main() 
{
	test1();
	return 0;
}



/*******************************************/



void test1(void)
{
	int num = 1;
	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;
	int num_4 = 4;

	pri_queue_t *new_pri_queue = PriQueueCreate(Compare, &num);
	
	PriQueueEnqueue(new_pri_queue, &num_3); 
	PriQueueEnqueue(new_pri_queue, &num_1); 
	PriQueueEnqueue(new_pri_queue, &num_4); 
	PriQueueEnqueue(new_pri_queue, &num_2); 

	if(1 != *(int*)PriQueuePeek(new_pri_queue))
	{
		printf("error in line %d\n", __LINE__);
	}

	PriQueueDequeue(new_pri_queue);
	if(2 != *(int*)PriQueuePeek(new_pri_queue))
	{
		printf("error in line %d\n", __LINE__);
	}

	if(3 != PriQueueSize(new_pri_queue))
	{
		printf("error in line %d\n", __LINE__);
	}

	PriQueueErase(new_pri_queue, MatchFunc, &num_3);

	if(2 != PriQueueSize(new_pri_queue))
	{
		printf("error in line %d\n", __LINE__);
	}

	PriQueueClear(new_pri_queue);
	if(0 != PriQueueSize(new_pri_queue))
	{
		printf("error in line %d\n", __LINE__);
	}






	PriQueueDestroy(new_pri_queue);
	
}



/*****************************************************************/



int Compare(const void *new_elem, const void *curr_elem, const void *param)
{
	(void)param;

	if (*(int*)new_elem < *(int*)curr_elem)
	{
		return 1;
	}

	return 0;
}


int MatchFunc(const void *curr_item, const void *param)
{
	if(*(int*)curr_item == *(int*)param)
	{
		return 1;
	}
	return 0;
}
