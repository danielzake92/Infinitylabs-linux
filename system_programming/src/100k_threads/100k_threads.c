/*****************************************************************************
* FILE:      100k_threads.c	           PURPOSE: 100k_threads
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  			               STATUS: APPROVED
******************************************************************************/
/*INCLUDES*/
#include <stdlib.h>/*Atoi*/
#include <stdio.h> /*Basic prints*/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*sleep*/
#include <errno.h> /*perror*/
#include <pthread.h>
#include <time.h>
#include <omp.h>
#include <signal.h> 
/*DEFINES*/
#define ARR_SIZE 100000
#define NUM_THREADS 16
#define MAX_NUM 30000000000
#define CALC_INTERVAL ((MAX_NUM) / (NUM_THREADS))
#define EX_NUM 7
#define GREEN "\033[32;1m"
#define DEFAULT "\x1b[0;0m"
/*Typedef*/
typedef void (*func_t)(void);
/*Functions*/
void EX1_100k(void);
void EX2_100k(void);
void EX3_100k(void);
void EX4_100k(void);
void EX5_100k(void);
void EX6_100k(void);

void EX7_100k(void);
void *DoPing(void*);
void *DoPong(void*);

/*util function*/
void *SumOfDivisors(void *i);
void* PutInArray (void* i);

union converter
{
	int i;
	size_t z;
	void *v;
}c;

/*converter functions*/
void *ItoV(int i);
int VtoI(void *v);
void *ZtoV(size_t i);
size_t VtoZ(void *v);

func_t g_func_lut[EX_NUM] = {EX1_100k, EX2_100k, EX3_100k,
							 EX4_100k, EX5_100k, EX6_100k, EX7_100k};

int g_arr[ARR_SIZE] = {0};
sig_atomic_t g_is_ping = 0;
/****************************************************************************/
int main(int argc, char *argv[])
{
	int ex_num = 0;
	
	if(argc > 1)
	{
		ex_num = atoi(argv[1]);
	}

	(void)argc;
	
	printf ("%s*****************************************\n",GREEN);
	printf ("%s---------------EX%d tests-----------------\n",GREEN,ex_num);
	printf ("%s*****************************************",GREEN);
	puts(DEFAULT);

	g_func_lut[ex_num - 1]();
		
	return 0;
}
/****************************************************************************/
void EX1_100k(void)
{
	int i = 0;
	size_t count = 0;
	static pthread_t pth[ARR_SIZE] = {0}; /*its recommended to create arr on the data segment*/
	int status = 0;
	time_t start, end;

	start = time(NULL);

	for(i = 0; i < ARR_SIZE ; ++i )
	{  
		status = pthread_create(&pth[i],NULL,PutInArray,ItoV(i));
	}

	if( EAGAIN == status )
	{
		printf("not enough resources\n");
	}

	sleep(1);
/*
	for(i = 0; i < ARR_SIZE ; ++i )
	{  
		pthread_join(pth[i],NULL);
	}
*/

	for(i = 0; i < ARR_SIZE; ++i)
	{
		if(g_arr[i] != i)
		{
			++count;
		}

		/*printf("%d\n", g_arr[i]);*/
	}
	end=time(NULL);
	printf("program take %d second\n",(unsigned int)difftime(end,start));
	printf("number of uncorrelated = %lu\n", count);
}
/****************************************************************************/
void EX2_100k(void)
{
	int i = 0;
	size_t count = 0;
	static pthread_t pth[ARR_SIZE] = {0};
	int status = 0;
	time_t start, end;

	start = time(NULL);

	for(i = 0; i < ARR_SIZE ; ++i )
	{  
		status = pthread_create(&pth[i],NULL,PutInArray,ItoV(i));
		if( 0 != status )
		{
			++count;
		}
	}

	sleep(1);

	end=time(NULL);
	printf("program take %d second\n",(unsigned int)difftime(end,start));
	printf("number of failures = %lu\n", count);
}
/****************************************************************************/
void EX3_100k(void)
{
	int i = 0;
	size_t count = 0;
	static pthread_t pth[ARR_SIZE] = {0};
	time_t start, end;
	pthread_attr_t attr = {0};
	int status = 0;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	start = time(NULL);

	for(i = 0; i < ARR_SIZE ; ++i )
	{  
		status = pthread_create(&pth[i],&attr,PutInArray,ItoV(i));
		if( 0 != status )
		{
			printf("fail\n");
		}
	}

	sleep(5);

	for(i = 0; i < ARR_SIZE; ++i)
	{
		if(g_arr[i] != i)
		{
			++count;
		}

		/*printf("%d\n", g_arr[i]);*/
	}

	end=time(NULL);
	printf("program take %d second\n",(unsigned int)difftime(end,start));
	printf("number of uncorellations = %lu\n", count);

}
/****************************************************************************/
void EX4_100k(void)
{
	size_t i = 0;
	static pthread_t pth[ARR_SIZE] = {0};
	time_t start, end;
	void *ret = NULL;
	size_t sum_if_divisors = 0;

	start = time(NULL);

	for(i = 0; i < NUM_THREADS ; ++i )
	{  
		pthread_create(&pth[i],NULL,SumOfDivisors,ZtoV(i)); /* TODO check ret val */
	}

	for(i = 0; i < NUM_THREADS ; ++i )
	{  
		pthread_join(pth[i],&ret);
		sum_if_divisors += VtoZ(ret);
	}

	end=time(NULL);
	printf("program take %d second\n",(unsigned int)difftime(end,start));
	printf("sum_if_divisors = %lu\n",sum_if_divisors);
}
/****************************************************************************/
void EX5_100k(void)
{
	size_t i = 0;
	static pthread_t pth[ARR_SIZE] = {0};
	time_t start, end;
	void *ret = NULL;
	size_t sum_if_divisors = 0;
	size_t core_num = 16;
	start = time(NULL);

	for(i = 0; i < core_num ; ++i )
	{  
		pthread_create(&pth[i],NULL,SumOfDivisors,ZtoV(i)); /* TODO check ret val */
	}

	for(i = 0; i < core_num ; ++i )
	{  
		pthread_join(pth[i],&ret);
		sum_if_divisors += VtoZ(ret);
	}

	end=time(NULL);
	printf("program take %d second\n",(unsigned int)difftime(end,start));
	printf("sum_if_divisors = %lu\n",sum_if_divisors);
}
/****************************************************************************/

