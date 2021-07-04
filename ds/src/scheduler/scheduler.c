/********************************************************************************
 *  FILENAME:  scheduler.c  DEVELOPER: Daniel Zaken   TEAM: Blue&Green                
 *                                                                              
 *  Reviwer:   Gil Friedman  also Itamar Aron                                                    
 *                                                                              
 *  PURPOSE:   LIB for modifying & creating a task scheduler.             		
 *                                                                              
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for malloc function*/
#include <unistd.h>/*Required for sleep function*/
#include "scheduler.h"/*My implemented scheduler library*/
#include "utl.h"/*Utilities for defines and macros */

static int SchedularCompare(const void *data1, const void *data2 );

struct scheduler
{
	p_queue_t *queue;
	task_t *curr_task;
	status_t to_stop; /*change the name - maybe state*/
};

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t *)malloc( sizeof(scheduler_t) );
	
	if( NULL == scheduler )
	{
		return NULL;
	}
	
	scheduler->queue = PQHeapCreate(SchedularCompare);
	
	if( NULL == scheduler->queue )
	{
		free( scheduler );
		return NULL;
	}
	
	scheduler->curr_task = NULL;
	scheduler->to_stop = NO_TASKS;
	
	return (scheduler);
}
/****************************************************************************/
void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);
	
	SchedulerClear(scheduler);
	
	PQHeapDestroy(scheduler->queue);
	
	scheduler->queue = NULL;
	scheduler->curr_task = NULL;
	
	free(scheduler);
}
/****************************************************************************/
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler,
							int (*operation_func)(void *param), 
							void(*destroy_func)(void *param), 
							time_t time_interval, 
							void* param)
{
	task_t *new_task = TaskCreate(operation_func ,destroy_func, time_interval, param); 
	
	if( NULL == new_task )
	{
		return (UIDGetBadUID());
	}
	assert(operation_func);
	assert(destroy_func);
	
	if( PQHeapEnqueue(scheduler->queue, (void*)new_task) != SUCCESS ) /*better tyo do !=success*/
	{
		TaskDestroy(new_task);
		return (UIDGetBadUID());
	}
		
	return (TaskGetUid(new_task));
}
/****************************************************************************/
int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid)
{
	task_t *temp = NULL;
	assert(scheduler);
	
	temp = PQHeapErase(scheduler->queue, TaskIsMatchUID, (void*)&uid);
	
	if ( NULL == temp )
	{
		return FAIL;
	}
	
	TaskDestroy(temp);
	
	return SUCCESS;
}


status_t SchedulerRun(scheduler_t *scheduler)
{
	time_t sleep_time = 0;
	int status = 0;
	assert(scheduler);
	scheduler->to_stop = RUNNING;
	
	while( ( scheduler->to_stop == RUNNING ) ) 
	{
		if ( PQHeapIsEmpty(scheduler->queue) == TRUE )
		{
			scheduler ->to_stop = NO_TASKS;
			break;
		}
		else if( scheduler ->to_stop == STOPPED)
		{
			break;
		}
		
		if( NULL == scheduler->curr_task )
		{
			scheduler->curr_task = PQHeapDequeue(scheduler->queue);
		}
		
		sleep_time = TaskGetExecutionTime(scheduler->curr_task) - time(NULL);
		
		while ( 0 < sleep_time )
		{
			sleep_time = sleep(TaskGetExecutionTime(scheduler->curr_task) - time(NULL));
		}
		
		status = TaskExecute(scheduler->curr_task);
		
		if( SUCCESS == status )
		{
			TaskUpdateTimeToRun(scheduler->curr_task);
			status = PQHeapEnqueue(scheduler->queue, (void*)scheduler->curr_task);
			if ( FAIL == status )
			{
				scheduler->to_stop = FAILURE;
				break;
			}
			scheduler->curr_task = NULL;
		}
		else
		{
			TaskDestroy(scheduler->curr_task);
			scheduler->curr_task = NULL;
		}
		
	}
	return scheduler->to_stop;
}
					

void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);
	scheduler->to_stop = STOPPED; 
}
/****************************************************************************/
size_t SchedulerCount(const scheduler_t *scheduler)
{
	size_t count = 0;
	assert(scheduler);
	
	count = PQHeapSize(scheduler->queue);
	
	if( NULL != scheduler->curr_task)
	{
		++count;
	}
	
	return count;
}
/****************************************************************************/
int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(scheduler);
	
	return (NULL == scheduler->curr_task && PQHeapIsEmpty(scheduler->queue));
}
/****************************************************************************/
void SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler);
	
	while( !PQHeapIsEmpty(scheduler->queue) )
	{
		TaskDestroy( (task_t*)PQHeapDequeue(scheduler->queue) );
	}
	
	scheduler->to_stop = NO_TASKS;
}
/****************************************************************************/
static int SchedularCompare(const void *data1, const void *data2 )
{
	return ( (int)( (TaskGetExecutionTime((task_t*)data1))
	       - ( TaskGetExecutionTime((task_t*)data2)) ));
}

