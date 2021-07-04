/****************************************************************************
 *  FILENAME:  logger.c   NAME:  Daniel Zaken    REVIEWER:  Nitzan Holmes   *
 *                                                                          *
 *  POURPOSE:  loogers implementation.                                      *
 *                                                                          *
 ****************************************************************************/
/*INCLUDES*/
#include <stdio.h> /*Standart i/o required*/
#include <string.h> /*Standart String functions required*/
#include <stdlib.h> /*reuqired exit*/
/*DEFINE*/
#define ENTER 10
#define MAX 100
#define SIZE 5

/*ENUM*/
enum status
{
	SUCCESS = 0,
	ERR_RMV = -1,
	ERR_OPEN = -2,
	ERR_CLOSE = -3,
	ERR_RENAME = -4,
	ERR_FPUTS = -5,
	ERR_UNKNOWN = -6,
	EXIT = -9,
	NONE = -10
}status_t;

typedef int (*operation_ptr) (const char *, char *); 	

/*STRUCT*/
typedef struct operation
{
	char key[MAX];
	int (*cmp) (const char *str1, const char *str2); 	
	operation_ptr op;  	
} operation_t;

static operation_t g_op[SIZE] = {0};

/*DELCLERATIONS*/
static int Remove(const char *f_name, char *line);
static int Count(const char *f_name, char *line);
static int Exit(const char *f_name, char *line);
static int StartAdd(const char *f_name, char *line);
static int Append(const char *f_name, char *line);
static int FirstCharCmp (const char *str1, const char *str2);
static int AppendCmp (const char *str1, const char *str2);
static void StrucInit();
static void RunLogger(const char *f_name);
static int Routine(char *line);
static void ErrHandler(int status);


int main(int argc, char *argv[])
{
	(void)argc;
		
	RunLogger(argv[1]);
	
	return 0;
}

void RunLogger(const char *f_name)
{	
	char line[MAX] = "";
	
	int feedback = NONE; 
	
	StrucInit(); /*initialize structure*/
	while(1)
	{	
		printf("Please enter a line with maximum of %d charachters\n", MAX-1);
		fgets(line, MAX , stdin);
		feedback = g_op[Routine(line)].op(f_name, line);
		ErrHandler(feedback);
	}
}


int Remove(const char *f_name, char *line)
{
	int feedback = NONE;
	(void)f_name;
	(void)line;
		
	if( (feedback = remove(f_name) ) != 0) return (ERR_RMV); 
	
	printf("The file %s has been removed\n\n", f_name);
	
	return(SUCCESS);	
}

int Count(const char *f_name, char *line)
{	
	FILE *file = NULL;
	char ch = 0;
	size_t count = 0;
	int feedback = NONE;
	(void)line;
	
	if ( ( file = fopen(f_name, "r") ) == NULL ) return(ERR_OPEN);
			
	while( (ch = fgetc(file) ) != EOF)
	{
		if( ch == '\n' )
		{
			++count;
		}
	}
		
	printf("There are %lu lines in this document\n", count);
	
	if( (feedback = fclose(file) ) != 0) return (ERR_CLOSE); 
			
	return(SUCCESS);	
}



int StartAdd(const char *f_name, char *line)
{	
	const char *newname = "newfile.txt";
	char ch = 0;
	int feedback = NONE;
	FILE *f_src = NULL;
	FILE *f_new = NULL;
	
	if ( ( f_src = fopen(f_name, "r") ) == NULL ) return(ERR_OPEN);
	if ( ( f_new = fopen(newname, "a") ) == NULL ) return(ERR_OPEN);
	/*Adding the new line to a new file with a temp name*/
	++line;
	
	if( (feedback = fputs(line, f_new) ) == EOF) return (ERR_FPUTS); 
		
	/*copy from the old file to the new file*/
	ch = fgetc(f_src);
	while ( ch != EOF )
	{
		fputc(ch, f_new);
		ch = fgetc(f_src);
	}
	/*closing old file, deleting it and renaming the new file*/
	
	if( (feedback = fclose(f_src) ) != 0) return (ERR_CLOSE); 

	if( (feedback = remove(f_name) ) != 0) return (ERR_RMV); 
	
	if( (feedback = rename(newname,f_name) ) != 0) return (ERR_RENAME);
		
	if( (feedback = fclose(f_new) ) != 0) return (ERR_CLOSE); 
		
	return(SUCCESS);	
}

int Append(const char *f_name, char *line)
{
	FILE *file = NULL;
	int feedback = NONE;
	
	if ( ( file = fopen(f_name, "a") ) == NULL ) return(ERR_OPEN);
	
	if( (feedback = fputs(line, file) ) == EOF) return (ERR_FPUTS);
	
	if( (feedback = fclose(file) ) != 0) return (ERR_CLOSE); 
		
	return(SUCCESS);	
}

int Exit(const char *f_name, char *line)
{	
	(void)f_name;
	(void)line;
	return(EXIT);
}

int FirstCharCmp (const char *str1, const char *str2)
{
	if (*str1 == *str2)
	{
		return 0;
	}
		return 1;
}

int AppendCmp (const char *str1, const char *str2)
{
	(void)str1;
	(void)str2;
	return 0;
}

int Routine(char *line)
{
	int i = 0;
	
	for(;i < SIZE ;++i)
	{
		if (! g_op[i].cmp(g_op[i].key, line) )
		{
			return i;
		}
	}
	return ERR_UNKNOWN;
}

void StrucInit()
{
	strcpy(g_op[0].key, "-remove\n");
	strcpy(g_op[1].key, "-count\n");
	strcpy(g_op[2].key, "-exit\n");
	strcpy(g_op[3].key, "<");
	strcpy(g_op[4].key, "");
		
	g_op[0].op = Remove;
	g_op[1].op = Count;
	g_op[2].op = Exit;
	g_op[3].op = StartAdd;
	g_op[4].op = Append;
	
	g_op[0].cmp = strcmp;
	g_op[1].cmp = strcmp;
	g_op[2].cmp = strcmp;
	g_op[3].cmp = FirstCharCmp;
	g_op[4].cmp = AppendCmp;

}

void ErrHandler(int status)
{
	switch (status)
	{
		case SUCCESS :
		{
			break;
		}
		case ERR_RMV:
		{	
			puts("Error while tyring to remove the file");
			break;
		}
		case ERR_OPEN:
		{	
			puts("Error while tyring to open the file");
			break;
		}
		case ERR_CLOSE:
		{	
			puts("Error while tyring to close a file");
			break;
		}
		case ERR_RENAME :
		{	
			puts("Error while tyring to rename a file");
			break;
		}
		case ERR_FPUTS :
		{	
			puts("Error while tyring to use fputs function");
			break;
		}
		case ERR_UNKNOWN :
		{	
			puts("Error unknown");
			break;
		}
		case EXIT :
		{
			exit(1);
		}
		default :
		{
			break;
		}
	}
	
	
}



