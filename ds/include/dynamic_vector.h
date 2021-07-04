/********************************************************************************
 *  FILENAME:  vector.c  DEVELOPER: Daniel Zaken  TEAM: Blue                    * 
 *                                                                              *
 *  REVIEWER: --------                                                          * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating DynamicVector                        *
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_DYNAMIC_VECTOR_H__
#define __ILRD_DYNAMIC_VECTOR_H__
/****************************************************************************/
#include <stddef.h> /*required for size_t type*/

/*************************************************************************************************************/


/* Dynamic Vector type definition */
typedef struct vector dynamic_vector_t;


/*************************************************************************************************************/
/*
Description: Create new dynamic vector
Parameters: 
	-size_t capacity: number of elements to be held in new dynamic vector
Return Value: dynamic vector data structure
Time Complexity: O(1)
*/
dynamic_vector_t *DynamicVectorCreate( size_t capacity );


/*************************************************************************************************************/
/*
Description: Destroy Existing Dynamic Vector object
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
Return Value: N/A
Time Complexity: O(1)
*/
void DynamicVectorDestroy( dynamic_vector_t *vector );

/*************************************************************************************************************/
/*
Description: Set value in dynamic vector as specified position
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
	-size_t position: position of array element to be set, position must be smaller than size of dynamic vector. Otherwise behavior is undefined.
	-void *value: value to be places in given position
Return Value: N/A
Time Complexity: O(1)
*/
void DynamicVectorSetAt( dynamic_vector_t *vector, size_t position, void *value );


/*************************************************************************************************************/
/*
Description: Return value stored in dynamic vector at specified position
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
	-size_t position: position of element to be returned
Return Value: value found at given position of array
Time Complexity: O(1)
*/
void *DynamicVectorGetAt( const dynamic_vector_t *vector , size_t position);


/*************************************************************************************************************/
/*
Description: add value to the end of dynamic vector
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
	-void *value: value to pushed to the top of the array
Return Value: int value indicating 1 for success and 0 for failure
Time Complexity: Amortized O(1)
*/
int DynamicVectorPushBack( dynamic_vector_t *vector, void *value );

/*************************************************************************************************************/
/*
Description: return value at end of dynamic vector and remove it from dynamic vector.
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
Return Value: int value indicating 1 for success and 0 for failure
Time Complexity: O(1)
*/
int DynamicVectorPopBack( dynamic_vector_t *vector ); 

/*************************************************************************************************************/

/*
Description: Reserve specified number of places in dynamic vector
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
	-size_t size: the total new capacity of the vector
Return Value: int value indicating 1 for success and 0 for failure
Time Complexity: O(n)
*/
int DynamicVectorReserve( dynamic_vector_t *vector, size_t new_capacity ); 

/*************************************************************************************************************/

/*
Description: Shrink Dynamic Vector so that capacity is equal to size
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
Return Value: int value indicating 1 for success and 0 for failure
Time Complexity: O(1)
*/
int DynamicVectorShrinkToFit( dynamic_vector_t *vector ); 

/*************************************************************************************************************/

/*
Description: return size of dynamic vector stored elements
Parameters: 
	-const dynamic_vector_t *vector: dynamic vector data structure
Return Value: number of occupied elements in dynamic vector
Time Complexity: O(1)
*/
size_t DynamicVectorGetSize( const dynamic_vector_t *vector ); 

/*************************************************************************************************************/
/*
Description: returns the capacity of dynamic vector
Parameters: 
	-const dynamic_vector_t *vector: dynamic vector data structure
Return Value:  total current capacity of dynamic vector
Time Complexity: O(1)
*/
size_t DynamicVectorGetCapacity( const dynamic_vector_t *vector ); 

/*************************************************************************************************************/
/*
Description: Sets all values within capacity of dynamic vector to specified value.
Parameters: 
	-dynamic_vector_t *vector: dynamic vector data structure
	-void *value: value to be copied to all currently occupied elements in vector
Return Value: 
Time Complexity: O(n)
*/
void DynamicVectorSetAll( dynamic_vector_t *vector , void *value); /*optional*/
/*************************************************************************************************************/


#endif
