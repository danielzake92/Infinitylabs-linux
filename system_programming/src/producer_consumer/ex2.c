/*****************************************************************************
* FILE:      ex2.c	          	 	   PURPOSE: Produce Consumer
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  Vladi Kysluk              STATUS: Imp Done
******************************************************************************/
/* INCLUDES */
#include <stdio.h> /* Basic prints */
#include <stdlib.h> /* rand */ 
#include <pthread.h> /* thread is needed */
#include "doubly_linked_list.h"

/* DEFINES */
#define ARR_SIZE 16
#define EX_EXIT 2
#define THREAD_NUM 4
#define COUNTER 10

#define GREEN "\033[32;1m"
#define DEFAULT "\x1b[0;0m"

/* Functions */
void EX2_PC(void);

/* util function */
void* ReadFromBuffer(void *g_buffer);
void* WriteToBuffer(void *g_buffer);

union converter
{
	int i;
	void *v;
}c;

/*converter functions*/
void *ItoV(int i);
int VtoI(void *v);
/*void InitArr(void);*/

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
dll_t *g_list = NULL;
int g_arr[ARR_SIZE] = {0};

/****************************************************************************/
int main()
{
	int ex_num = 2;
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------EX%d tests-----------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
	EX2_PC();
	printf ("%s*****************************************\n",GREEN);
	printf ("%s-------------EX%d tests ended------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
		
	return 0;
}
/****************************************************************************/
void EX2_PC(void)
{
	pthread_t pth_read[THREAD_NUM / 2] = {0}; 
	pthread_t pth_write[THREAD_NUM / 2] = {0}; 
	int i = 0;

	g_list = DoublyLinkedListCreate();

	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return;
    }

	for (i = 0; i < THREAD_NUM / 2; ++i)
	{
		pthread_create(&(pth_write[i]),NULL,WriteToBuffer,NULL);
		pthread_create(&(pth_read[i]),NULL,ReadFromBuffer,NULL);
	}	

	for (i = 0; i < THREAD_NUM / 2; ++i)
	{
		pthread_join(pth_write[i],NULL);
		pthread_join(pth_read[i],NULL);
	}	

	pthread_mutex_destroy(&lock);
	DoublyLinkedListDestroy(g_list);

}
/****************************************************************************/
void* WriteToBuffer(void *arg)
{
	int i = 0;
	(void)arg;
	while (i < COUNTER)
	{
		pthread_mutex_lock(&lock);
		printf("Produced...\n");
		DoublyLinkedListPushBack(g_list,ItoV(rand() % ARR_SIZE));
		pthread_mutex_unlock(&lock);
		++i;
	}

	return NULL;
}
/****************************************************************************/
void* ReadFromBuffer(void *arg)
{
	int i = 0;
	void *data = NULL;
	(void)arg;

	while (i < COUNTER)
	{
		pthread_mutex_lock(&lock); /*beware from dead lock*/

		while (!DoublyLinkedListIsEmpty(g_list))
		{
			data = DoublyLinkedListPopFront(g_list);
			printf("Consumed...\n");
			printf("%d\n",VtoI(data) );
		}

		pthread_mutex_unlock(&lock);
		++i;
	}

	return NULL;
}

void *ItoV(int i)
{
	c.i = i;
	return c.v;
}
/****************************************************************************/
int VtoI(void *v)
{
	c.v = v;
	return c.i;
}

/*gd ex2.c ../../../ds/src/doubly_linked_list/doubly_linked_list.c -o ex2.out -lpthread -I../../../ds/include*/