/********************************************************************************
 *  FILENAME:  fsa.h  DEVELOPER: Daniel Zaken   TEAM: Blue                      *
 *                                                                              *
 *  Reviwer:   Kim Aharfi                                                       *
 *                                                                              *
 *  PURPOSE:   LIB for Malloc and Free                                  		*
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for malloc function*/
#include "vsa.h"/*Our variadic allocation lib*/
#include "utl.h"/*Utilities for defines and macros */
/****************************************************************************/
#define HEADER_SIZE sizeof(block_header_t)
#define WORD sizeof(size_t)
#define INVALID 0

#define MAGIC_NUMBER 0x90909090
#define END 0xffffffff

typedef struct block_header
{
	ssize_t allocated_size;
#ifndef NDEBUG /*only for debug version*/
	size_t magic_number;
#endif
}block_header_t;


static size_t GetNegetiveSpace(block_header_t *header);
static void HeaderUpdate(block_header_t *header, ssize_t allocated_size, size_t magic_number);

/****************************************************************************/
vsa_t *VSAInit(void *memory_ptr, size_t total_size)
{
	block_header_t *first_header = NULL, *last_header = NULL;
	assert(memory_ptr);

	total_size -= total_size % WORD;

	if(total_size < (2 * HEADER_SIZE + WORD))
    {
        return NULL;
    }

	first_header = (block_header_t*)memory_ptr;
	HeaderUpdate(first_header, (-1)*(total_size - 2 * HEADER_SIZE),MAGIC_NUMBER);

	last_header = (block_header_t*)((char*)memory_ptr + total_size - HEADER_SIZE );
	HeaderUpdate(last_header, END,MAGIC_NUMBER);

	return memory_ptr;
}
/****************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t num_bytes)
{
	long free_space = 0;
	long new_val = 0;
	block_header_t *header = NULL;
	block_header_t *new_header = NULL;

	assert(vsa);
	header = vsa;

	if( num_bytes % WORD )
	{
		num_bytes += ( WORD - (num_bytes % WORD) );
	}

	free_space = header->allocated_size;


	while( END != free_space )
	{
		if( 0 > free_space )
		{
			free_space = GetNegetiveSpace(header);

			if( free_space >= (long)(num_bytes + HEADER_SIZE) )
			{
				new_header = (block_header_t*)( (char*)header + HEADER_SIZE + num_bytes );
				new_val = free_space - HEADER_SIZE - num_bytes;

				HeaderUpdate(new_header,(-1)*new_val , MAGIC_NUMBER);

				HeaderUpdate(header, num_bytes, MAGIC_NUMBER);

				return ( (vsa_t *)((char*)header + HEADER_SIZE) );
			}
		}

		header = (block_header_t*)((char*)header + free_space + HEADER_SIZE);
		free_space = header->allocated_size;
	}

	return NULL;
}
/****************************************************************************/
void VSAFree(void *block)
{
	block_header_t *header = NULL;

	assert(block);

	header = (block_header_t*)((char*)block - HEADER_SIZE);

	#ifndef NDEBUG
		assert(header->magic_number == MAGIC_NUMBER);
	#endif

	header->allocated_size *= (-1);
}
/****************************************************************************/
size_t VSALargestChunkAvailable(vsa_t *vsa)
{
	block_header_t * header = NULL;
	long free_space = 0;
	long max_count = 0;

	assert(vsa);

	header = vsa;
	free_space = header->allocated_size;

	while( END != free_space )
	{
		if( 0 > free_space )
		{
			free_space = GetNegetiveSpace(header);
			HeaderUpdate(header, (-1) * free_space, MAGIC_NUMBER); /*fragmentation*/
			max_count = MAX(max_count, free_space);
		}
		header = (block_header_t*)((char*)header + free_space + HEADER_SIZE);
		free_space = header->allocated_size;
	}
	return max_count;	
}
/****************************************************************************/
static void HeaderUpdate(block_header_t *header, ssize_t allocated_size, size_t magic_number)
{
	header->allocated_size = allocated_size;
	(void)magic_number;
	#ifndef NDEBUG
		header->magic_number = magic_number;
	#endif
}
/****************************************************************************/
static size_t GetNegetiveSpace(block_header_t *header)
{
	block_header_t *start = NULL;
	long header_val = 0;
	size_t counter = 0;
	assert(header);

	start = header;

	header_val = header->allocated_size;

	while( header_val < 0 && END != header_val )
	{
		header_val *= -1;
		counter += (header_val + HEADER_SIZE);
		header = (block_header_t*)((char*)header + header_val + HEADER_SIZE);
		header_val = header->allocated_size;
	}

	start->allocated_size = - (counter - HEADER_SIZE);

	return counter - HEADER_SIZE;
}
