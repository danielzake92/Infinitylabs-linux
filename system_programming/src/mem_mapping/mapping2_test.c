/********************************************************************************
 *  FILENAME:  mapping.c  DEVELOPER: Daniel Zaken   TEAM: Blue                  *
 *                                                                              *
 *  Reviwer:   Peleg Rosenbaum                                                  *
 *                                                                              *
 *                                                                              *
 *******************************************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*heap mallocs*/
#include <dlfcn.h>
/*#include "mapping2.h"*/

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"

static void PrintSharedGlobals(void);


typedef char*(*func_t)(char*);

/*
extern int g_i, bss1, bss2, bss3, bss4;
extern char *literal1, *literal2;
extern int c_g_i;
*/
int main()
{
	int x = 5;
	int y = 2 * x;
	int size = 10;
	int *heap1 = (int*)malloc( size * sizeof(int));
	int *heap2 = (int*)malloc( size * sizeof(int));
	char str[] = "hello my name is daniel";

	void *handle = dlopen("./libmapping2.so", RTLD_LAZY);

	func_t *WordRev = dlsym(handle, "WordRev");
	int *bss1 = dlsym(handle, "bss1");
	int *c_g_i = dlsym(handle, "c_g_i");

	(void)WordRev;
	(void)bss1;
	(void)c_g_i;

	dlclose(handle);

	/*WordRev(str);*/

	printf("%s\n",str);

	printf("y = %d\n",y);

  	PrintSharedGlobals();

	free(heap1);
	free(heap2);

	return 0;
}

static void PrintSharedGlobals(void)
{
	/*
	printf(GREEN"g_i address : "YELLOW"%p\n", (void*)&g_i);
	printf(GREEN"bss1 address : "YELLOW"%p\n", (void*)&bss1);
	printf(GREEN"bss2 address : "YELLOW"%p\n", (void*)&bss2);
	printf(GREEN"bss4 address : "YELLOW"%p\n", (void*)&bss4);
	printf(GREEN"bss3 address : "YELLOW"%p\n", (void*)&bss3);

	printf(GREEN"literal1 address : "YELLOW"%p\n", (void*)&literal1);
	printf(GREEN"literal2 address : "YELLOW"%p\n",(void*)&literal2);

	printf(GREEN"c_g_i address : "YELLOW"%p\n",(void*)&c_g_i);
*/
}
