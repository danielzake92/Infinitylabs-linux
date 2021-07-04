#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* required for sleep function */
#include <assert.h>
#include "scheduler.h"
#include "task.h"
#include "uid.h"
#include "utl.h"

#define SUCCESS 0

typedef struct array
{
    int *arr;
    int size;
    int mult;
    int add;
}arr_t;

static arr_t *ArrInit( int size, int mult, int add);
static void ArrDestroy(void *data);
static int ArrAdd(void *data);
static int ArrMultiple(void *data);
static int ArrPrint(void *data);
static void ArrDoNothing(void *data);
static int StopInTask(void *data);
static int RemoveMe(void *data);

static void SchedulerTest();



int main()
{	
	
	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------PRJ 1 tests---------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);
	
	SchedulerTest();
	
	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------Test ended----------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);
	
	return 0;
}

static void SchedulerTest()
{
	arr_t *arr1 = ArrInit(10,2,1);
	arr_t *arr2 = ArrInit(10,3,5);
	arr_t *arr3 = ArrInit(10,7,1);
	scheduler_t *scheduler = SchedulerCreate();
	
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	
	puts(YELLOW"Scheduler Test");
	
	if(scheduler && SchedulerIsEmpty(scheduler))
	{
		printf ("%s SchedulerCreate:%s SUCCESS\n",WHITE,GREEN);
		printf ("%s SchedulerIsEmpty:%s SUCCESS\n",WHITE,GREEN);
	}
	else
	{
		printf ("%s SchedulerCreate:%s FAILURE\n",WHITE,RED);	
		printf ("%s SchedulerIsEmpty:%s FAILURE\n",WHITE,RED);								
	}
	puts(WHITE);
	SchedulerAddTask(scheduler, StopInTask, ArrDoNothing, 5, (void *)scheduler);
	SchedulerAddTask(scheduler, RemoveMe, ArrDoNothing, 0 , (void*)arr1);
	SchedulerAddTask(scheduler, ArrMultiple, ArrDestroy, 1 , (void*)arr1);
	SchedulerAddTask(scheduler, ArrPrint, ArrDoNothing, 1 , (void*)arr1);
	SchedulerAddTask(scheduler, ArrAdd, ArrDestroy, 2 , (void*)arr2);
	SchedulerAddTask(scheduler, ArrPrint, ArrDoNothing, 2 , (void*)arr2);
	
	uid1 = SchedulerAddTask(scheduler, ArrMultiple, ArrDestroy, 3 , (void*)arr3);
	uid2 = SchedulerAddTask(scheduler, ArrPrint, ArrDoNothing, 3 , (void*)arr3);	
	if(SchedulerRun(scheduler) == STOPPED)
	{
		printf ("%s SchedulerAddTask:%s SUCCESS\n",WHITE,GREEN);
		printf ("%s SchedulerRun:%s SUCCESS\n",WHITE,GREEN);
		printf ("%s SchedulerStop:%s SUCCESS\n",WHITE,GREEN);
	}
	else
	{
		printf ("%s SchedulerAddTask:%s FAILURE\n",WHITE,RED);	
		printf ("%s SchedulerRun:%s FAILURE\n",WHITE,RED);		
		printf ("%s SchedulerStop:%s FAILURE\n",WHITE,RED);								
	}
	
	if( !SchedulerRemoveTask(scheduler,uid1) && !SchedulerRemoveTask(scheduler,uid2	) && SchedulerRemoveTask(scheduler,UIDGetBadUID()) )
	{
		printf ("%s SchedulerRemove:%s SUCCESS\n",WHITE,GREEN);
	}
	else
	{
		printf ("%s SchedulerRemove:%s FAILURE\n",WHITE,RED);
	}
	
	if( SchedulerCount(scheduler) == 5 )
	{
		printf ("%s SchedulerCount:%s SUCCESS\n",WHITE,GREEN);
	}
	else
	{
		printf ("%s SchedulerCount:%s FAILURE\n",WHITE,RED);
	}
	
	SchedulerClear(scheduler);
	if ( SchedulerCount(scheduler) == 0)
	{
		printf ("%s SchedulerClear:%s SUCCESS\n",WHITE,GREEN);	
	}
	else
	{
		printf ("%s SchedulerClear:%s FAILURE\n",WHITE,RED);	
	}
	
	
	SchedulerDestroy(scheduler);
	printf ("%s SchedulerDestroy:%s SUCCESS\n",WHITE,GREEN);	
}


static arr_t *ArrInit( int size, int mult, int add)
{
	arr_t *arr = (arr_t*)malloc( sizeof(arr_t));
	int i = 0;
	arr->mult = mult;
	arr->add = add;
	arr->size = size;
	arr->arr = (int*)malloc(size * sizeof(int));
	
	for( i = 0; i < size; ++i)
	{
		(arr->arr)[i] = i ;
	}
	puts(YELLOW"ArrCreate");
	return arr;
}

static void ArrDestroy(void *data)
{
    free(((arr_t*)data) -> arr);
    free(data);
}

static int ArrAdd(void *data)
{
	arr_t *temp = (arr_t*)data;
	int i = 0;
	
	for( i = 0; i < temp->size ; ++i)
	{
		temp->arr[i] += temp->add;
	}
	
	printf(YELLOW"ArrAdd %d\n", temp->add);
	
	return SUCCESS; 
}
static int ArrMultiple(void *data)
{
	arr_t *temp = (arr_t*)data;
	int i = 0;
	
	for( i = 0; i < temp->size ; ++i)
	{
		temp->arr[i] *= temp->mult;
	}
	
	printf(YELLOW"ArrMultiply by %d\n", temp->mult);
	
	return SUCCESS; 

}
static int ArrPrint(void *data)
{
	arr_t *temp = (arr_t*)data;
	int i = 0;
	puts(YELLOW"ArrPrint"DEFAULT);
	
	printf("array numbers : \n"); 
	for( i = 0; i < temp->size ; ++i)
	{
		printf("%s %d ",WHITE,temp->arr[i]);
	}
	
	puts("");
	
	return SUCCESS; 
}
static void ArrDoNothing(void *data)
{
	(void)data;
	return;
}

static int StopInTask(void *data)
{
	assert(data);
	
	SchedulerStop((scheduler_t *)data);
	return SUCCESS;
}

static int RemoveMe(void *data)
{
	(void)data;
	puts(WHITE"task removed itself\n");
	return FAILURE;
}
