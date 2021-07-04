/********************************************************************************
 *  FILENAME: singly_linked_list.h  DEVELOPER: Daniel Zaken  TEAM: Blue         * 
 *                                                                              *
 *  REVIEWER: --------                                                          * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating DynamicVector Singly Linked List     *
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_SINGLY_LINKED_LIST_H__
#define __ILRD_SINGLY_LINKED_LIST_H__
/****************************************************************************/
#include <stddef.h> /*required for size_t type*/

typedef struct sll_node *sll_iterator_t; /*iterator*/

typedef struct sll sll_t; /*manage list*/
/****************************************************************************/

/* Function used to find a specific iterator, returns a 0 value int if data is not a match and a non-zero int value if it is.  */
typedef int(*match_func_t)(const void *data, void *parameter ); 

/****************************************************************************/

/* Operation function applied to each value held in list according to range supplied to SinglyLinkedListForEach function. Operation function returns 0 if application of operation is to continue to the next value in the list, and a non-zero value otherwise. */
typedef int(*operation_func_t)(void *data,void *parameter); 

/****************************************************************************/
/*
Description: Creates new list
Parameters: None
Return Value: pointer to new list
Time Complexity: O(1)
*/
sll_t *SinglyLinkedListCreate(void);
/****************************************************************************/
/*
Description: Destroys input list
Parameters:
	-sll_t *list: pointer to list to be destroyed
Return Value: none
Time Complexity: O(n)
*/
void SinglyLinkedListDestroy(sll_t *list);
/****************************************************************************/
/*
Description: Returns first iterator in list
Parameters: 
	-const sll_t *list: pointer to list
Return Value: first iterator in list
Time Complexity: O(1)
*/
sll_iterator_t SinglyLinkedListBegin(const sll_t *list);
/****************************************************************************/
/*
Description: Returns last iterator in list
Parameters: 
	-const sll_t *list: pointer to list
Return Value: last iterator in list
Time Complexity: O(1)
*/
sll_iterator_t SinglyLinkedListEnd(const sll_t *list);
/****************************************************************************/
/*
Description: inserts a new iterator with given data into list before the input iterator
Parameters: 
	-sll_iterator_t iterator: iterator before which the new iterator will be inserted
	-void *data: data to be inserted in new iterator
Return Value: iterator which has been added
Time Complexity: O(1)
*/
sll_iterator_t SinglyLinkedListInsert(sll_iterator_t iterator, void *data);
/****************************************************************************/
/*
Description: removes the specified iterator and returns the next
Parameters: 
	-sll_iterator_t iterator: iterator to be removed from list
Return Value: next iterator in list after the one removed
Time Complexity: O(1)
*/
sll_iterator_t SinglyLinkedListRemove( sll_iterator_t iterator);
/****************************************************************************/
/*
Description: finds the first iterator in the range of from to to for which the given match function returns a non-zero value
Parameters: 
	-match_func_t match_func: function which compares data within the list and returns a non-zero value only if the values are a match. compares using parameter passed as other argument to this function.
	-sll_iterator_t from: iterator from which to begin the search
	-sll_iterator_t to: iterator at which the search ends, does not check the value of to iterator.
	-void *parameter: parameter against which data in the list is compared using match function.
Return Value: iterator at which the match function declares there is a match.
Time Complexity: O(n)
*/
sll_iterator_t SinglyLinkedListFind(match_func_t match_func, sll_iterator_t from,sll_iterator_t to,void *parameter);
/****************************************************************************/
/*
Description: returns the next iterator from the one input
Parameters: 
	-const sll_iterator_t iterator: iterator from which the next iterator is selected.
Return Value: next iterator after the one input
Time Complexity: O(1)
*/
sll_iterator_t SinglyLinkedListNext(const sll_iterator_t iterator);
/****************************************************************************/
/*
Description: returns the data value in the input iterator
Parameters: 
	-const sll_iterator_t iterator: iterator structure from which data is taken
Return Value: data value stored in iterator
Time Complexity: O(1)
*/
void *SinglyLinkedListGetData(const sll_iterator_t iterator);
/****************************************************************************/
/*
Description: Sets the specified value to be held by the given iterator
Parameters: 
	sll_iterator_t iterator: iterator structure where data is stored
Return Value: none
Time Complexity: O(1)
*/
void SinglyLinkedListSetData(sll_iterator_t iterator, void *data);
/****************************************************************************/
/*
Description: Counts the number of iterators in the list and returns that value
Parameters: 
	-const sll_t *list: linked list object
Return Value: number of iterators in the list
Time Complexity: O(n)
*/
size_t SinglyLinkedListCount(const sll_t *list);
/****************************************************************************/
/*
Description: Checks is the list is empty
Parameters: 
	-const sll_t *list: linked list object
Return Value: returns 0 if the list is not empty and 1 otherwise.
Time Complexity: O(1)
*/
int SinglyLinkedListIsEmpty(const sll_t *list);
/****************************************************************************/
/*
Description: Checks whether two nodes are identical
Parameters: 
	-const sll_iterator_t iterator1:First iterator to be compared
	-const sll_iterator_t iterator2:Second iterator to be compared
Return Value: returns 1 if the iterators are a match and 0 otherwise.
Time Complexity: O(1)
*/
int SinglyLinkedListIsMatchNode( const sll_iterator_t iterator1, const sll_iterator_t iterator2 );
/****************************************************************************/
/*
Description: Applies the supplied function on each iterator in the array in the range from iterator from to iterator to. Will also stop if the supplied function returns a non-zero int for any of the iterators in the range. The supplied function also accomodates an additional parameter which must be supplied.
Parameters: 
	-operation_func_t operation_func: function to be applied to data in list indicators
	-sll_iterator_t from: iterator from which to begin the application of the supplied function
	-sll_iterator_t to: iterator before which the application of the supplied function must end
	-void *parameter: additional parameter supplied to operation_func.
Return Value: returns the return value of operation_func at the last application, whether it is because the function returned a non-zero value or it is because iterator to was reached.
Time Complexity: O(n)
*/
int SinglyLinkedListForEach(operation_func_t operation_func,sll_iterator_t from, sll_iterator_t to, void *parameter);
/****************************************************************************/
/*
Description: Concatenating list 2 into list one, afterwards list 2 remains empty.
Parameters: 
	-sll_t list1: Pointer to list 1
	-sll_t list2: Pointer to list 2
Return Value: Void
Time Complexity: O(1)
*/
void SinglyLinkedListAppend(sll_t *list1, sll_t *list2);
/****************************************************************************/

#endif
