/*****************************************************************************
* FILE:      ex1.c	          	 	   PURPOSE: Produce Consumer
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  Vladi Kysluk              STATUS: Imp Done
******************************************************************************/
/* INCLUDES */
#include <stdio.h> /* Basic prints */
#include <string.h> /* strcmp*/
#include <errno.h> /* perror */
#include <pthread.h> /* thread is needed */
#include <signal.h> /* sig_atomic_t type */
#include <stdlib.h> /* exit function */
/* DEFINES */
#define BUFF_SIZE ((BUFSIZ) / (128))
#define EX_EXIT 2

#define GREEN "\033[32;1m"
#define DEFAULT "\x1b[0;0m"

/* Functions */
void EX1_PC(void);

/* util function */
void* ReadFromBuffer(void *buffer);
void* WriteToBuffer(void *buffer);

union converter
{
	int i;
	size_t z;
	void *v;
}c;

/*converter functions*/
void *ItoV(int i);
int VtoI(void *v);


sig_atomic_t g_lock = 1; /*1 for unlocked 0 for locked*/
char buffer[BUFF_SIZE] = "";

/****************************************************************************/
int main()
{
	int ex_num = 1;
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------EX%d tests-----------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
	EX1_PC();
	printf ("%s*****************************************\n",GREEN);
	printf ("%s-------------EX%d tests ended------------\n",GREEN,ex_num);
	printf ("%s*****************************************\n",DEFAULT);
		
	return 0;
}
/****************************************************************************/
void EX1_PC(void)
{
	pthread_t pth_read = 0; 
	pthread_t pth_write = 0; 
	int status = 0;
	
	status = pthread_create(&pth_read,NULL,ReadFromBuffer,NULL);
	if (EAGAIN == status)
	{
		printf("not enough resources\n");
	}

	status = pthread_create(&pth_write,NULL,WriteToBuffer,NULL);
	if (EAGAIN == status)
	{
		printf("not enough resources\n");
	}
	pthread_join(pth_read,NULL);
	pthread_join(pth_write,NULL);

}
/****************************************************************************/
void* ReadFromBuffer(void *arg)
{
	(void)arg;
	while (1)
	{
		while (0 == g_lock)
		{
			/*busy wait*/
		}
		printf("Please enter command, for exit press [Y]\n");
		fgets(buffer, BUFF_SIZE, stdin);

		g_lock = 0;
	}
	return NULL;
}
/****************************************************************************/
void* WriteToBuffer(void *arg)
{
	(void)arg;
	while (1)
	{
		while (1 == g_lock)
		{
			/*busy wait*/
		}

		if (!strcmp("y\n", buffer) || !strcmp("Y\n", buffer)) /**/
		{
			exit(1);
		}

		printf("****\n%s",buffer);
		
		g_lock = 1;
	}

	return NULL;
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