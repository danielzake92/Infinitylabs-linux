/*****************************************************************************
* FILE:      ex4.c	          	 	   PURPOSE: Produce Consumer
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  Vladi Kysluk              STATUS: Imp Done
******************************************************************************/
/* INCLUDES */
#include <stdio.h> /* Basic prints */
#include <stdlib.h>
#include <errno.h> /* perror */
#include <pthread.h> /* thread is needed */
#include <semaphore.h> /*sem_t*/
#include "circular_buffer.h"

/* DEFINES */
#define BUFF_SIZE 4
#define EX_EXIT 2
#define THREAD_NUM 4

#define COUNTER 10

#define GREEN "\033[32;1m"
#define DEFAULT "\x1b[0;0m"


/* Functions */
void EX4_PC(void);

/* util function */
void* ReadFromBuffer(void *g_buffer);
void* WriteToBuffer(void *g_buffer);
void Constructor(void);
void Destructor(void);
static int MiliSleep(long msec);

union converter
{
	int i;
	void *v;
}c;

/*converter functions*/
void *ItoV(int i);
int VtoI(void *v);
/*void ConstructorArr(void);*/

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t overflow;
sem_t underflow;
circular_buffer_t *g_buffer = NULL;

/****************************************************************************/
int main()
{
	int ex_num = 4;
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------EX%d tests-----------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
	EX4_PC();
	printf ("%s*****************************************\n",GREEN);
	printf ("%s-------------EX%d tests ended------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
		
	return 0;
}
/****************************************************************************/
void EX4_PC(void)
{
	pthread_t pth_read[THREAD_NUM / 2] = {0}; 
	pthread_t pth_write[THREAD_NUM / 2] = {0}; 
	int i = 0;

	Constructor();

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

	Destructor();

}
/****************************************************************************/
void *WriteToBuffer(void *arg)
{
	int i = 0 ;
	char a = 'a';
	(void)arg;
	while (i < COUNTER)
	{
		sem_wait(&overflow);
		pthread_mutex_lock(&lock);
		CircularBufferWrite(g_buffer,&a, 1);
		sem_post(&underflow);
		printf("Produced...\n");
		pthread_mutex_unlock(&lock);
		++i;
	}

	return NULL;
}
/****************************************************************************/
void *ReadFromBuffer(void *arg)
{
	int i = 0;
	char temp_buffer = '\0';
	(void)arg;

	while (i < COUNTER)
	{
		sem_wait(&underflow);
		pthread_mutex_lock(&lock); 
		CircularBufferRead(g_buffer,&temp_buffer ,1);
		sem_post(&overflow);
		printf("Consumed...%c\n", temp_buffer);
		MiliSleep(100);

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

void Constructor(void)
{
	g_buffer = CircularBufferCreate(BUFF_SIZE);

	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex Constructor failed\n");
        return;
    }
	if (sem_init(&overflow, 0, BUFF_SIZE) != 0)
    {
        printf("\n sem overflow failed\n");
        return;
    }

	if (sem_init(&underflow, 0, 0) != 0)
    {
        printf("\n sem underflow failed\n");
        return;
    }
}

void Destructor(void)
{
	sem_destroy(&overflow);
	sem_destroy(&underflow);
	pthread_mutex_destroy(&lock);
	CircularBufferDestroy(g_buffer);
}

static int MiliSleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = msec * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

/*gd ex4.c ../../../ds/src/circular_buffer/circular_buffer.c -o ex4.out -lpthread -I../../../ds/include*/