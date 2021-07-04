/********************************************************************************
 *  FILENAME:  task.c  DEVELOPER: Daniel Zaken   TEAM: Blue                     * 
 *                                                                              *
 *  Reviwer:   Gil Friedman                                                     * 
 *                                                                              *
 *  PURPOSE:   LIB for modifying & creating tasks for the task scheduler.		*
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for malloc function*/
#include "task.h"/*My implemented task library*/
#include "utl.h"/*Utilities for defines and macros */
/****************************************************************************/
struct task
{
	ilrd_uid_t uid;
	int(*operation_func)(void *param);
	void(*destroy_func)(void *param);
	time_t interval_in_sec; 
	time_t execution_time;
	void* data;
};
/****************************************************************************/
task_t *TaskCreate(int(*operation_func)(void *param), 
					void(*destroy_func)(void *param), 
					time_t interval_in_sec, 
					void* param)
{
	task_t *task = NULL;
	
	assert(operation_func);
	assert(destroy_func);
	
	task = (task_t *)malloc( sizeof(task_t) );	

	if ( NULL == task)
	{
		return NULL;
	}

	task->uid = UIDCreate();
	task->operation_func = operation_func;
	task->destroy_func = destroy_func;
	task->interval_in_sec = interval_in_sec;
	TaskUpdateTimeToRun(task); 
	task->data = param;
	
	return task;
}		
/****************************************************************************/
void TaskDestroy(task_t *task)
{
	assert(task);
	
	task->destroy_func( task->data );
	
	task->operation_func = NULL;
	task->destroy_func = NULL;
	task->data = NULL;
	task->uid = UIDGetBadUID();
	free(task);
}	
/****************************************************************************/
ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(task);
	
	return(task->uid);
}
/****************************************************************************/
int TaskExecute(task_t *task)
{
	assert(task);
	
	return (task->operation_func( task->data ));
}
/****************************************************************************/
void TaskUpdateTimeToRun(task_t *task)
{
	assert(task);
	
	task->execution_time =  time(NULL) + task->interval_in_sec;
}
/****************************************************************************/		
time_t TaskGetExecutionTime(const task_t *task)
{
	assert(task);
	return (task->execution_time);
}
/****************************************************************************/
int TaskIsMatchUID(const void *data1, const void *data2)
{
	return(UIDIsSame( TaskGetUid((task_t*)data1), *((ilrd_uid_t*)data2) ));	
}
