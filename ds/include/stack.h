/********************************************************************************
 *  FILENAME:  stack.h  DEVELOPER: Daniel Zaken  TEAM: Blue                     *
 *                                                                              *
 *  REVIEWER:  Or Katz                                                          *
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating stack                                *
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_STACK_H__
#define __ILRD_STACK_H__
/****************************************************************************/
#include <stddef.h> /*required for size_t type*/

/*************************************************************************************************************/

typedef struct stack stack_t;


/*************************************************************************************************************/
/*
Description    : Creates new stack by allocating space according to capacity given
Parameters     : capacity - size of the stack
Return Value   : Pointer to the stack base
Time Complexity: o(1)
*/
stack_t *StackCreate( size_t capacity ); 

/*************************************************************************************************************/
/*
Description    : Destroys stack
Parameters     : stack - pointer of the stack base
Time Complexity: o(1)
*/
void StackDestroy( stack_t *stack );
/*************************************************************************************************************/

/*
Description    : Pushes new element to stack
Parameters     : stack - pointer of the stack base
		         value - value to push into the stack
Time Complexity: o(1)
*/

void StackPush( stack_t *stack, void *value);
/*************************************************************************************************************/

/*
Description    : Removes element from top of stack
Parameters     : stack - pointer of the stack base
Time Complexity: o(1)
*/
void StackPop( stack_t *stack);

/*************************************************************************************************************/

/*
Description: indicates whether the stack is empty with logical value
Parameters     : stack - pointer of the stack base
Return Value   : for empty (1) not empty (0)
Time Complexity: o(1)
*/
int StackIsEmpty( const stack_t *stack );

/*************************************************************************************************************/

/*
Description: indicates whether the stack is full with logical value
Parameters     : stack - pointer of the stack base
Return Value   : for full (1) not full (0)
Time Complexity: o(1)
*/
int StackIsFull(const stack_t *stack);

/*************************************************************************************************************/

/*
Description: Returns total number of elements the stack can hold
Parameters     : stack - pointer of the stack base
Return Value   : returns the total number the stack capacity
Time Complexity: o(1)
*/
size_t StackCapacity(const stack_t *stack );

/*************************************************************************************************************/

/*
Description: Returns number of elements currently in stack
Parameters     : stack - pointer of the stack base
Return Value   : returns the total number of element exist in the current stack
Time Complexity: o(1)
*/
size_t StackSize(const  stack_t *stack );

/*************************************************************************************************************/

/*
Description: Returns number of elements currently in stack
Parameters     : stack - pointer of the stack base
Return Value   : returns a the data which is on top of the stack
Time Complexity:
*/
void *StackPeek(const stack_t *stack );

/*************************************************************************************************************/

#endif
