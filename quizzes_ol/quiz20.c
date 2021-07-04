#include <stdio.h>
#include <string.h>
#include <assert.h>

void StrRev(char *str, int n);
char* WordRev(char* str);
void SwapChars(char *a, char *b);

int main()
{
	char str[] = "my name is daniel";
	
	printf("original string - \"%s\"\n", str);
	
	printf("reversed string - \"%s\"\n", WordRev(str));
	
	return 0;
}


char* WordRev(char* str)
{
	char *from = NULL;
	char *to = NULL;	
	
	assert(str);
	
	from = str;
	to = str;
	
	StrRev(str, strlen(str));
	
	while (*to)
	{
		while ( ' ' != *to && *to )
		{
			++to;
		}
		
		StrRev( from, to - from );
		++to;
		from = to;
	}
	return str;
}


void StrRev(char *str, int n)
{
    int i = 0;
    char *begin = str;
    char *end = NULL;
 	
    end = (str + n -1);
 
    while (i < n/2)
    {        
       SwapChars(begin, end);
       begin++;
       end--;
       i++;
    }
}

void SwapChars(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}









