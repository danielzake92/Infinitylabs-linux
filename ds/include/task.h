/********************************************************************************
 *  FILENAME:  task.h  DEVELOPER: Daniel Zaken   TEAM: Blue                     * 
 *                                                                              *
 *  Reviwer:   Gil Friedman                                                     * 
 *                                                                              *
 *  PURPOSE:   LIB for modifying & creating tasks for the task scheduler.		*
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_TASK_H__
#define __ILRD_TASK_H__

#include <stddef.h> /*required for size_t type*/
#include "uid.h" /* for generating uid*/

typedef struct task task_t;

/****************************************************************************/
/*
Description: Creates a new instance of a task object.
Parameters:
	operation_func: function pointer which begins the tasks instructions
	destroy_func: function pointer which frees memory associated with the task
	interval: number of seconds between executions of the task
	param: pointer to additional data which is fed to operation_func
Return Value: pointer to new task object
Time Complexity: O(1)
*/

task_t *TaskCreate(int(*operation_func)(void *param), 
					void(*destroy_func)(void *param), 
					time_t interval_in_sec, 
					void* param);
					
/****************************************************************************/
/*
Description: Destroys the input task object.
Parameters:
	-task: pointer to task object
Return Value: NONE
Time Complexity: O(1)
*/			
	
void TaskDestroy(task_t *task);

/****************************************************************************/
/*
Description: Returns the uid of the task.
Parameters:
	-task: pointer to task object
Return Value: uid of input task object
Time Complexity: O(1)
*/

ilrd_uid_t TaskGetUid(const task_t *task);

/****************************************************************************/
/*
Description: Executes the task.
Parameters:
	-task: pointer to task object
Return Value: Success(0) if the task is to be repeated, and Failure(1) if it is to be destroyed.
Time Complexity: Complexity of operation function of task
*/

int TaskExecute(task_t *task);

/****************************************************************************/
/*
Description: Updates the task execution time
Parameters:
	-task: pointer to task object
Return Value: NONE
Time Complexity: O(1)
*/

void TaskUpdateTimeToRun(task_t *task);

/****************************************************************************/
/*
Description: Returns the task's execution time.
Parameters:
	-task: pointer to task object
Return Value: returns the time at which the task is to be executed.
Time Complexity: O(1)
*/

time_t TaskGetExecutionTime(const task_t *task);

/****************************************************************************/
/*
Description: determines whether the input task matches the input uid.
Parameters:
	-task: pointer to task object as void pointer
	-uid: pointer to uid as void pointer
Return Value: True(1) if the uid matches the task, and False(0) otherwise
Time Complexity: O(1)
*/

int TaskIsMatchUID(const void *task, const void *uid);

/****************************************************************************/
#endif
