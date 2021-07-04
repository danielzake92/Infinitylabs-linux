/*****************************************************************************
* FILE:      ex7.c	          	 	   PURPOSE: Produce Consumer
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  Vladi Kysluk              STATUS: Imp 
******************************************************************************/
/* INCLUDES */
#include <stdio.h> /* Basic prints */
#include <stdlib.h>
#include <pthread.h> /* thread is needed */
#include <semaphore.h> /*sem_t*/
#include <signal.h> /* sig_atomic_t type */

/* DEFINES */
#define BUFF_SIZE 16
#define THREAD_NUM 8
#define COUNTER 100

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
void EX7_PC(void);

/* util function */
void* ReadFromBuffer(void *g_buffer);
void* WriteToBuffer(void *g_buffer);
void Constructor(void);
void Destructor(void);

/* cq_t functions */
void CQEnqueue(cq_t *buff, int data);
int CQDequeue(cq_t *buff);



pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER;

int read_index = 0;
int write_index = BUFF_SIZE;

cq_t *g_buffer = NULL;

/****************************************************************************/
int main()
{
	int ex_num = 7;
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------EX%d tests-----------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
	srand(time(NULL));
	EX7_PC();
	printf ("%s*****************************************\n",GREEN);
	printf ("%s-------------EX%d tests ended------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
		
	return 0;
}
/****************************************************************************/
void EX7_PC(void)
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
		num = rand() % (BUFF_SIZE * 8);

		pthread_mutex_lock(&read_mutex);
		pthread_mutex_lock(&write_mutex);

		if (0 < write_index)
		{
			CQEnqueue(g_buffer, num);
			printf("Produce..."GREEN"%d"DEFAULT"\n", num);
			--write_index;
			++read_index;
		}
		++i;
		pthread_mutex_unlock(&write_mutex);
		pthread_mutex_unlock(&read_mutex);
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
		pthread_mutex_lock(&read_mutex); 
		if (read_index > 0 && read_index <= BUFF_SIZE)
		{
			data = CQDequeue(g_buffer);
			printf("Consumed..."RED"%d"DEFAULT"\n", data);
			++write_index;
			--read_index;
		}
		++i;
		pthread_mutex_unlock(&read_mutex);
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

	if (pthread_mutex_init(&read_mutex, NULL) != 0)
    {
        printf("\n read_mutex Constructor failed\n");
        return;
    }

	if (pthread_mutex_init(&write_mutex, NULL) != 0)
    {
        printf("\n write_mutex Constructor failed\n");
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

	pthread_mutex_destroy(&write_mutex);
	pthread_mutex_destroy(&read_mutex);
}
