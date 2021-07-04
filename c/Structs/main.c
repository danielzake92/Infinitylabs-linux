/*INCLUDE*/
#include <stdio.h>
#include "structs.h"
/*DEFINE*/
#define SIZE 4

static element_t g_chain[SIZE];

int main()
{	
	int i = 0;
	
	/*Initialize chain*/
	InitilizeInt(&g_chain[0], 10);
	InitilizeFloat(&g_chain[1], 10.52);
	InitilizeString(&g_chain[2], "hello world");
	InitilizeString(&g_chain[3], "This is my test");
	
	printf ("\033[34;1mINITIALIZE\033[0m \n");/*blue msg*/	
	
	for (i = 0; i < SIZE ; ++i)
	{
		g_chain[i].print(&g_chain[i]);
	}
			
	for (i = 0; i < SIZE ; ++i)
	{
		g_chain[i].add(&g_chain[i], 30);
	}
	
	printf ("\033[34;1mADDING 30\033[0m \n");/*blue msg*/	
	
	for (i = 0; i < SIZE ; ++i)
	{
		g_chain[i].print(&g_chain[i]);
	}
	
	for (i = 0; i < SIZE ; ++i)
	{
		g_chain[i].free_data(&g_chain[i]);
	}
			
	return 0;
}

