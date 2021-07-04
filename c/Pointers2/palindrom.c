/******************************************************************************
 *  FILENAME:  palindrom.c  NAME:  Daniel Zaken    REVIEWER:  Nitzan Holmes   *
 *                                                                            *
 *  POURPOSE:  Cheack of a string is a palindrom                              *
 *                                                                            *
 ******************************************************************************/
/*INCLUDE*/
#include <stdio.h> /*Required Standart input output*/
#include <string.h> /*required for strlen*/
#include <assert.h>  /*For assert*/

int IsPalindrom(const char *);

int main()
{
	char *pal1 = "adnnsa";
	char *pal2 = "palinilap";
	int i = IsPalindrom(pal1);
	int j = IsPalindrom(pal2);
	
	printf("i = %d\nj = %d\n",i,j); 
	puts("");		
	return 0;
}

/* 
****	ISPALLINDROM - Implemented function    ****
*/
int IsPalindrom(const char *src)
{
	const char *start = src;
	const char *end = src + strlen(src) -1;
	
	while( start < end )
	{	
		if ( *start != *end )
		{
			return 0;
		}
		++start;
		--end;
	}

	return 1;

}







