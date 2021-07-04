/********************************************************************************
 *  FILENAME:  circular_buffer.c  DEVELOPER: Daniel Zaken   TEAM: Blue          * 
 *                                                                              *
 *  Reviwer:   ----------                                                       * 
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating circular buffer Data Structure  *
 *                                                                              *
 *******************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "circular_buffer.h"
#include "utl.h"
/*#include <stdeff.h>*/
/****************************************************************************/
typedef char flexible_array_t[1];

struct circular_buffer
{
    size_t size;
    size_t capacity;
    size_t read_from;
    flexible_array_t buffer;
};
/****************************************************************************/
circular_buffer_t *CircularBufferCreate(size_t capacity)
{
	circular_buffer_t *manage = 0;
	
	assert(capacity);
	
	manage = (circular_buffer_t *)malloc( offsetof(circular_buffer_t, buffer) + capacity );
	
	if( manage == NULL )
	{
		return NULL;
	}
	
	manage->capacity = capacity;
	manage->size = 0;
	manage->read_from = 0;
	
	return manage;	
}
/****************************************************************************/
void CircularBufferDestroy(circular_buffer_t *buffer)
{
	assert(buffer);
	free(buffer);
}
/****************************************************************************/
ssize_t CircularBufferWrite( circular_buffer_t *buffer, const void *src, size_t count)
{
	ssize_t res = 0;
	int w1 = 0;
	int w2 = 0;
	const char *ptr = NULL;
	
	assert(buffer);
	assert(src);
	
	ptr = src;
	
	count = MIN(count, CircularBufferFreeSpace(buffer) );
	w1 = MIN(count, buffer->capacity - ( buffer->read_from + buffer->size ));
	w2 = count - w1;
	
	memcpy(buffer->buffer + ((buffer->size + buffer->read_from) % buffer->capacity) , ptr, w1);
	res += w1;
	buffer->size += w1;
	
	if ( w2 == 0 )return res;
	
	memcpy(buffer->buffer , ptr + w1, w2);
	res += w2;
	buffer->size += w2;
	
	return res;	
}
/****************************************************************************/
ssize_t CircularBufferRead( circular_buffer_t *buffer, void *dest, size_t count)
{    
	int r1 = 0;
	int r2 = 0;
    ssize_t res = 0;
    assert(dest);
    assert(buffer);   
    
	count = MIN(count, buffer->size);
	r1 =MIN( (buffer->capacity - buffer->read_from), count);
	r2 = count - r1;
	
	memcpy((char*)dest, buffer->buffer + buffer->read_from, r1);
	res += r1;
	buffer->size -= r1;
	
	if ( r2 == 0 )
	{
		buffer->read_from = ( buffer->read_from + r1 ) % buffer->capacity;
		return res;
	}
	
	memcpy( (char*)dest + r1 , buffer->buffer,r2 );
	res += r2;
	buffer->size -= r2;
	
	buffer->read_from = ( buffer->read_from + r1 + r2 ) % buffer->capacity;
	return res;
}

/****************************************************************************/
size_t CircularBufferBuffSiz( const circular_buffer_t *buffer)
{	
	assert(buffer);
	return buffer->capacity;
}
/****************************************************************************/
int  CircularBufferIsEmpty(const circular_buffer_t *buffer)
{
	assert(buffer);
	return ( !buffer->size );
}
/****************************************************************************/
size_t CircularBufferFreeSpace(const circular_buffer_t *buffer)
{
	assert(buffer);
	return( buffer->capacity - buffer->size );
}

