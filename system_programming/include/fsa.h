/********************************************************************************
 *  FILENAME:  fsa.h  DEVELOPER: Daniel Zaken   TEAM: Blue                      * 
 *                                                                              *
 *  Reviwer:   Peleg Rosenbaum                                                  * 
 *                                                                              *
 *  PURPOSE:   LIB for Malloc and Free                                  		*
 *                                                                              *
 *******************************************************************************/
#ifndef __FIXED_SIZE_ALLOCATOR_H__
#define __FIXED_SIZE_ALLOCATOR_H__


typedef struct fsa fsa_t;
typedef struct block_header block_header_t;



/****************************************************************************/
/*
Description: Creates a new FSA according given memory block size
Parameters: 

				memory_ptr -> address of memory chunk to be manged.
				total_size -> The total size of the given chunck to be managed.
				block_size -> The requested block size.

Return Value: Returns a Word Aliigned pointer to the Memory manager, an invalid memory address 
Time Complexity: O(n)
*/
fsa_t* FSAInit(void* memory_ptr, size_t total_size, size_t block_size);

/****************************************************************************/
/*
Description: Suggest a size for the fsa according to required amount of blocks and block size
Parameters: 

				num_of_blocks -> block number
				block_size -> block size

Return Value: Returns a calculated number of the chuck size needed according to the
			  block number and the block size.
Time Complexity: O(1)
*/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);

/****************************************************************************/
/*
Description: Allocate a block and return a pointer to it
Parameters: 

				fsa_pool -> Address of the fsa manager given in FSAInit function 

Return Value: Returns the address of the block allocated
Time Complexity: O(1)
*/
void* FSAAlloc(fsa_t* fsa_pool);
/****************************************************************************/
/*
Description: Free an allocated block
Parameters: 

				block_to_free -> A pointer the block which designated to be free

Return Value: void
Time Complexity: O(1)
*/
void FSAFree(void* block_to_free);

/****************************************************************************/
/*
Description: Return amount of free blocks in the FSA
Parameters: 

				pointer -> Address of the fsa manager given in FSAInit function 

Return Value: Number of free blocks existing 
Time Complexity: O(n)
*/
size_t FSACountFree(const fsa_t* pointer);


#endif
