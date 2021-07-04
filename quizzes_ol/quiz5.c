/****************************************************************************
 * FILENAME: quiz5.c 	AUTHOR: Daniel Zaken		                        *
 *																			*
 * PURPOSE: Bursa buy & sell                                         		*
 *																			*
 ****************************************************************************/

#include <stdio.h>  /*required standart output*/

int Bursa (int arr[], int size, int *b, int *s);

int main()
{
	int arr1[8] = {6, 12, 3, 5, 1, 4, 9, 2};
	int b = 0;
	int s = 0;
	int rev = Bursa(arr1, sizeof(arr1) / sizeof(arr1[0]), &b, &s);
	
	printf("rev = %d\nbuy index = %d\nsell index = %d\n", rev, b, s);
		
	return 0;
}

int Bursa (int arr[], int size, int *buy, int *sell)
{
	int *end = &(arr[size-1]);
	int rev = 0;
	int *b = arr;
	int *s = arr + 1;
	
	while ( s <= end )
	{	
		
		if( (*s - *b) > rev )
		{
			rev = *s - *b;
			*sell = s - arr;	 
		}
		if ( *s < *b )
		{
			b = s;
		}
		++s;
	}
				
	*buy = b - arr;
	return rev;
}

