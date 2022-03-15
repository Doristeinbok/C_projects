#include <time.h> /* get current time */
#include <stdlib.h> /* malloc */ 
#include <assert.h>
#include "task.h"


struct task
{
	unique_id_t uid;
	task_func_t task;
	const void *param;
	time_t timing;
	size_t interval;
};


task_t *TaskCreate(task_func_t task, size_t interval_in_secs, const void *param)
{
	task_t *new_task = NULL;
	
	new_task = (task_t*)malloc(sizeof(task_t));
	if (NULL == new_task)
	{
		return NULL;
	}
	
	new_task->uid = UIDGenerate();	
	new_task->task = task;
	new_task->param = param;
	new_task->interval = interval_in_secs;
	return new_task;
}



void TaskDestroy(task_t *task)
{
	assert(task);
	free(task);
}


void TaskUpdateTime(task_t *task, time_t curr_time)
{
	assert(task);
	task->timing = curr_time + task->interval;
}


int TaskRun(const task_t *task)
{
	assert(task);
	return task->task(task->param);
}


unique_id_t TaskGetUID(const task_t *task)
{
	assert(task);
	return task->uid;
}


time_t TaskGetTime(const task_t *task)
{
	assert(task);
	return task->timing;
}




