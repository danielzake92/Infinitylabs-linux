/********************************************************************************
 *  FILENAME:  vector.c  DEVELOPER: Daniel Zaken  TEAM: Blue                    * 
 *                                                                              *
 *  REVIEWER: --------                                                          * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating DynamicVector                        *
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include "dynamic_vector.h"/*Lib header*/
#define SUCCESS 0
#define FAILURE 1
#define ENLARGE 2
/******************************************************************************/
struct vector
{
	void **array;
	size_t capacity; 
	size_t size; /* size of total block of elements in which data is stored, not number 
		  		    of elements which have been assigned a value */
};
/******************************************************************************/
dynamic_vector_t *DynamicVectorCreate( size_t capacity )
{
		
	dynamic_vector_t *ptr = (dynamic_vector_t*)malloc( sizeof(dynamic_vector_t) );
	if ( !ptr )return NULL; 
		
	ptr->array = (void**)malloc(capacity * sizeof(void*) );	
	
	if ( !ptr->array ) 
	{	
		free(ptr);
		return NULL;
	}
	
	ptr->size = 0;
	ptr->capacity = capacity;
	return ptr;		
}
/******************************************************************************/
void DynamicVectorDestroy( dynamic_vector_t *vector )
{
	assert(vector);
	assert(vector->array);
	free(vector->array);
	vector->array = NULL;
	free(vector);
}
/******************************************************************************/
void DynamicVectorSetAt( dynamic_vector_t *vector, size_t position, void *value )
{
	assert(vector);
	assert(vector->array);
	(vector->array)[position] = value;
}
/******************************************************************************/
void *DynamicVectorGetAt( const dynamic_vector_t *vector , size_t position)
{
	assert(vector);
	assert(vector->array);

	if( 0 == DynamicVectorGetSize (vector))
	{
		return NULL;
	}

	return *(vector->array + position);
}
/******************************************************************************/
int DynamicVectorPushBack( dynamic_vector_t *vector, void *value )
{
	assert(vector);
	
	if( vector->size == vector->capacity )
	{
		if (FAILURE == DynamicVectorReserve( vector, vector->capacity * ENLARGE))
		{
			return FAILURE;
		}
	}
		
	(vector->array)[vector->size] = value;
	++vector->size;
	
	return SUCCESS;
}
/******************************************************************************/
int DynamicVectorPopBack( dynamic_vector_t *vector )
{
	assert(vector);
	
	if(vector->size == 0)
	{
		return FAILURE;
	}
	
	--(vector->size);

	return SUCCESS;
}
/******************************************************************************/
int DynamicVectorReserve( dynamic_vector_t *vector, size_t new_capacity )
{
    assert(vector);
    assert(vector->array);
    if((vector->array = (void**)realloc(vector->array,new_capacity * sizeof(void*))) != NULL) 
    {
        vector->capacity = new_capacity;
        return SUCCESS;
    }
    if( vector->size < new_capacity )
    {
    	vector->size = new_capacity;
    }
    return FAILURE;
}
/******************************************************************************/
int DynamicVectorShrinkToFit( dynamic_vector_t *vector )
{
	assert(vector);
	return( DynamicVectorReserve(vector, vector->size ) );
}
/******************************************************************************/
size_t DynamicVectorGetSize( const dynamic_vector_t *vector ) 
{
	assert(vector);
    return vector->size;
}
/*******************************************************************************/
size_t DynamicVectorGetCapacity( const dynamic_vector_t *vector )
{
	assert(vector);
    return vector->capacity;
}
/*******************************************************************************/
void DynamicVectorSetAll( dynamic_vector_t *vector , void *value)
{
	size_t i = 0;
	assert(vector);
	
	while(i < vector->capacity)
	{
		(vector->array)[i] = value;
		++i;
	}
}
/******************************************************************************/


