#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h> /* size_t type */
#include "uid.h" /* return value unique_id_t */


typedef struct task task_t;


typedef int (*task_func_t)(const void* param);

/* create a new task */
extern task_t *TaskCreate(task_func_t task, size_t interval_in_secs, const void *param);

/* deallocate memory of task */
extern void TaskDestroy(task_t *task);

/* update the timing of task according to current time and its respective time interval */
extern void TaskUpdateTime(task_t *task, time_t curr_time);

/* run the respective function */
extern int TaskRun(const task_t *task);

/* get task uid */
extern unique_id_t TaskGetUID(const task_t *task);

/* get task timing */
extern time_t TaskGetTime(const task_t *task);

#endif
