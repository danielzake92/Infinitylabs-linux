/****************************************************************************
* FILE: bst.h  Purpose: library for bst data structure
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Roger Farber				STATUS: Sent for review
*
****************************************************************************/

#ifndef __ILRD_BST_H__
#define __ILRD_BST_H__

/****************************************************************************/

#include <stddef.h> /*size_t*/

/****************************************************************************/

typedef enum
{
	FALSE = 0,
	TRUE = 1
}boolean_t;

enum result
{
	SUCCESS = 0,
	FAILURE = 1
};

typedef void *bst_iterator_t;

typedef struct bst bst_t;

typedef int(*bst_compare_func_t)(const void *lhs, const void *rhs);

typedef int(*bst_operation_func_t)(void *target, void *parameters);

/****************************************************************************/

/*
Description: Creates new empty BST, which will organize data within it based on input comparison function.
Parameters:
	-compare_func: comparison function by which data is organized within BST.
Return Value:	pointer to new BST.
Time Complexity: O(1)
*/

bst_t *BSTCreate(bst_compare_func_t compare_func);

/****************************************************************************/

/*
Description: Destroys existing BST, freeing all associated allocated memory, but not deallocating memory of data stored within BST.
Parameters:
	-tree: BST to be destroyed.
Return Value:	NONE
Time Complexity: O(n*log(n))
*/
void BSTDestroy(bst_t *tree);

/****************************************************************************/

/*
Description: Returns beginning iterator in BST, which is the leftmost leaf in BST.
Parameters:
	-tree: BST data structue.
Return Value: Beggining(leftmost) iterator of input tree.
Time Complexity: O(log(n))
*/

bst_iterator_t BSTBegin(const bst_t *tree);

/****************************************************************************/

/*
Description: Returns end iterator which is invalid, this iterator will be returned in case of failure in a function that returns an iterator.
However, the previous iterator to the one returned by this function is the rightmost leaf in BST.
Parameters:
	-tree: BST data structure.
Return Value: invalid iterator
Time Complexity: O(1)
*/

bst_iterator_t BSTEnd(const bst_t *tree);

/****************************************************************************/

/*
Description: Inserts data into tree accoring to comparison function.
Insertion of data which already is held by tree will cause function to return invalid iterator which is also returned by BSTEnd function.
Parameters:
	-tree: BST data structure
	-data: data to be inserted into tree
Return Value: Returns iterator of inserted data, upon failure will return invalid iterator which is also returned by BSTEnd
Time Complexity: O(log(n))
*/

bst_iterator_t BSTInsert(bst_t *tree, void *data);

/****************************************************************************/

/*
Description: Removes iterator from its respective tree. After removal, inputting iterator to other BST function will lead to undefined behavior.
Parameters:
	-target: iterator to be removed
Return Value: NONE
Time Complexity: O(log(n))
*/

void BSTRemove(bst_iterator_t target);

/****************************************************************************/

/*
Description: Finds iterator associated with the input data, if not found will return invalid iterator.
Parameters:
	-tree: BST data structure
	-data: data to be found in BST
Return Value: returns iterator of input dat, if Find does not succeed will return end node which can be found using BSTEnd
Time Complexity: O(log(n))
*/

bst_iterator_t BSTFind(const bst_t *tree, void *data);

/****************************************************************************/

/*
Description: Returns the size of the input BST.
Parameters:
	-tree: BST data structure
Return Value:	size of input BST
Time Complexity: O(n)
*/

size_t BSTSize(const bst_t *tree);

/****************************************************************************/

/*
Description: Determines whether input tree is empty.
Parameters:
	-tree: BST data structure
Return Value: Returns (1) if empty and (0) otherwise
Time Complexity: O(1)
*/

boolean_t BSTIsEmpty(const bst_t *tree);

/****************************************************************************/

/*
Description: Determines whether two iterators are equal.
Parameters:
	-one: first input iterator
	-other: second input iterator
Return Value: Returns (1) if iterators are equal and (0) otherwise
Time Complexity: O(1)
*/

boolean_t BSTIsEqualIterator(const bst_iterator_t one, const bst_iterator_t other);

/****************************************************************************/

/*
Description: returns previous iterator to input iterator as determined by comparison function of associated tree.
Input of beginning iterator will cause function to return invalid iterator.
Input of end iterator will return rightmost leaf of BST.
Parameters:
	-target: iterator from which previous iterator is to be determined.
Return Value: previous iterator to input iterator
Time Complexity: O(log(n))
*/

bst_iterator_t BSTPrev(const bst_iterator_t target);

/****************************************************************************/

/*
Description: returns next iterator to input iterator as determined by comparison function of associated tree.
input of end iterator will cause function to return invalid iterator.
Parameters:
	-target: iterator from which next iterator is to be determined.
Return Value: next iterator to input iterator
Time Complexity: O(log(n))
*/

bst_iterator_t BSTNext(const bst_iterator_t target);

/****************************************************************************/

/*
Description: Applies callback function to each data held in iterators in range [from,to),
that is beggining at and including iterator from, and ending at but not including iterator to.
BSTForEach will also stop before iterator to if callback function returns a non-zero value.
Parameters:
	-from: iterator at which calls to callback function begin, callback is applied to from's data.
	-to: iterator before which application of callback function ends.
	-callback: Pointer to function to be applied to data associated with iterators as described in description.
	-parameters: parameters which are supplied to callback function as second argument during each call.
Return Value: Value returned by callback function during its final call before BSTForEach ends.
Time Complexity: O(n)
*/

int BSTForEach(bst_iterator_t from, bst_iterator_t to, bst_operation_func_t callback, void *parameters);

/****************************************************************************/

/*
Description: Retuns the data associated with target iterator.
Parameters:
	-target: iterator whose associated data is to be returned.
Return Value: data associated with input iterator.
Time Complexity: O(1)
*/

void *BSTGetData(const bst_iterator_t target);

int IsPerfect(bst_t *root);
/****************************************************************************/



#endif
