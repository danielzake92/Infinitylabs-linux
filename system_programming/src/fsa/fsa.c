/********************************************************************************
 *  FILENAME:  fsa.c  DEVELOPER: Daniel Zaken   TEAM: Blue                      * 
 *                                                                              *
 *  Reviwer:   Peleg Rosenbaum                                                  * 
 *                                                                              *
 *  PURPOSE:   LIB for Malloc and Free                                  		*
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for malloc function*/
#include <stdio.h>
#include "fsa.h"
#include "utl.h"/*Utilities for defines and macros */
/****************************************************************************/
#define MANAGE_SIZE sizeof(fsa_t)
#define HEADER_SIZE sizeof(block_header_t)
#define WORD_SIZE sizeof(size_t)
#define INVALID 0
static size_t GetBlockSize ( size_t block_size );
/* managment structure */

struct fsa
{
	size_t next_free; /*Bytes offset*/
	size_t num_of_blocks; 
	size_t block_size; 	
};
/* memory block structure */
struct block_header
{
	size_t next_free;
};



/****************************************************************************/
fsa_t *FSAInit(void *memory_ptr, size_t total_size, size_t block_size)
{
	char *arr = NULL;
	size_t new_block_size = GetBlockSize( block_size );
	size_t i = 0;
	size_t fix = 0;
	
	assert(memory_ptr);
	
	arr = (char*)memory_ptr;
	fix = ((size_t)WORD_SIZE - (size_t)memory_ptr % (size_t)WORD_SIZE);
	
	if(fix < WORD_SIZE) /*first address to be aligned*/
	{	
		total_size -= fix;
		arr += fix;
	}
	
	if( total_size < new_block_size + MANAGE_SIZE)
	{
		return NULL;
	}
	
	((fsa_t *)arr)->next_free = MANAGE_SIZE ; /*init next_free*/
	((fsa_t *)arr)->num_of_blocks = ( total_size - MANAGE_SIZE ) / new_block_size; /*init num_of_blocks*/
	((fsa_t *)arr)->block_size = new_block_size; /*init block_size*/
	
	while( i < ((fsa_t *)arr)->num_of_blocks - 1 )  
	{
		((block_header_t *)(arr + ( MANAGE_SIZE + i * new_block_size )))-> next_free = MANAGE_SIZE + (i + 1) * new_block_size; 
		++i;
	}
	
	((block_header_t *)(arr + ( MANAGE_SIZE + i * new_block_size )))-> next_free = INVALID; 
	
	
	return (fsa_t *)arr;
}
/****************************************************************************/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return ( MANAGE_SIZE + num_of_blocks * GetBlockSize(block_size) );
}
/****************************************************************************/
void* FSAAlloc(fsa_t *fsa_pool)
{
	char *arr = NULL;
	size_t next_free = 0;
	
	assert(fsa_pool);
	
	if( fsa_pool->next_free == INVALID )
	{
		return NULL;
	}
	
	arr = (char*)fsa_pool; /*mange structure*/
	next_free = (fsa_pool->next_free); 
	fsa_pool->next_free = *(size_t*)((arr + next_free));
	*((size_t*)(arr + next_free)) = next_free;

	return ((void*)(arr + next_free + HEADER_SIZE));
}
/****************************************************************************/
void FSAFree(void *block_to_free)
{
    size_t next_free = 0;
    char * manage = NULL;
    assert(block_to_free);
    
    next_free = ((block_header_t*)((char*)block_to_free - HEADER_SIZE))->next_free;
    manage = (char*)block_to_free - HEADER_SIZE - next_free;
    ((block_header_t *)((char*)block_to_free - HEADER_SIZE))->next_free = ((fsa_t*)manage)->next_free;
    ((fsa_t*)manage)->next_free = next_free;
    
}
/****************************************************************************/

size_t FSACountFree(const fsa_t *fsa_pool)
{
    size_t count = 0;
    size_t next_free = INVALID;
    block_header_t *block_header = NULL;
    assert(fsa_pool);
    
    next_free = fsa_pool->next_free;
    while (next_free != INVALID)
    {
        ++count;
        block_header = (block_header_t *)((char*)fsa_pool + next_free);
        next_free = block_header->next_free;
    }
    return count;
}

/****************************************************************************/
static size_t GetBlockSize ( size_t block_size )
{
	block_size += HEADER_SIZE;
    
    if( block_size % WORD_SIZE )
    {
    	 block_size += WORD_SIZE - ( block_size % WORD_SIZE );
    }
        
    return block_size;
}



