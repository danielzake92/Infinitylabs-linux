#include <stdio.h>
#include <stddef.h>
int Atoi(char *str, int base);
int main()
{
	printf ("\033[34;1mAtoi - TEST\033[0m \n");/*blue msg*/	
	
	printf("my_imp : %d source : %d \n",Atoi("00ZZA", 36), 46630);
	printf("my_imp : %d source : %d \n",Atoi("00FFA", 16), 4090);
	
	printf("my_imp : %d     source : %d \n",Atoi("-FF", 16), -255);
	printf("my_imp : %d    source : %d \n",Atoi("-ZZ", 36), -1295);
	
	return 0;
}

int Atoi(char *str, int base)
{
	int res = 0;
	int minus = 1;
	char last_dig = '0';
	char first_ch = 'A';
	char last_ch = 'A';
	
	if(base <= 1) return 0;
	
	if(base <= 10) 
	{
		last_dig = '0' + base - 1;
	}
	else
	{
		last_dig = '9';
		last_ch = base -11 + 'A';
	}

	if( *str == '-' )
	{
		++str;
		minus = -1;
	}

	while(*str)
	{
		if( ('0' <= *str) && (last_dig >= *str) )
		{
			res = res * base + (*str - '0');
			++str;
			continue;
		}
		if( (first_ch <= *str ) && (last_ch >= *str) )
		{
			res = res * base + (*str - 'A' + 10);
			++str;
			continue;
		}
		break;	
	}
	return minus*res;
}
