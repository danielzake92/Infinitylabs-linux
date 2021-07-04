/****************************************************************************
 *  FILENAME:  ex1.c   NAME:  Daniel Zaken    REVIEWER:                     * 
 *                                                                          *
 *  POURPOSE:  Implementation of Itoa / Atoi                                *
 *                                                                          *
 ****************************************************************************/
#include <stdio.h> /*printf required*/
#include <string.h>
#include <assert.h> /*Requred assert*/
#include "word2.h" /*My implemented lib*/
/****************************************************************************/

static char ValMod(int n);
void StrRev(char *str);

int Atoi_base(const char *str, size_t base)
{
	int res = 0;
	short minus = 1;
	int dig_last = 0;
	int let_first = 'A';
	int let_last = 0;
	
	assert(str);
	
	if( base <= 1 ) return 0;
		
	if( base <= 10 )
	{
		dig_last = '0' + base -1;
	}
	else
	{
		dig_last = '9';
		let_last = 'A' + (base - 11);
	}
		
	if( *str == '-' )
	{
		++str;
		minus = -1;
	}
				
	while( *str )
	{
		if( ( 48 <= *str ) && ( dig_last >= *str ) )
		{
			res = (res * base) + (*str - '0');
			++str;
			continue;
		}
		if( ( let_first <= *str ) && ( let_last >= *str ) )
		{
			res = (res * base) + (*str - 55);
			++str;
			continue;
		}
		break;
		
	}
	return res * minus;
}


void Itoa_base(int num, char *str, size_t base)
{
	char *runner = NULL;
	short is_neg = 0;	
	assert(str);
	
	runner = str;
	
	if( num < 0 )
	{
		num *= -1;
		is_neg = 1;
	}
	
	while( num > 0 )
	{
		*runner = ValMod(num % base);
		num /= base;
		++runner;
	}
	
	if(is_neg)
	{
		*runner = '-';
		++runner;
	}
		
	*runner = '\0';
	StrRev(str);
	
}

static char ValMod(int n)
{
	if ( 0 <= n && 9 >= n )
	{
		return (n + '0') ;
	} 
	if ( 10 <= n && 36 >= n )
	{
		return (n + 55) ;
	}
	return 0;
}

void StrRev(char *str)
{
    int length = 0; 
    int i = 0;
    char temp = 0;
    char *begin = str;
    char *end = NULL;
        
    length = strlen(str);
 
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



