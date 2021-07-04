#include <stdio.h>
#include <assert.h>

int MaxSubArray(int arr[], int size, int *i_start, int *i_end);

int main()
{
	int arr[9] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	int i_start = 0;
	int i_end = 0;
	MaxSubArray(arr, 9, &i_start, &i_end); 
	
	return 0;
}

int MaxSubArray(int arr[], int size, int *ind1, int *ind2)
{	
	int max_sum = arr[0];
	int temp_sum = arr[0];
	int i = 0;
	
	*ind1 = 0;
	*ind2 = 0;
	while( i < size )
	{
		if( temp_sum > max_sum )
		{
			max_sum = temp_sum;
			*ind2 = i;
		}
		if( arr[i] > temp_sum )
		{
			temp_sum = arr[i];
			
			*ind1 = i;
		}
		++i;
		temp_sum += arr[i];
	}
	printf("sum = %d, i_start = %d, i_end = %d\n", max_sum, *ind1, *ind2);
	return max_sum;
}