void EX6_100k(void)
{
	size_t i = 0;
	time_t start, end;
	size_t local_sum_of_divisors = 0;
	size_t sum_of_divisors = 0;

	start = time(NULL);

	#pragma omp parallel private(local_sum_of_divisors) shared(sum_of_divisors)
	{
		local_sum_of_divisors = 0;

		#pragma omp for schedule(static,1) 
		for( i = 1; i <= MAX_NUM ; ++i)
		{
			if( 0 == MAX_NUM % i)
			{
				local_sum_of_divisors += i;
			}
		}
		#pragma omp critical 
    	sum_of_divisors += local_sum_of_divisors;

	}

	end=time(NULL);
	printf("program take %d second\n",(unsigned int)difftime(end,start));
	printf("sum_if_divisors = %lu\n",sum_of_divisors);
}
/****************************************************************************/
void EX7_100k(void)
{
	int i = 0;
	size_t count = 0;
	pthread_t pth[2] = {0};
	time_t start, end;

	start = time(NULL);

	pthread_create(&pth[0],NULL,DoPing,NULL);
	pthread_create(&pth[1],NULL,DoPong,NULL);
	
	for(i = 0; i < 2; ++i)
	{
		pthread_join(pth[i], NULL);
	}

	end=time(NULL);
	printf("program take %d second\n",(unsigned int)difftime(end,start));
	printf("number of failures = %lu\n", count);
}
/****************************************************************************/
void* PutInArray (void *i)
{
	g_arr[VtoI(i)] = VtoI(i);
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
/****************************************************************************/
void *ZtoV(size_t i)
{
	c.z = i;
	return c.v;
}
/****************************************************************************/
size_t VtoZ(void *v)
{
	c.v = v;
	return c.z;
}
/****************************************************************************/
void *SumOfDivisors(void *index)
{
	size_t sum_of_divisors = 0;
	size_t i_v = VtoZ(index);
	size_t i = 0;
	for( i = (CALC_INTERVAL * i_v) + 1; i <= CALC_INTERVAL * (i_v + 1); ++i)
	{
		if( 0 == MAX_NUM % i)
		{
			sum_of_divisors += i;
		}
	}
	return ZtoV(sum_of_divisors);
}
/****************************************************************************/
void *DoPing(void *i)
{
	while(1)
	{
		if( 0 == g_is_ping )
		{
			printf("Ping\n");
			g_is_ping = 1;
		}
		sleep(1);	
	}
	(void)i;
}
/****************************************************************************/
void *DoPong(void *i)
{
	while(1)
	{
		if( 1 == g_is_ping )
		{
			printf("Pong\n");
			g_is_ping = 0;
		}
		sleep(1);
	}
	(void)i;
}
/****************************************************************************/
/*gc 100k_threads.c -lpthread*/





