#include <assert.h>
#include <time.h> /* time() */
#include <unistd.h> /*sleep */

#include "scheduler.h"
#include "task.h"


static int RUN = 1;
static int CompareTime(const void *new_elem, const void *curr_elem, const void *param);

int MatchUID(const void *curr_item, const void *param);


struct scheduler
{
	pri_queue_t *p_queue;
};



scheduler_t *SchedulerCreate()
{
	
	scheduler_t *new_scheduler = NULL;
	
	new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_scheduler)
	{
		return NULL;
	}
	
	new_scheduler->p_queue = NULL;
	
	new_scheduler->p_queue = PriQueueCreate(CompareTime, NULL);
	if (NULL == new_scheduler->p_queue)
	{
		free(new_scheduler);
		return NULL;
	}
	
	return new_scheduler;
}


void SchedulerDestroy(scheduler_t *scheduler)
{	
	assert(scheduler);

	SchedulerClear(scheduler);
	PriQueueDestroy(scheduler->p_queue);
	free(scheduler);
}


unique_id_t SchedulerTaskAdd(scheduler_t *scheduler, task_func_t task, size_t interval_in_secs, const void *param)
{
		task_t *new_task = NULL;
		
		new_task = TaskCreate(task, interval_in_secs, param);
		if (NULL == new_task)
		{
			return uid_null_uid;
		}
		
		TaskUpdateTime(new_task, time(NULL));
		PriQueueEnqueue(scheduler->p_queue, new_task);
		return TaskGetUID(new_task);
}



void SchedulerTaskCancel(scheduler_t *scheduler, unique_id_t uid)
{
	assert(scheduler);
	
	PriQueueErase(scheduler->p_queue, MatchUID, &uid);
}


int SchedulerRun(scheduler_t *scheduler)
{
	task_t *curr_task = NULL;
	RUN = 1;
	assert(scheduler);

	while(!PriQueueIsEmpty(scheduler->p_queue) && RUN)
	{
		curr_task = PriQueuePeek(scheduler->p_queue);
		sleep(TaskGetTime(curr_task) - time(NULL));
		PriQueueDequeue(scheduler->p_queue);
		
		if(TaskRun(curr_task))
		{
			TaskUpdateTime(curr_task, time(NULL));
			PriQueueEnqueue(scheduler->p_queue, curr_task);
		}
		else
		{
			TaskDestroy(curr_task);
		}
	}
	return 1;
}


void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);

	(void)scheduler;
	RUN = 0;
}


size_t SchedulerSize(scheduler_t *scheduler)
{
	assert(scheduler);

	return PriQueueSize(scheduler->p_queue);
}



int SchedulerIsEmpty(scheduler_t *scheduler)
{
	assert(scheduler);

	return PriQueueIsEmpty(scheduler->p_queue);
}


scheduler_t *SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler);

	while (!SchedulerIsEmpty(scheduler))
	{
		TaskDestroy(PriQueuePeek(scheduler->p_queue));
		PriQueueDequeue(scheduler->p_queue);
	}
	return scheduler;
}



/* ------------------------ helper functions ------------------------------- */



static int CompareTime(const void *new_elem, const void *curr_elem, const void *param)
{
	(void)param;
	return TaskGetTime(new_elem) < TaskGetTime(curr_elem);
}


int MatchUID(const void *curr_item, const void *param)
{
	return UIDIsEqual(TaskGetUID(curr_item), TaskGetUID(param));
}
