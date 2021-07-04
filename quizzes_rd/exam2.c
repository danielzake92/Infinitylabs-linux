#include <stdio.h>
#include <string.h>
 
/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
    char temp = *x;;
    *x = *y;
    *y = temp;
}
 
void Permute(char *arr, int left, int right)
{
	int i = left;
	if (left == right)
	{	
		printf("%s\n", arr);
		return;
	}
	for (i = left; i <= right; i++)
	{
		swap(&arr[left], &arr[i]);
		Permute(arr ,left + 1 , right);
		swap(&arr[left], &arr[i]);
	}
}



int main()
{
    char str[] = "123";
    int n = strlen(str);
    Permute(str, 0, n-1);
    return 0;
}