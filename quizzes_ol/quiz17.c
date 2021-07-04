#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define EXIST 0x9090909

int FindSmallestKNumber(int *arr, int k, int size);

int main()
{
	int arr[7] = { 3, 88, 93, 250, 5, 99, 33};  /*3, 5, 33, 88, 93, 99, 127*/
	int size = 7;
	int k = 3;
	
	int res = FindSmallestKNumber(arr, k, size);
	
	printf("res = %d\n", res);
	
	return 0;
}

int FindSmallestKNumber(int *arr, int k, int size)
{
	int max_num = 0;
	int res = 0;
	int *temp = NULL;
	int count = 0;
	int i = 0;
	
	
	for( i = 0 ; i < size ; ++i) max_num = MAX(max_num, arr[i]);
		
	temp = (int*)malloc( max_num * sizeof(int) );

	for( i = 0 ; i < size ; ++i) temp[arr[i]] = EXIST;
	
	for( i = 0 ; k != count ; ++i) 
	{
		if( EXIST == temp[i] ) ++count;
	}
	
	res = i - 1;
	free(temp);
	
	return res;	
}
