/****************************************************************************
 *  FILENAME:  ex3.c      NAME:  Daniel Zaken    REVIEWER:  Peleg Rosenbaum *
 *                                                                          *
 *  POURPOSE:  Print addresses of different types of variables              *
 *                                                                          *
 ****************************************************************************/
/*INCLUDE*/
#include <stdio.h> /*Required Standart input output*/
#include <stdlib.h> /*Required for allocation*/
#include <assert.h>  /*for assert*/

void PrintAdresses ();

int main()
{
	PrintAdresses();
			
	return 0;
}

void PrintAdresses()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));
	
	printf("Address of s_i = %p\n",(void*)&s_i);
	printf("Address of i = %p\n",(void*)&i);
	printf("Address of ptr = %p\n",(void*)&ptr);
	printf("Address of ptr2 = %p\n",(void*)&ptr2);
	
	free(ptr2);
			
}


