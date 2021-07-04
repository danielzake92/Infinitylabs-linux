/*****************************************************************************
* FILE:      ex8.c	          	 	   PURPOSE: Produce Consumer
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  Vladi Kysluk              STATUS: Imp 
******************************************************************************/
/* INCLUDES */
#include <stdio.h> /* Basic prints */
#include <string.h> /* strcmp*/
#include <stdlib.h>
#include <sys/types.h> /* pid_t */
#include <errno.h> /* perror */
#include <pthread.h> /* thread is needed */
#include <semaphore.h> /*sem_t*/
#include <signal.h> 
#include <assert.h>
#include <unistd.h> /* sleep */
#include <time.h>

/* DEFINES */
#define BUFF_SIZE 32
#define EX_EXIT 2
#define THREAD_NUM 5
#define COUNTER 3

#define GREEN "\033[32;1m"
#define RED "\033[31;1m"
#define DEFAULT "\x1b[0;0m"

/* Functions */
void EX8_PC(void);

/* util function */
void* ReadFromBuffer(void *g_buffer);
void* WriteToBuffer(void *g_buffer);
void Constructor(void);
void Destructor(void);

union converter
{
	int i;
	void *v;
}c;

/*converter functions*/
void *ItoV(int i);
int VtoI(void *v);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;

char g_buffer[BUFF_SIZE] = "";

/****************************************************************************/
int main()
{
	int ex_num = 8;
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------EX%d tests-----------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
	srand(time(NULL));
	EX8_PC();
	printf ("%s*****************************************\n",GREEN);
	printf ("%s-------------EX%d tests ended------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
		
	return 0;
}
/****************************************************************************/
void EX8_PC(void)
{
	pthread_t pth_read[THREAD_NUM - 1] = {0}; 
	pthread_t pth_write = 0; 
	int i = 0;

	Constructor();

	pthread_create(&pth_write,NULL,WriteToBuffer,NULL);

	for(i = 0; i < (THREAD_NUM - 1); ++i)
	{
		pthread_create(&(pth_read[i]),NULL,ReadFromBuffer,NULL);
	}

	pthread_join(pth_write,NULL);

	for(i = 0; i < (THREAD_NUM - 1); ++i)
	{
		pthread_join(pth_read[i],NULL);
	}	

	Destructor();

}
/****************************************************************************/
void *WriteToBuffer(void *arg)
{
	int i = 0;
	int j = 0;
	(void)arg;

	while(j < COUNTER )
	{
		i = THREAD_NUM - 1;
		while( i )
		{
			sem_wait(&sem);
			--i;
		}

		pthread_mutex_lock(&lock);
		fgets(g_buffer, BUFF_SIZE, stdin);
		/*strcpy(g_buffer, "hello my name is Daniel");*/
		/*printf("Produce..."GREEN"%s"DEFAULT"\n", g_buffer);*/

		pthread_cond_broadcast(&con);

		++j;
		pthread_mutex_unlock(&lock);
	}


	return NULL;
}
/****************************************************************************/
void *ReadFromBuffer(void *arg)
{
	char buff[BUFF_SIZE] = "";
	int j = 0;
	(void)arg;

	while( j )
	{
		pthread_mutex_lock(&lock); 

		sem_post(&sem);
		pthread_cond_wait(&con, &lock);

		printf("Consumed..."RED"%s"DEFAULT"\n", g_buffer);
		strcpy(g_buffer,"");

		++j;
		pthread_mutex_unlock(&lock);
	}



	return NULL;
}	
/*****************************************************************************/
void Constructor(void)
{
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex Constructor failed\n");
        return;
    }

	if (sem_init(&sem, 0, 0) != 0)
    {
        printf("\n sem sem failed\n");
        return;
    }

	if( pthread_cond_init(&con, NULL) != 0 )
	{
        printf("\n cond var failed\n");
        return;
	}
	
}
/*****************************************************************************/
void Destructor(void)
{
	pthread_mutex_destroy(&lock);
	sem_destroy(&sem);
	pthread_cond_destroy(&con);
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
/* gd ex8.c -o ex8.out -lpthread */
