/*****************************************************************************
* FILE:      mapping3.c	          	 	   PURPOSE: Produce Consumer
* DEVELOPER: Daniel Zaken && Nitzibi       TEAM:    Yellow
*
* REVIEWER:  Vladi Kysluk              STATUS: Imp 
******************************************************************************/
/* INCLUDES */
#include <stdio.h> /* Basic prints */
#include <string.h> /* strcmp*/
#include <stdlib.h>
#include <pthread.h> /* thread is needed */
#include <semaphore.h> /*sem_t*/

/* DEFINES */
#define THREAD_NUM 20

#define GREEN "\033[32;1m"
#define RED "\033[31;1m"
#define DEFAULT "\x1b[0;0m"

/* Functions */
void Test(void);
void *PutInArray (void *i);
void PrintArr(void);

size_t g_arr[THREAD_NUM];

sem_t overflow;
sem_t underflow;


/****************************************************************************/
int main()
{
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------tests-----------------\n",GREEN);
	printf ("%s*****************************************\n",DEFAULT);
	Test();
	printf ("%s*****************************************\n",GREEN);
	printf ("%s-------------tests ended------------\n",GREEN);
	printf ("%s*****************************************\n",DEFAULT);
		
	return 0;
}
/****************************************************************************/
void Test(void)
{
	pthread_t pth[THREAD_NUM] = {0}; 
	size_t i = 0;

	for (i = 0; i < THREAD_NUM ; ++i)
	{
		/*pthread_create(&(pth[i]),NULL,PutInArray,&i); cuases race conditions*/
		pthread_create(&(pth[i]),NULL,PutInArray,(void*)i);
	}	

	for (i = 0; i < THREAD_NUM; ++i)
	{
		pthread_join(pth[i],NULL);
	}	

	PrintArr();

}
/****************************************************************************/

void* PutInArray (void *i)
{
	size_t s_i = (size_t)i;

	/*size_t s_i = (*(size_t*)i); causes race conditions */

	while(1){}
	while(1){}
	while(1){}

	g_arr[s_i] = s_i;


	return NULL;
}

void PrintArr(void)
{
	size_t i = 0;

	for(i = 0; i < THREAD_NUM; ++i)
	{
		printf("|%lu|",g_arr[i]);
	}

	puts("");
}