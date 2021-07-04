/****************************************************************************
 *  FILENAME:  ex2.c      NAME:  Daniel Zaken    REVIEWER:  Peleg Rosenbaum *
 *                                                                          *
 *  POURPOSE:  Copying an array                                             *
 *                                                                          *
 ****************************************************************************/
/*INCLUDE*/
#include <stdio.h> /*Required Standart input output*/
#include <stdlib.h> /*Required for allocation*/
#include <assert.h>  /*for assert*/

/*DECLERATIONS*/
int* ArrCpy (int *, int*, int);
void PrintTest (int *, int);

int main()
{
	int origin[5] = {1, 2, 3, 4, 5};
	int size = sizeof(origin) / sizeof(origin[0]); /*detemine size of origin*/
	int *new_arr = (int*)malloc(sizeof(int)*size); /*allocation for copy arr*/
	
	new_arr = ArrCpy(origin,new_arr,size);
	/*test*/
	PrintTest(origin, size);		
	PrintTest(new_arr, size);
	/*free allocation*/
	free(new_arr); 
					
	return 0;
}

int* ArrCpy(int *arr, int *new_arr, int size)
{
	int i = 0;
	
	assert(arr);
	assert (new_arr);
	
	/*transfering vars from arr to new_arr*/
	for( ; i < size ; ++i)
	{
		*(new_arr + i) = *(arr + i);
	}
			
	return new_arr;
}

void PrintTest (int *arr, int size)
{
	int i = 0;
	
	assert(arr);
	
	for ( ; i < size ; ++i)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");
}
