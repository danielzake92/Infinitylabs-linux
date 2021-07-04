/********************************************************************************
 *  FILENAME:  search.h  DEVELOPER:    TEAM:
 *
 *  Reviwer:
 *
 *  PURPOSE:   Function for sorting lists
 *
 *******************************************************************************/
#ifndef __ILRD_SORTS_H__
#define __ILRD_SORTS_H__

#include <stddef.h> /*required for size_t type*/

/****************************************************************************/
/*
Description: Performs iterative binary search on the array.
Parameters: arr - a pointer to the array to search.
			last_index - The last index in the array
			data - the data to search.
Return Value: the index of the found element, -1 otherwise.
Time Complexity:
Space Complexity:
*/
int BinarySearchIter(const int *arr, int last_index, int data);
/****************************************************************************/
/*
Description: Performs recursive binary search on the array.
Parameters: arr - a pointer to the array to search.
			last_index - The last index in the array
			data - the data to search.
Return Value: the index of the found element, -1 otherwise.
Time Complexity:
Space Complexity:
*/
int BinarySearchRec(const int *arr, int last_index, int data);

#endif
