/****************************************************************************
 *  FILENAME:  Env printing  NAME:  Daniel Zaken  REVIEWER:  Liad oz        *
 *                                                                          *
 *  POURPOSE:  Environment variables printing                               *
 *                                                                          *
 ****************************************************************************/
 /*INCLUDES*/
#define _POSIX_C_SOURCE 200809L /*for strdup*/
#include <stdio.h> /*standart output required*/
#include <stdlib.h>  /*required allocation*/
#include <string.h>  /*required strdup*/
#include <ctype.h>  /*required tolower*/
#include <assert.h>  /*required assert*/

/*PROTOTYPE*/
char **EnvCpy(char **);
void PrintEnv (char **);
size_t NumOfStrings(char **);
void Free(char **);
char *StringToLower(char *);

int main(int argc, char *argv[], char *envp[])
{	
	char **buffer = EnvCpy(envp);
	
	if (!buffer)
	{
		return 0;
	}
			
	(void)argc;
	(void)argv;
	
	PrintEnv(buffer);
	/*Free(buffer);*/
		
	return 0;
}


size_t NumOfStrings(char **src)
{	
	size_t num = 0;
	
	assert(src);
				
	while(*src)
	{
		++num;
		++src;
	}
	printf("\n    num =%lu\n", num);	
	return num;
}

char **EnvCpy(char **src)
{	
	char **cpy = NULL;
	char **start = NULL;
	size_t num = 0;
	
	assert(src);
	
	num = NumOfStrings(src) + 1;
		
	cpy = (char**)malloc( num * sizeof(char*) );
	
	if (!cpy)
	{
		puts("Allocation failed");
		return NULL;
	}
	
	start = cpy;
		
	while(*src)
	{	
		*cpy = strdup(*src);
		++cpy;
		++src;
	}
	*cpy = NULL;
			
	return start;
}



void PrintEnv(char **src)
{
		
	assert(src);
	
	while(*src)
	{
		printf(" \n%s ", StringToLower(*src));	
		++src;	
	}
	puts("");
}

void Free(char **src)
{
	char **start = NULL;	
	
	assert(src);
	
	start = src;
	
	while(*src)
	{
		free(*src);	
		++src;	
	}
	free(start);
}

char *StringToLower(char *str)
{
	char *start = str;
	
	assert(str);	
	
	while(*str)
	{
		*str = tolower(*str);
		++str;
	}
	
	return start;
}









