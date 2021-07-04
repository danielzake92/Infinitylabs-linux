/********************************************************************************
 *  FILENAME:  circular_buffer.c  DEVELOPER: Daniel Zaken   TEAM: Blue          * 
 *                                                                              *
 *  Reviwer:   ----------                                                       * 
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating circular buffer Data Structure  *
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_CIRCULAR_BUFFER_H__
#define __ILRD_CIRCULAR_BUFFER_H__
/****************************************************************************/
#include <stddef.h> /*required for ssize_t type*/
#include <sys/types.h>  /* ssize_t */

/****************************************************************************/


/**************** move struct to source  + typedef of flexible array*********************/



/**************** move struct to source  + typedef of flexible array*********************/


typedef struct circular_buffer circular_buffer_t;

/****************************************************************************/
/*
Description: create new buffer
Parameters: 
	-capacity: capacity new buffer is to have, must be at lease 1
Return Value: pointer to new buffer data structure
Time Complexity: O(1)
*/
circular_buffer_t *CircularBufferCreate(size_t capacity);

/****************************************************************************/
/*
Description: destroy buffer
Parameters: 
	-buffer: circular buffer data structure
Return Value: None
Time Complexity: O(1)
*/
void CircularBufferDestroy(circular_buffer_t *buffer); 

/****************************************************************************/
/*
Description: write to buffer without overwriting
Parameters: 
	-buffer: circular buffer data structure
	-src: source from which data is written to buffer
	-count: maximum number of bytes to be writtem. If there are less open spaces in buffer than input count then will only write the number of available bytes. Count cannot be larger than the size of the buffer.
Return Value: number of bytes written or, in case of failure, 0.
Time Complexity: O(count)
*/
ssize_t CircularBufferWrite( circular_buffer_t *buffer, const void *src, size_t count);

/****************************************************************************/
/*
Description: read from buffer (limit to buffer size)
Parameters: 
	-buffer: circular buffer data structure
	-dest: destination to which data is to be read from buffer
	-count: maximum number of bytes to be read. If there are less elements in buffer than input count, then will only read the number of available bytes. Count cannot be larger than the size of the buffer.
Return Value: number of bytes read from buffer or, upon failure, 0
Time Complexity: O(count)
*/
ssize_t CircularBufferRead( circular_buffer_t *buffer, void *dest, size_t count);

/****************************************************************************/
/*
Description: Gives the size of the buffer
Parameters: 
	-buffer: circular buffer data structure
Return Value: size of the input buffer
Time Complexity: O(1)
*/
size_t CircularBufferBuffSiz( const circular_buffer_t *buffer);

/****************************************************************************/
/*
Description: Checks if the buffer is empty
Parameters: 
	-buffer: circular buffer data structure
Return Value: returns 1 if the buffer is empty, and otherwise 0.
Time Complexity: O(1)
*/
int  CircularBufferIsEmpty(const circular_buffer_t *buffer);

/****************************************************************************/
/*
Description: Determines the amount of free space left in the buffer
Parameters: 
	-buffer: circular buffer data structure
Return Value: returns the number of free bytes in the buffer.
Time Complexity: O(1)
*/
size_t CircularBufferFreeSpace(const circular_buffer_t *buffer);

#endif
