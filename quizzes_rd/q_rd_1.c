#include <stdio.h>

int FindMinInRotatedAndSorted(int *arr, size_t size);

int main()
{
	/* ANS IS 1 */

	int arr1[6] = {4, 5, 1, 2, 3};
	size_t size1 = 6;
    
	int arr2[8] = {15, 19, 22, 33, -1, 8, 9, 10};
	size_t size2 = 8;

	int arr3[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t size3 = 10;
	
	printf("The min num = %d\n",FindMinInRotatedAndSorted(arr1, size1));
	printf("The min num = %d\n",FindMinInRotatedAndSorted(arr2, size2));
	printf("The min num = %d\n",FindMinInRotatedAndSorted(arr3, size3));

	return 0;
}

int FindMinInRotatedAndSorted(int *arr, size_t size)
{
	int l = 0;
	int r = size - 1;
	int m = (l + r) / 2;

	while( l < r )
	{
		if(arr[m] > arr[0])
		{
			l = m + 1;
		}
		else
		{
			r = m ;
		}
		m = (l + r) / 2;
	}

	if( (size_t)m == size - 1)
	{
		return arr[0];
	}
	return arr[m];
}