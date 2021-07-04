/****************************************************************************
 *  FILENAME:  MemMove.c   NAME:  Daniel Zaken    REVIEWER:  Moshe Elisha   * 
 *                                                                          *
 *  POURPOSE:  Create LIB which implementes mem functions                   *
 *                                                                          *
 ****************************************************************************/
/*INCLUDES*/
#include <stdio.h> /*required printf*/
#include <assert.h> /*assert required*/
#include "mem.h" /*my implemented lib*/
/*************************************************************/
void *MemMove(void *dest, const void * src, size_t n)
{
	unsigned char *dest_start = NULL;
	unsigned char *src_start = NULL;
	unsigned char *dest_end = NULL;
	unsigned char *src_end = NULL;
	size_t word = 0;
	int word_num = 0;
	
	assert(dest);
	assert(src);
		
	dest_start = (unsigned char*)dest;
	src_start = (unsigned char*)src;
	dest_end = dest_start + n -1;
	src_end = src_start + n -1;
	word = sizeof(dest_end);
			
	/*overlapping*/
	if( ( src_start < dest_start ) && ( (src_start + n) > dest_start ) )
	{	
					
		while( (size_t)dest_end % (size_t)word )
		{	
			*dest_end = *src_end ;
			dest_end -= 1;	
			src_end -= 1;	
		}
		
		word_num = ( dest_end - dest_start ) / word;
		
		while( word_num )
		{	
			dest_end -= word;	
			src_end -= word;	
			(*(size_t*)dest_end) = (*(size_t*)src_end);
			--word_num;
		}	
		
		while( dest_end >= dest_start )
		{	
			/*puts("while ending");*/
			*dest_end = *src_end ;
			dest_end -= 1;	
			src_end -= 1;	
		}
		return dest;
	}	
	
	return ( MemCpy(dest, src, n) );
}


