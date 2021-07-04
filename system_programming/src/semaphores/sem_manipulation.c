/*****************************************************************************
* FILE:      semaphores.c	           PURPOSE: Semaphores
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  Or Kats	               STATUS: Impl Done
******************************************************************************/
/*INCLUDES*/
#include <stdlib.h>/*Atoi*/
#include <stdio.h> /*Basic prints*/
#include <string.h>
#include <assert.h> /* assert */ 
#include <sys/types.h> /*pid_t*/
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <signal.h> 
#include <semaphore.h>
#include <fcntl.h>   /* For O_* constants */
#include <sys/stat.h> 
/*DEFINES*/
#define GREEN "\033[32;1m"
#define DEFAULT "\x1b[0;0m"

#define MAX_INPUT_SIZE 80
#define MAX_WORD_TO_PARSE 3
#define ASCII 128
#define AZ 22
#define UNDO 0X2ADA711E

typedef enum parse_status
{
	PARSE_SUCCESS = 0,
	PARSE_SYNTAX_ERROR = 1,
	PARSE_NO_NUM_ERROR = 2,
	PARSE_EXIT = 3	
}ps_status_t;

typedef enum op_status
{
	OP_SUCCESS = 0,
	OP_GET_VAL_FAILURE = 1,
	OP_SEM_FAILURE = 2
}op_status_t;

typedef enum sem_status
{
	SEM_SUCCESS = 0,
	SEM_CLOSE_ERROR = -1,
	SEM_UNLINK_ERROR = -1,
	SEM_POST_ERROR = -1,
	SEM_WAIT_ERROR = -1,
	SEM_OPEN_ERROR = -1
}s_status_t;

const char *map[] = {"PARSE_SUCCESS", "PARSE_SYNTAX_ERROR", "PARSE_NO_NUM_ERROR", "PARSE_EXIT"};

s_status_t SemManipulation(char *argv[]);
int IsUndo(char *str);
ps_status_t Parser(char *input, int *output);
void InitLut(void);
void PrintOutput(int *output);

/*func_t funcs*/
typedef ps_status_t (*func_t)(char *input, int *output);

ps_status_t CaseDecInc(char *input, int *output);
ps_status_t CaseV(char *input, int *output);
ps_status_t CaseX(char *input, int *output);
ps_status_t CaseInvalidInput(char *input, int *output);

typedef op_status_t (*op_t)(sem_t *sem, int *output);

op_status_t OpDec(sem_t *sem, int *output);
op_status_t OpInc(sem_t *sem, int *output);
op_status_t OpViewVal(sem_t *sem, int *output);
op_status_t OpExit(sem_t *sem, int *output);
op_status_t OpNull(sem_t *sem, int *output);
op_status_t OpUndo(sem_t *sem, int *output);

func_t g_parse_lut[ASCII] = {CaseInvalidInput};
op_t g_op_lut[22] = {OpNull};

sig_atomic_t g_undo_couner = 0;
/****************************************************************************/
int main(int argc, char *argv[])
{
	(void)argc;
	if( argc < 2 )
	{
		printf("You havent entered a sem name\nThe program chose to terminate!!!!\n");
		return 0;
	}
	SemManipulation(argv);
	return 0;
}
/****************************************************************************/

s_status_t SemManipulation(char *argv[])
{
	sem_t *sem = NULL;

	char name[MAX_INPUT_SIZE] = "";
	char input[MAX_INPUT_SIZE] = "";
	int status = PARSE_SUCCESS;
	int output[MAX_WORD_TO_PARSE] = {0};
	char letter = 0;

	sprintf(name, "/%s",argv[1]);
	
	sem = sem_open(name,O_CREAT,S_IRWXU,1);
	if( SEM_FAILED == sem )
	{
		return SEM_OPEN_ERROR;
	}

	while( PARSE_EXIT != status )
	{
		printf("Please enter command\n");
		fgets(input, MAX_INPUT_SIZE, stdin);
		letter = *input;
		status = Parser(input,output);
		if( PARSE_SUCCESS == status )
		{
			g_op_lut[letter - 'A'](sem, output);
		}

		/*printf("Exit status = %s\n", map[status]);*/
	}

	status = OpUndo(sem, output);

	sem_close(sem);

	printf("Do you wish to Unlink A named semaphore %s [Y]\n",argv[1]);

	scanf("%s", input);
	if( 'Y' == *input )
	{
		if( SEM_UNLINK_ERROR == sem_unlink(argv[1]) )
		{
			return SEM_UNLINK_ERROR;
		}
	}
	
	return SEM_SUCCESS;
}

