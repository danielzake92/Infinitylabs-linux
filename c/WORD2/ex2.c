/****************************************************************************
 *  FILENAME:  ex2.c   NAME:  Daniel Zaken    REVIEWER:  Nitzan holmes      * 
 *                                                                          *
 *  POURPOSE:  Implementation for found in str1 and str2 and not in str3    *
 *                                                                          *
 ****************************************************************************/
#include <stdio.h> /*printf required*/
#include "word2.h" /*My implemented lib*/
/****************************************************************************/
void PrintMagicPhrase(char *str1, char *str2, char *str3)
{
	int abc[26] = {0};
	int size = 26;
	int *ptr = abc;
	
	while( *str1 )
	{
		if( ( 'A' <= *str1 ) && ( 'Z' >= *str1 ) )
		{	
			if( abc[*str1 - 'A'] < 1 )
			{
				abc[*str1 - 'A'] += 1;
			}
		}
		++str1;
	}
	
	while( *str2 )
	{
		if( ( 'A' <= *str2 ) && ( 'Z' >= *str2 ) )
		{
			if( abc[*str2 - 'A'] < 5)
			{
				abc[*str2 - 'A'] += 5;
			}
		}
		++str2;
	}	
	
	while( *str3 )
	{
		if( ( 'A' <= *str3 ) && ( 'Z' >= *str3 ) )
		{
			abc[*str3 - 'A'] += 10;
		}
		++str3;
	}	
	
	while( size )
	{	
		if( *ptr == 6 )
		{
			printf("%c  ", (char)(ptr - abc) + 'A' );
		}
		++ptr;
		--size;
	}
	puts("");
}

