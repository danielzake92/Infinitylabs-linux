#include <stdio.h>

/*INCLUDE*/
#include <stdio.h>  /*required standart output*/
#include <stdlib.h>  /*required for calloc*/

int *IsSumFound (int arr[], int size, int sum);

int main()
{
	int arr1[5] = {2, 4, 7, 12, 14};
	int arr2[9] = {2, 4, 9, 10, 13, 15, 18, 42, 68};
	int *res = NULL;
	
	res = IsSumFound(arr1, 5, 21);
	printf(" isfound = %d, index1 = %d, index2 = %d\n",res[0], res[1], res[2]);
	
	res = IsSumFound(arr2, 9, 31);
	printf(" isfound = %d, index1 = %d, index2 = %d\n",res[0], res[1], res[2]);
	
	free(res);
	
	return 0;
}

int *IsSumFound (int arr[], int size, int sum)
{	
	int *start = arr;
	int *end = arr + size - 1;
	int *res = (int*)calloc( 3 , sizeof(int) );
	
	while(start < end)
	{
		
		if( sum == ( *start + *end ) )
		{
			res[0] = 1;
			res[1] = start - arr;
			res[2] = end -arr;
			return res;
		}
		if ( sum < ( *start + *end ))
		{
			--end;
			continue;
		}
		
		++start;
	}
	return res;
}

