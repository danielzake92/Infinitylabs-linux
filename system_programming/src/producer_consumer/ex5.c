/*****************************************************************************
* FILE:      ex5.c	          	 	   PURPOSE: Produce Consumer
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
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
#define BUFF_SIZE 4
#define EX_EXIT 2
#define THREAD_NUM 4
#define COUNTER 10

#define GREEN "\033[32;1m"
#define RED "\033[31;1m"
#define DEFAULT "\x1b[0;0m"

typedef struct circular_queue
{
	int *arr;
	int capacity;
	int read;
	int write;
}cq_t;

/* Functions */
void EX5_PC(void);

/* util function */
void* ReadFromBuffer(void *g_buffer);
void* WriteToBuffer(void *g_buffer);
void Constructor(void);
void Destructor(void);

/* cq_t functions */
void CQEnqueue(cq_t *buff, int data);
int CQDequeue(cq_t *buff);


union converter
{
	int i;
	void *v;
}c;

/*converter functions*/
void *ItoV(int i);
int VtoI(void *v);

pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;

sem_t overflow;
sem_t underflow;

cq_t *g_buffer = NULL;

/****************************************************************************/
int main()
{
	int ex_num = 5;
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------EX%d tests-----------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
	srand(time(NULL));
	EX5_PC();
	printf ("%s*****************************************\n",GREEN);
	printf ("%s-------------EX%d tests ended------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
		
	return 0;
}
/****************************************************************************/
void EX5_PC(void)
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
	int i = 0;
	int num = 0;

	(void)arg;
	while (i < COUNTER)
	{
		sem_wait(&overflow);
		num = rand() % (BUFF_SIZE * 4);
		pthread_mutex_lock(&write_lock);
		CQEnqueue(g_buffer, num);
		sem_post(&underflow);
		pthread_mutex_unlock(&write_lock);
		++i;
	}

	return NULL;
}
/****************************************************************************/
void *ReadFromBuffer(void *arg)
{
	int i = 0;
	int data = 0;
	(void)arg;

	while (i < COUNTER)
	{
		sem_wait(&underflow);
		pthread_mutex_lock(&read_lock); 
		data = CQDequeue(g_buffer);
		printf("Consumed..."GREEN"%d"DEFAULT"\n", data);
		sem_post(&overflow);
		pthread_mutex_unlock(&read_lock);
		++i;
	}
	return NULL;
}	
/*****************************************************************************/
void CQEnqueue(cq_t *buff, int data)
{
	buff->arr[buff->write] = data;
	buff->write = ((buff->write) + 1 ) % (buff->capacity);
}
/*****************************************************************************/
int CQDequeue(cq_t *buff)
{
	int res = 0;
	res = buff->arr[buff->read];
	buff->read = ((buff->read) + 1 ) % (buff->capacity);

	return res;
}
/*****************************************************************************/
void Constructor(void)
{
	
	g_buffer = (cq_t*)malloc(sizeof(cq_t));
	g_buffer->capacity = BUFF_SIZE;
	g_buffer->read = 0;
	g_buffer->write = 0;
	g_buffer->arr = (int*)malloc(sizeof(int) * BUFF_SIZE);

	if (pthread_mutex_init(&write_lock, NULL) != 0)
    {
        printf("\n mutex Constructor failed\n");
        return;
    }
	if (pthread_mutex_init(&read_lock, NULL) != 0)
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
/*****************************************************************************/
void Destructor(void)
{
	
	free(g_buffer->arr);
	g_buffer->arr = NULL;
	
	free(g_buffer);
	g_buffer = NULL;

	sem_destroy(&overflow);
	sem_destroy(&underflow);
	pthread_mutex_destroy(&write_lock);
	pthread_mutex_destroy(&read_lock);
}
/****************************************************************************/
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
/*****************************************************************************/
/* gd ex5.c -o ex5.out -lpthread */