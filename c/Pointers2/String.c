/****************************************************************************
 *  FILENAME:  ex1.c      NAME:  Daniel Zaken    REVIEWER:  Nitzan Holmes   *
 *                                                                          *
 *  POURPOSE:  Implementing String.h lib                                    *
 *                                                                          *
 ****************************************************************************/

#include "String.h"  /*Implemented string library*/
  
size_t StrLen(const char *str)
{
	const char *start = NULL;
	assert(str);
	
	start = str;
	
	while(*str)
	{
		++str;
	}
	return (str-start);
}

/* 
****	STRCMP - Implemented function	****
*/
int StrCmp(const char *s1, const char *s2)
{
	assert(s1);
	assert(s2); 
	
	while( *(s1) && ( *(s1) == *(s2) ))
	{
		++s1;
		++s2;
	}
			
	return *(s1) - *(s2);
}
/* 
****	STRCASECMP - Implemented function	****
*/
int StrCaseCmp(const char *s1, const char *s2)
{
	assert(s1);
	assert(s2); 
	
	while( tolower(*(s1)) && ( tolower(*(s1)) == tolower(*(s2)) ))
	{
		++s1;
		++s2;
	}
			
	return tolower(*(s1)) - tolower(*(s2));
}
/* 
****	STRCPY - Implemented function	****
*/
char *StrCpy(char *destination, const char *source)
{
	char *start = destination;		
	assert(destination);
	assert(source);	
			
	while (*source)
	{
		*destination = *source;
		++destination;
		++source;
	}
	
	*destination = '\0';	
	
	return start ;
}
/* 
****	STRNCPY - Implemented function	****
*/
char *StrnCpy(char *destination, const char *source, size_t n)
{
    size_t i = 0;    
    assert(destination);
    assert(source);    
            
    while (++i <= n)
    {    
        if(!source) /*arrived to NULL*/
        {
            *destination = '\0';
        }
        else
        {
            *destination = *source;
        }
        ++destination;
        ++source;
    }
    
    *destination = '\0';    
    
    return destination-n ;
}
/* 
****	STRCHR - Implemented function	****
*/
char *StrChr(const char *destination, int ch)   
{
	assert(destination);
	
	while(*destination)
	{	
		if (*destination == (char)ch )
		{
			return (char*)destination;
		}
		++destination;
	}
	
	return NULL;
}
/* 
****	STRDUP - Implemented function	****
*/
char *StrDup(const char *str)
{
	char *dup = (char*)malloc( (StrLen(str) + 1) * sizeof(char) );
	
	assert(str);
	
	if (!dup)
	{
		return NULL;
	}
	
	StrCpy(dup, str);
	return dup;
}
/* 
****	STRCAT - Implemented function	****
*/
char *StrCat(char *dest, const char *src)
{
	
	char *mid = dest + StrLen(dest) ;
		
	assert(dest);
	assert(src);	
			
	while (*src)
	{
		*mid = *src;
		++mid;
		++src;
	}
	
	*mid='\0';	
	
	return dest ;
}
/* 
****	STRNCAT - Implemented function	****
*/
char *StrnCat(char *dest, const char *src, size_t n)
{	
	size_t i = 0;
	char *mid = dest + StrLen(dest) ;
	
	assert(dest);
	assert(src);	
			
	while (++i <= n)
	{	
	
		if (!src)
		{
			*mid = '\0';	
		}
		else
		{
			*mid = *src;
		}
		++mid;
		++src;
	}
	
	*mid = '\0';	
	
	return dest ;

}
/* 
****	STRSTR- Implemented function	****
*/

char *StrStr(const char *str, const char *needle)
{
	size_t len_needle = StrLen(needle);
		
	assert(str);
	assert(needle);
	
	str = StrChr(str, *needle);
		
	while(*str)
	{
		if (! strncmp(needle, str,len_needle ))
		{
			return ( (char*)str ) ;
		}
		++str;
	}
	return NULL;
}

/* 
****	STRSPN- Implemented function	****
*/
size_t StrSpn(const char *code, const char *hashed)
{	
	size_t i = 0;

	assert(code);
	assert(hashed);
	
	while(*code)
	{
		if ( ! StrChr(hashed, *code) )
		{
			break;
		}
		
		++i;	
		++code;
	}
	return i;
}




