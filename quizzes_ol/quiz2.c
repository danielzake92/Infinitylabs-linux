/*INCLUDE*/
#include <stdio.h>  /*required standart output*/
#include <string.h>  /*required strlen*/
#include <ctype.h>  /*required tolower*/
#include <assert.h>  /*required assert*/

/*DECLERATIONS*/
void TF(int);
char *RevToLower(char *);
char *StringToLower(char *);
void ChSwap (char* , char*);

int main()
{
	char str1[] = "hEllo wQrld";
		
	RevToLower(str1);
	printf("the new string is - %s ",str1);
	
	puts("");
	TF(15);

	return 0;
}

char *RevToLower(char *str)
{
	size_t len = strlen(str);
	char *start = str;
	char *end = str + (len - 1);
	
	str = StringToLower(str);
	 
	while(end > start)
	{
		
		ChSwap(start, end);
		
		++start;
		--end;
	}
	return end;
}

void ChSwap (char *a , char *b)
{
	
	char temp = *a;
	*a = *b;
	*b = temp;
}

char *StringToLower(char *str)
{
	char *start = str;
	
	assert(str);	
	
	while(*str)
	{
		*str = tolower(*str);
		++str;
	}
	
	return start;
}

void TF(int num)
{
	int i = 1;
	while( i <= num)
	{
		if (i % 3 == 0)
		{
			printf("T");
		}
		if (i % 5 == 0)
		{
			printf("F");
			puts("");	
			++i;
			continue;
		}
		if (i % 3 && i % 5)
		{
			printf("%d",i);
		}
	puts("");	
		++i;
	}	
	
}

