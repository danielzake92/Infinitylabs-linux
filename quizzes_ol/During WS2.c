#include <stdio.h>
#include <string.h>

void TF(int );
char *RevToLower(char *);
char ToLower(char);

int main()
{
	int num1 = 9;
	int num2 = 10;
	int num3 = 15;
	int num4 = 16;
	
	char *str="hello world";
	
	printf("%s", RevToLower(str));
		
    TF(num1);
    puts("");
    TF(num2);
    puts("");
    TF(num3);
    puts("");
    TF(num4);
    puts("");
    
    
    
	return 0;
}

void TF(int num)
{
	
	
	if ( 0 == num%3 )
	{
		printf("T");
	}
	if ( 0 == num%5 )
	{
		printf("F");
	}		
	if ( 1 == num%3 && 1 == num%5)
	{
		printf("%d",num);
	}	
	
}

char *RevToLower(char *str)
{
	size_t len = strlen(str);
	char *end = str + len;
	char temp;
	
	while(len)
	{
		temp = *str;
		*str = * end;
		*end = temp;
		++str;
		--end;
		--len;		
	}
	return(end);

}

   
