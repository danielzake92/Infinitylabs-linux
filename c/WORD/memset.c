/****************************************************************************
 *  FILENAME:  MemSet.c   NAME:  Daniel Zaken    REVIEWER:   Moshe Elisha   * 
 *                                                                          *
 *  POURPOSE:  Create LIB which implementes mem functions                   *
 *                                                                          *
 ****************************************************************************/
/*INCLUDES*/
#include <stdio.h> /*required printf*/
#include <assert.h> /*assert required*/
#include "mem.h" /*my implemented lib*/
/*************************************************************/
static size_t WordMaker(size_t word, int c)
{
	size_t word_chunk = c;
	size_t i = 0;
	for ( i = 0 ;  i < word ; ++i) 
    {
    	word_chunk |= (word_chunk << word);
    }
    return word_chunk;
}

void *MemSet(void *str, int c, size_t n)
{
	unsigned char *runner = (unsigned char*)str;
	unsigned char *end = ( runner + n );
	size_t word = sizeof(str);
	int word_num = 0 ;
	size_t word_chunk = WordMaker(word, c);
	assert(str);
			
	if (n < word)
	{
		while( runner < end )
		{	
			*runner = c ;
			runner += 1;		
		}
		return str;
	}
	
	while( (size_t)runner % (size_t)word )
	{	
		*runner = c ;
		runner += 1;		
	}
	
	word_num = ( end - runner ) / word;
	
	while(word_num)
	{
		(*(size_t*)runner) = word_chunk;
		runner += word;
		--word_num;
	}
		
	while( runner < end )
	{	
		*runner = c ;
		runner += 1;		
	}
		
	return str;
	
}




