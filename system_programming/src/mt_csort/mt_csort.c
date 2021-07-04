/*****************************************************************************
* FILE:      m_csort.c	       		   PURPOSE: Multy-threading counting sort
* DEVELOPER: Daniel Zaken              TEAM:    RD100
*
* REVIEWER:  ************              STATUS: Impl
******************************************************************************/

#include <stdio.h> /* printfs */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <pthread.h> /* using thread lib */
#include <stdatomic.h> /*atomic variables*/
#include <assert.h> /* assert */
#include <sys/time.h> /*for benchmarks measurements*/
/*****************************************************************************/
#define NUM_LETTERS 972400
#define NUM_THREADS 9
#define NUM_COPIES 400
#define ASCII 256
/*****************************************************************************/
typedef struct args
{
	char *buffer;
	size_t thr_idx;
	size_t s_idx;
	size_t e_idx;
}args_t;

typedef enum 
{
	SUCCESS = 0,
	FAIL = 1,
	ALLOCATION_ERROR = 2,
	OPEN_ERR = 3,
	CLOSE_ERROR = 4
 }status_t;
/*****************************************************************************/
static status_t ReadLnxDicToBuff(const char *f_name ,char *buff);/* uses I/O */

static status_t LnxDicToBigData(char *buff);

static void InitStruc(args_t *arr, char *buffer, size_t buff_len);

status_t MtCounting(args_t *arr);

status_t MtCountSort(char *buff);

void *ThreadCount(void *arg);

void ArrangeBuff(char *buff);

char *CreateBuff();
/*****************************************************************************/
const char *DICT_PATH =  "/usr/share/dict/american-english";
size_t g_count[NUM_THREADS][ASCII] = {0};
/*****************************************************************************/
int main()
{
	long seconds = 0;
    long micro_seconds = 0;
    double benchmark = 0;
    struct timeval start, end;
	size_t i = 0;

	static char buffer[NUM_COPIES * NUM_LETTERS];
	//char *buffer = CreateBuff(num_copies);

	/*Start measuring*/
    gettimeofday(&start, 0);

	MtCountSort(buffer);
    /*Stop measuring*/
    gettimeofday(&end, 0);

	while(buffer[i + 1])
    {
        if (buffer[i] > buffer[i+1])
        {
            printf("failed sorting at %lu\n", i);
            printf("%c, %c\n", buffer[i], buffer[i + 1]);
            return 0;
        }
        ++i;
    }
    printf("sorting succeedded!!!\n");
    seconds = end.tv_sec - start.tv_sec;
    micro_seconds = end.tv_usec - start.tv_usec;
    benchmark = seconds + (micro_seconds * 1e-6);
    printf("Benchmark on %u copies with %u threads: ", NUM_COPIES, NUM_THREADS);
    printf("%f seconds\n\n", benchmark);

	return 0;
}
/*****************************************************************************/
status_t MtCountSort(char *buff)
{
	status_t status = SUCCESS;
	size_t buff_len = NUM_LETTERS * NUM_COPIES;
	args_t arr[NUM_THREADS];

	InitStruc(arr, buff, buff_len);

	status = ReadLnxDicToBuff(DICT_PATH, buff);

	LnxDicToBigData(buff);

	MtCounting(arr);

	ArrangeBuff(buff);

	
	return status;
}
/*****************************************************************************/
static status_t LnxDicToBigData(char *buff)
{
	size_t i = 0;

	for(i = 0; i < NUM_COPIES - 1; ++i)
	{
		memcpy(buff + NUM_LETTERS,buff, NUM_LETTERS );
		buff += NUM_LETTERS;
	}
	return SUCCESS;
}
/*****************************************************************************/
static status_t ReadLnxDicToBuff(const char *f_name,char *buff)
{
	FILE *file = NULL;
	status_t status = SUCCESS;
	size_t i = 0;
	
	if ( ( file = fopen(f_name, "r") ) == NULL )
	{
		return(OPEN_ERR);
	}
	char c = 0;
	for( i = 0 ; SUCCESS == feof(file); ++i )
	{
		c = fgetc(file);

		if( 0 > c)
		{
			c = ' ';
		}

		buff[i] = c;
	}

	if( (status = fclose(file) ) != 0)
	{
		return (CLOSE_ERROR);
	}  

	return SUCCESS;
}
/*****************************************************************************/
char *CreateBuff()
{
	char *buff = (char*)malloc( sizeof(char) * (NUM_COPIES * NUM_LETTERS) );
	if ( NULL == buff )
	{
		return(NULL);
	}
	return buff;
}
/*****************************************************************************/
void ArrangeBuff(char *buff)
{
	size_t i = 0;
	size_t j = 0;


	
	for(i = 1; i < ASCII; ++i)
	{
		for(j = 0; j < NUM_THREADS; ++j)
		{
			while(g_count[j][i])
			{
				--g_count[j][i];
				*buff = (char)i;
				++buff;
			}
		}
	}

	*buff = 0;
}
/*****************************************************************************/
status_t MtCounting(args_t *arr)
{
	pthread_t pth[NUM_THREADS] = {0};

	int status = 0;
	size_t i = 0;

	for(i = 0; i < NUM_THREADS ; ++i )
	{  
		status = pthread_create(&pth[i],NULL,ThreadCount,(void*)(arr + i));
		if( SUCCESS != status )
		{
			return status;
		}
	}

	for(i = 0; i < NUM_THREADS ; ++i )
	{  
		pthread_join(pth[i],NULL);
	}

	return SUCCESS;

}
/*****************************************************************************/
void *ThreadCount(void *arg)
{
	assert(arg);

	args_t *elem = (args_t*)arg;
	size_t thread = elem->thr_idx;
	size_t i = elem->s_idx;
	size_t end = elem->e_idx;
	int c = 0;

	for(; i < end; ++i)
	{
		c =	(elem->buffer)[i];
		g_count[thread][c] += 1;
	}

	return NULL;
}
/*****************************************************************************/
static void InitStruc(args_t *arr, char *buffer, size_t buff_len)
{
	size_t i = 0;
	size_t interval = buff_len / NUM_THREADS;

	for( i = 0; i < NUM_THREADS ; ++i)
	{
		arr[i].buffer = buffer;
		arr[i].thr_idx = i;
		arr[i].s_idx = i * interval;
		arr[i].e_idx = (i + 1) * interval - 1;
	}

	arr[NUM_THREADS - 1].e_idx = buff_len - 1;

}
/*****************************************************************************/
