/********************************************************************************
 *  FILENAME:  vsa.h  DEVELOPER: Daniel Zaken   TEAM: Blue                      * 
 *                                                                              *
 *  Reviwer:   Kim Aharfi                                                       * 
 *                                                                              *
 *  PURPOSE:   LIB for Malloc and Free                                  		*
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_VARIABLE_SIZE_ALLOCATOR_H__
#define __ILRD_VARIABLE_SIZE_ALLOCATOR_H__
#include <stddef.h> /* For size_t. */
#include <sys/types.h> /* For ssize_t. */

typedef void vsa_t;


/****************************************************************************/
/*
Description: Initializes the vsa to the memory_ptr address, memory_ptr should
			be aligned.
Parameters: memory_ptr - Segment ptr
			total_size - Total segment size
Return Value: segment ptr after initialize  
Time Complexity: O(1)
*/
vsa_t *VSAInit(void *memory_ptr, size_t total_size);
/****************************************************************************/
/*
Description: Allocate a block of size num_bytes and return a pointer to it.
Parameters: vsa - ptr for the segemnt start
			num_bytes - size of alloction desired
Return Value: ptr for memory block
Time Complexity: O(n)
*/
void *VSAAlloc(vsa_t *vsa, size_t num_bytes);
/****************************************************************************/
/*
Description: Free an allocated block.
Parameters: block - memory block to be freed ptr
Return Value: None.
Time Complexity: O(1)
*/
void VSAFree(void *block);
/****************************************************************************/
/*
Description: Returns the largest contiguous block of free memory.
Parameters: vsa - 
Return Value:  Returns the largest contiguous block of free memory.
Time Complexity: O(n)
*/
size_t VSALargestChunkAvailable(vsa_t *vsa);

#endif
