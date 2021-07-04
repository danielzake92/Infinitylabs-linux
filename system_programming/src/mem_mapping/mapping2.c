/********************************************************************************
 *  FILENAME:  mapping.c  DEVELOPER: Daniel Zaken   TEAM: Blue                  *
 *                                                                              *
 *  Reviwer:   ---------                                                        *
 *                                                                              *
 *                                                                              *
 *******************************************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*heap mallocs*/
#include <string.h>
#include <assert.h>
#include "mapping2.h"

/************************************/


static int s_g_i = 22;
static const int s_c_g_i = 23;
/************************************/


void Funcs(void)
{
	char *str="helloworld";

	printf("%p\n");

	return;
}

/************************************/
int Max(int x, int y)
{
	if(x > y)
	{
		return x;
	}
	return y;
}

char* WordRev(char* str)
{
	char *from = NULL;
	char *to = NULL;

	(void) s_g_i;
	(void) s_c_g_i;


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
