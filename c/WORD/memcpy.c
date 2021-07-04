/****************************************************************************
 *  FILENAME:  MemCpy.c   NAME:  Daniel Zaken    REVIEWER:   Moshe Elisha   * 
 *                                                                          *
 *  POURPOSE:  Create LIB which implementes mem functions                   *
 *                                                                          *
 ****************************************************************************/
/*INCLUDES*/
#include <stdio.h> /*required printf*/
#include <assert.h> /*assert required*/
#include "mem.h" /*my implemented lib*/
/*************************************************************/
void *MemCpy(void *dest, const void * src, size_t n)
{
	unsigned char *dest_runner = (unsigned char*)dest;
	unsigned char *src_runner = (unsigned char*)src;
	unsigned char *dest_end = ( dest_runner + n -1 );
	size_t word = sizeof(dest_runner);
	int word_num = 0 ;
	
	assert(dest);
	assert(src);
			
	while( (size_t)dest_runner % (size_t)word )
	{	
		*dest_runner = *src_runner ;
		dest_runner += 1;	
		src_runner += 1;	
	}
	
	word_num = ( dest_end - dest_runner ) / word;
		
	while( word_num )
	{	
		(*(size_t*)dest_runner) = (*(size_t*)src_runner);
		dest_runner += word;	
		src_runner += word;	
		--word_num;
	}
	
	while( dest_runner <= dest_end )
	{	
		*dest_runner = *src_runner ;
		dest_runner += 1;	
		src_runner += 1;	
	}
	return dest;	
}