ps_status_t Parser(char *input, int *output)
{
	char letter = 0;

	assert(input);

	memset(output, 0, MAX_WORD_TO_PARSE * sizeof(int));
	letter = *input;

	return (g_parse_lut[(int)letter](input,output));
}

ps_status_t CaseDecInc(char *input, int *output)
{
	char *end_ptr = NULL;
	output[0] = *input;
	++input;
	
	if( ' ' == *input && *(input + 1) )
	{
		output[1] = strtol(input, &end_ptr, 10);
		if( input == end_ptr )
		{
			return PARSE_NO_NUM_ERROR;
		}
		input = end_ptr;
	}
	else
	{
		return PARSE_NO_NUM_ERROR;
	}

	if( ' ' == *input && IsUndo(input + 1) )
	{
		output[2] = UNDO;
		return PARSE_SUCCESS;
	}
	else if( !strcmp(input, "\n") )
	{
		return PARSE_SUCCESS;
	}

	return PARSE_SYNTAX_ERROR;
}

ps_status_t CaseV(char *input, int *output)
{
	if( '\n' == *(input + 1) )
	{
		output[0] = *input;
		return PARSE_SUCCESS;
	}
	return PARSE_SYNTAX_ERROR;
}

ps_status_t CaseX(char *input, int *output)
{
	if( '\n' == *(input + 1) )
	{
		output[0] = *input;
		return PARSE_EXIT;
	}
	return PARSE_SYNTAX_ERROR;
}	

ps_status_t CaseInvalidInput(char *input, int *output)
{
	(void)input;
	(void)output;
	return PARSE_SYNTAX_ERROR;
}

op_status_t OpDec(sem_t *sem, int *output)
{
	int i = 0;

	assert(sem);

	for( i = 0 ;i < output[1]; ++i)
	{
		if( SEM_WAIT_ERROR == sem_wait(sem) )
		{
			return OP_SEM_FAILURE;
		}
	}
	
	
	if( UNDO == output[2] )
	{
		g_undo_couner -= output[1];
	}

	return OP_SUCCESS;
}

op_status_t OpInc(sem_t *sem, int *output)
{
	int i = 0;

	for( i = 0 ;i < output[1]; ++i)
	{
		if( SEM_POST_ERROR == sem_post(sem) )
		{
			return OP_SEM_FAILURE;
		}
	}

	if( UNDO == output[2] )
	{
		g_undo_couner += output[1];
	}

	return OP_SUCCESS;
}

op_status_t OpViewVal(sem_t *sem, int *output)
{
	int curr_val = 0;
	(void)output;

	if( 0 != sem_getvalue(sem,&curr_val))
	{
		return OP_GET_VAL_FAILURE;
	}

	printf("The semaphore value is = %d\n", curr_val);

	return OP_SUCCESS;
}

op_status_t OpExit(sem_t *sem, int *output)
{
	(void)sem;
	(void)output;
	return OP_SUCCESS;
}

op_status_t OpNull(sem_t *sem, int *output)
{
	(void)sem;
	(void)output;
	return OP_SUCCESS;
}

op_status_t OpUndo(sem_t *sem, int *output)
{
	if( g_undo_couner > 0)
	{
		while( g_undo_couner )
		{
			--g_undo_couner;
			if( SEM_WAIT_ERROR == sem_trywait(sem) )
			{
				return OP_SEM_FAILURE;
			}

		}
	}
	else
	{
		while( 0 != g_undo_couner )
		{
			++g_undo_couner;
			if( SEM_POST_ERROR == sem_post(sem) )
			{
				return OP_SEM_FAILURE;
			}
		}
	}

	printf("%d\n", g_undo_couner);

	(void)output;
	return OP_SUCCESS;
}

void __attribute__((constructor)) InitLut(void)
{
	int i = 0;
	for(i = 0; i < ASCII; ++i)
	{
		g_parse_lut[i] = CaseInvalidInput;
	}

	g_parse_lut['D'] = CaseDecInc;
	g_parse_lut['I'] = CaseDecInc;
	g_parse_lut['V'] = CaseV;
	g_parse_lut['X'] = CaseX;

	for(i = 0; i < AZ; ++i)
	{
		g_op_lut[i] = OpNull;
	}

	g_op_lut['D' - 'A'] = OpDec;
	g_op_lut['I' - 'A'] = OpInc;
	g_op_lut['V' - 'A'] = OpViewVal;
	g_op_lut['X' - 'A'] = OpExit;
	g_undo_couner = 0;
}

int IsUndo(char *str)
{
	return( !strcmp("undo\n",str));
}



