#include <stdio.h>
#include <stdlib.h>

#include "scheduler.h"


static int task1(const void *param);
static int task2(const void *param);
static int task3(const void *param);


int main()
{
	scheduler_t *scheduler = SchedulerCreate();
	unique_id_t uid1 = uid_null_uid;
	
	
	if((SchedulerSize(scheduler) == 0))
	{
		printf("SUCESS. SchedulerCreate and SchedulerSize\n");
	}
	else
	{
		printf("FAIL. SchedulerCreate and SchedulerSize\n");
	}
	
	if((SchedulerIsEmpty(scheduler) == 1))
	{
		printf("SUCCES. SchedulerIsEmpty\n");
	}
	else
	{
		printf("FAIL. SchedulerIsEmpty\n");
	}
	
	uid1 = SchedulerTaskAdd(scheduler, task1, 1, "2");
	
	if((SchedulerSize(scheduler) == 1))
	{
		printf("SUCESS. SchedulerTaskAdd\n");
	}
	else
	{
		printf("FAIL. SchedulerTaskAdd\n");
	}
	
	SchedulerTaskCancel(scheduler,uid1);
	
	if((SchedulerSize(scheduler) == 0))
	{
		printf("SUCESS. SchedulerTaskCancel\n");
	}
	else
	{
		printf("FAIL. SchedulerTaskCancel\n");
	}
	SchedulerTaskAdd(scheduler, task2, 5, "1");
	SchedulerTaskAdd(scheduler, task3, 2, "3");
	
	if((SchedulerSize(scheduler) == 2))
	{
		printf("SUCESS. SchedulerTaskAdd\n");
	}
	else
	{
		printf("FAIL. SchedulerTaskAdd\n");
	}
	
	SchedulerClear(scheduler);
	
	if((SchedulerSize(scheduler) == 0))
	{
		printf("SUCESS. SchedulerClear\n");
	}
	else
	{
		printf("FAIL. SchedulerClear\n");
	}


	SchedulerTaskAdd(scheduler, task2, 5, "1");
	SchedulerTaskAdd(scheduler, task3, 7, "3");

	SchedulerRun(scheduler);
	

	SchedulerDestroy(scheduler);
	
	return 0;
}



/****************************** Helper functions ******************************/



static int task1(const void *param)
{
	printf("hello i am task1 you see me every 1 secound, %s\n", (char*)param);
	return 1;
}

static int task2(const void *param)
{
	printf("hello i am task2. you see me every 5 secound, %s\n", (char*)param);
	return 1;
}

static int task3(const void *param)
{
	printf("hello i am task3 you see me every 2 secound, %s\n", (char*)param);
	return 1;
}


