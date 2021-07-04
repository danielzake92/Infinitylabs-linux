/********************************************************************************
 *  FILENAME:  mapping.c  DEVELOPER: Daniel Zaken   TEAM: Blue                  * 
 *                                                                              *
 *  Reviwer:   Itamar Aron                                                      * 
 *                                                                              *
 *                                                                              *
 *******************************************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*heap mallocs*/

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"


static void Printer(void);
int Max(int x, int y);
void Vars(char **envp, char **argv);
void Funcs(void);
/************************************/

int g_i = 20;

int bss1;
int bss2;
int bss3;
int bss4;

const int c_g_i = 21;
static int s_g_i = 22;
static const int s_c_g_i = 23;
/************************************/

int main(int argc, char *argv[], char *envp[])
{
	int test1 = 5;
	int test2 = 7;
	(void)test1;
	(void)test2;
	(void)argc;
    (void)argv;
    
    
	Vars(envp, argv);
	
	
	Funcs();

	return 0;
}


/************************************/
void Vars(char **envp, char **argv)
{
	int i = 5;
	const int c_i = 10;
	int size = 5;
	int counter = 0;
	char str1[] = "regular string1"; /*16*/
	char str2[] = "regular string2"; /*16*/
	static int s_i = 15;
	static const int s_c_i = 30;
	char *literal1 = "string literal1";
	char *literal2 = "string literal2";
	
	int *heap1 = (int*)malloc( size * sizeof(int) );
	int *heap2 = (int*)malloc( size * sizeof(int) );

	for( counter = 0; counter < size ; ++counter)
	{
		heap1[counter] = counter + 1;
	} 

	for( counter = 0; counter < size ; ++counter)
	{
		heap2[counter] = counter + 1;
	} 
	

	free(heap1);
	free(heap2);
}

void Funcs(void)
{
	return;
}

/************************************/
int Max(int x, int y)
{
	if(x > y)
	{
		return x;
	}
	return y;
}
/************************************/
static void Printer(void)
{
	puts("static void function named Printer");
}
