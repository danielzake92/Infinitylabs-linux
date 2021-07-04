/********************************************************************************
 *  FILENAME:  scheduler.h  DEVELOPER: Daniel Zaken   TEAM: Blue&Green                 
 *                                                                             
 *  Reviwer:  Gil Friedman also Itamar Aron                                           
 *                                                                              
 *  PURPOSE:  LIB for modifying & creating a task scheduler.             		
 *                                                                              
 *******************************************************************************/
#ifndef __ILRD_SCHEDULER_H__
#define __ILRD_SCHEDULER_H__

#include <stddef.h> /*required for size_t type*/
#include "task.h"
#include "pq_heap.h" /*required for lib operations*/

typedef struct scheduler scheduler_t;

typedef enum run_status
{
	RUNNING,
	FAILURE,
	NO_TASKS,
	STOPPED
}status_t;

/****************************************************************************/
/*
Description: Creates a new instance of the scheduler object.
Parameters: NONE
Return Value: pointer to new scheduler object
Time Complexity: O(1)
*/
scheduler_t *SchedulerCreate(void);
/****************************************************************************/
/*
Description: Destroys the scheduler object.
Parameters: 
	-scheduler: pointer to scheduler object
Return Value: NONE
Time Complexity: O(n)
*/
void SchedulerDestroy(scheduler_t *scheduler);
/****************************************************************************/
/*
Description: Adds a new task to the scheduler.
Parameters:
	-scheduler: pointer to scheduler object
	-operation_func: function pointer which is executed when task is
	-destroy_func: function pointer which frees up all allocated memory associated with the task's data.
	-param: pointer to additional data that is maintained by task, is fed as argument to operation func and destroy func when appropriate.
Return Value: UID of new task which has been added to scheduler
Time Complexity: O(n)
*/
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler,
							int (*operation_func)(void *param), 
							void(*destroy_func)(void *param), 
							time_t time_interval, 
							void* param);
/****************************************************************************/
/*
Description: Removes the task with specified uid from the scheduler.
Parameters:
	-scheduler: pointer to scheduler object
	-uid: uid of task to be removed.
Return Value: Success(0) if the task with specified uid was found and removed, and Failure(1) otherwise
Time Complexity: O(n)
*/
int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid);
/****************************************************************************/
/*
Description: Begins scheduler execution of tasks, while running main function will be unresponsive. Tasks will be executed and returned to the scheduler if the return values of their operation functions returns a value of zero, otherwise they will be removed from scheduler and destroyed. Will exit from run only if a task in scheduler executes SchedulerStop function, if the scheduler empties of tasks, or if there is an allocation error during returning a task to the scheduler after execution.
Parameters:
	-scheduler: pointer to scheduler object
Return Value: 3 possibilities enum - 
	FAILURE - Allocation failure
	NO_TASKS - all tasks executed and not returned to schedule 
	STOPPED - scheduler run ended by SchedulerStop Task.
Time Complexity: N/A
*/
status_t SchedulerRun(scheduler_t *scheduler);
/****************************************************************************/
/*
Description: Stops the running of the scheduler, can only be applied during run by adding it as the operation function of a task within scheduler.
Parameters:
	-scheduler: pointer to scheduler object
Return Value: NONE
Time Complexity: O(1)
*/
void SchedulerStop(scheduler_t *scheduler);
/****************************************************************************/
/*
Description: Return the number of tasks in the scheduler.
Parameters:
	-scheduler: pointer to scheduler object
Return Value: Number of tasks held in scheduler
Time Complexity: O(n)
*/
size_t SchedulerCount(const scheduler_t *scheduler);
/****************************************************************************/
/*
Description: Returns whether the scheduler is empty or not.
Parameters:
	-scheduler: pointer to scheduler object
Return Value: True(1) if the scheduler is empty, and False(0) otherwise.
Time Complexity: O(1)
*/
int SchedulerIsEmpty(const scheduler_t *scheduler);
/****************************************************************************/
/*
Description: Clears all tasks from the scheduler.
Parameters:
	-scheduler: pointer to scheduler object
Return Value: NONE
Time Complexity: O(n)
*/
void SchedulerClear(scheduler_t *scheduler);

#endif

