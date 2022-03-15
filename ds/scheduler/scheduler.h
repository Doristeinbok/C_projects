#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>

#include "task.h"
#include "priority_queue.h"


typedef struct scheduler scheduler_t;
/*typedef struct task task_t;*/

/*creates new scheduler engine*/
extern scheduler_t *SchedulerCreate();

/*destroy scheduler*/
extern void SchedulerDestroy(scheduler_t *scheduler);

/* insert new task to the scheduler engine*/
extern unique_id_t SchedulerTaskAdd(scheduler_t *scheduler, task_func_t task, 
						size_t interval_in_secs, const void *param);

/* remove task from scheduler engine*/
extern void SchedulerTaskCancel(scheduler_t *scheduler, unique_id_t uid);

/* run the scheduler engine */
extern int SchedulerRun(scheduler_t *scheduler);

/* stop running scheduler */
extern void SchedulerStop(scheduler_t *scheduler);

/* return the size of the scheduler */
extern size_t SchedulerSize(scheduler_t *scheduler);

/*check if scheduler is empty*/
extern int SchedulerIsEmpty(scheduler_t *scheduler);

/*stop the scheduler*/
extern scheduler_t *SchedulerClear(scheduler_t *scheduler);

#endif
