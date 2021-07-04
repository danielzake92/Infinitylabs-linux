#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int Parentheses(char *string);
int IsInTheArr(char arr[], int size, int num);
void StrRev(char *str, int n);
char* RotateInPlace(char *arr, int size, int n_rotate);
int main()
{
	char str1[] = {'a','b','3','d','z','A'};
	/*char str2[] = "hello world";*/
	
	
	printf("checking if %c is in str 1 - %d \n",'a',IsInTheArr(str1, 6, 'a'));
	printf("checking if %c is in str 1 - %d \n",'B',IsInTheArr(str1, 6, 'B'));
	printf("checking if %c is in str 1 - %d \n",'C',IsInTheArr(str1, 6, 'C'));

	/*StrRev(str2,8);*/
	
	
	printf("%s\n",str1);
	RotateInPlace(str1, strlen(str1), 1);
	printf("%s\n",str1);
	RotateInPlace(str1, strlen(str1), -1);
	printf("%s\n",str1);
	
	return 0;
}


int IsInTheArr(char arr[], int size, int num)
{
	int i = 0;
	int res = 1;
	while( i < size && res )
	{	
		res = arr[i] - num;
		++i;
	}
	return !res;
}


char* RotateInPlace(char *arr, int size, int n_rotate)
{
	
	int dir = 1;
	int num_rotation = 0;
	
	if( n_rotate < 0 )
	{
		n_rotate *= -1;
		dir = 0;
	}
	num_rotation = n_rotate % size;
	
	StrRev(arr,strlen(arr));
	/*puts("im here");*/
	
	if (dir)
	{
		StrRev(arr,num_rotation);
		StrRev(arr + num_rotation ,size - num_rotation);
	}
	else
	{
		StrRev(arr,size - num_rotation);
		StrRev(arr + size - num_rotation , num_rotation);
	}
	
	
	return arr;
	
}

void StrRev(char *str, int n)
{
    int length = 0; 
    int i = 0;
    char temp = 0;
    char *begin = str;
    char *end = NULL;
        
    length = strlen(str);
 	
 	length = MIN(length, n);
 	
    end = (str + length -1);
 
    while (i < length/2)
    {        
       temp   = *end;
       *end   = *begin;
       *begin = temp;
 
       begin++;
       end--;
       i++;
    }
}
