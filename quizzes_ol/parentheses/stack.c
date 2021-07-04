/********************************************************************************
 *  FILENAME:  stack.h  DEVELOPER: Daniel Zaken  TEAM: Blue                     * 
 *                                                                              *
 *  REVIEWER:  Or Katz                                                          * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating stack                                *
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include "stack.h"
/*******************************************************************************/
struct stack/* typedef for Stack data structure */
{
	void **array;		/* stack data */
	size_t size;        /* number of elements currently in stack */
	size_t capacity;    /* number of elements that stack can hold */
};
/*******************************************************************************/
stack_t *StackCreate( size_t capacity )
{
	stack_t *ptr = (stack_t*)malloc( sizeof(stack_t) );/*adding if for not succecing allocationg then return null*/  
	
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
/*******************************************************************************/
void StackDestroy( stack_t *stack )
{
	assert(stack);
	free(stack->array);
	stack->array = NULL;
	free(stack);
}
/*******************************************************************************/
void StackPush( stack_t *stack, void *value)
{
	assert(stack);
	assert(!StackIsFull(stack) ); 
	*(stack->array + stack->size) = value; 
	++(stack->size);
}
/*******************************************************************************/
void StackPop( stack_t *stack)
{
	assert(!StackIsEmpty(stack) ); 
	assert(stack);
	--(stack->size);
}
/*******************************************************************************/
int StackIsEmpty( const stack_t *stack )
{
	assert(stack);
	return ( !(stack->size) ); 
}
/*******************************************************************************/
int StackIsFull(const stack_t *stack)
{
	assert(stack);
	return ( stack->size == stack->capacity );
}
/*******************************************************************************/
size_t StackCapacity(const stack_t *stack )
{
	assert(stack);
    return stack->capacity;
}
/*******************************************************************************/
size_t StackSize(const  stack_t *stack )
{
	assert(stack);
    return stack->size;
}
/*******************************************************************************/
void *StackPeek(const stack_t *stack )
{	
	assert(!StackIsEmpty(stack) );
	assert(stack);
	return( *(stack->array + stack->size - 1) );
}
