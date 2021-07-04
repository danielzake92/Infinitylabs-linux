/****************************************************************************
* FILE: avl.h		Purpose: library for avl data structure
*
* DEVELOPER:						TEAM:
*
* REVIEWER: 						STATUS: In Development
*
****************************************************************************/

#ifndef __ILRD_AVL_H__
#define __ILRD_AVL_H__

/****************************************************************************/

#include <stddef.h> /*size_t*/

/****************************************************************************/
/**********************************************SOURCE FILE***********************/


/*****************************************************************************/

typedef enum traverse
{
	IN_ORDER = 0,
	PRE_ORDER = 1,
	POST_ORDER = 2
}traverse_t;

typedef struct avl avl_t;

typedef int(*avl_compare_func_t)(const void *lhs, const void *rhs);

typedef int(*avl_operation_func_t)(void *target, void *parameters);

/****************************************************************************/

/*
Description: Creates new empty AVL. and stores compare_func.
Parameters:
Return Value:	
Time Complexity:
*/

avl_t *AVLCreate(avl_compare_func_t compare_func);

/****************************************************************************/

/*
Description: Destroys existing AVL, freeing all associated allocated memory,
but not deallocating memory of data stored within AVL.
Parameters:
Return Value:
Time Complexity:
*/
void AVLDestroy(avl_t *tree);

/****************************************************************************/

/*
Description: inserting Unique Key to the correct location if the key already 
exist , it will not be stored. keep tree balanced.
Parameters:
Return Value: SUCCESS / FAIL for allocation. if data already exist return success (0).
Time Complexity: 
*/

int AVLInsert(avl_t *tree, void *data);

/****************************************************************************/

/*
Description: Removes unique Key . Keep tree balanced.
Parameters:
Return Value: 
Time Complexity:
*/

void AVLRemove(avl_t *tree, void *data); 

/****************************************************************************/

/*
Description: traverse tree search for key .if found returns the Key , otherwise
returns NULL. 
Parameters:
Return Value: 
Time Complexity: 
*/

const void *AVLFind(const avl_t *tree, const void *data);

/****************************************************************************/

/*
Description: returns the amount of elements in tree.
Parameters:
Return Value:	
Time Complexity:
*/

size_t AVLCount(const avl_t *tree);

/****************************************************************************/

/*
Description: returns 1 IF AVL IS EMPTY otherwise 0.
Parameters:
Return Value: 
Time Complexity:
*/

int AVLIsEmpty(const avl_t *tree);

/****************************************************************************/

/*
Description: Applies callback function to each data held in tree element in 
requested order, AVLForEach will also stop if callback function returns a non-zero value.
Parameters:
Return Value: 
Time Complexity: 
*/

int AVLForEach(avl_t *tree, avl_operation_func_t callback, 
							void *parameters, traverse_t traverse);

/****************************************************************************/
/*
Description: returns the tree height.
Parameters:
Return Value: 
Time Complexity:
*/

int AVLHeight(const avl_t *tree);

/****************************************************************************/
#endif

