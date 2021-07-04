/********************************************************************************
 *  FILENAME:  sorts.h  DEVELOPER: Daniel Zaken   TEAM: Green
 *
 *  Reviwer:   Elizabeta
 *
 *  PURPOSE:   Function for sorting lists
 *
 *******************************************************************************/
#ifndef __ILRD_SORTS_H__
#define __ILRD_SORTS_H__

#include <stddef.h> /*required for size_t type*/

typedef int (*cmp_func_t)(void const *lhs, void const *rhs);
/****************************************************************************/
/*
Description:
Parameters:
Return Value:
Time Complexity: O(n^2)
Space Complexity:
Stability:
*/
void BubbleSort(int *arr, size_t arr_size);
/****************************************************************************/
/*
Description:
Parameters:
Return Value:
Time Complexity: O(n^2)
Space Complexity:
Stability:
*/
void InsertionSort(int *arr, size_t arr_size);
/****************************************************************************/
/*
Description:
Parameters:
Return Value:
Time Complexity: O(n^2)
Space Complexity:
Stability:
*/
void SelectionSort(int *arr, size_t arr_size);
/****************************************************************************/
/*
Description:
Parameters:
Return Value: (0) for success (1) for failure
Time Complexity:
Space Complexity:
Stability:
*/
int RadixSort(int *arr, size_t arr_size);
/****************************************************************************/
/*
Description:
Parameters:
Return Value: (0) for success (1) for failure
Time Complexity:
Space Complexity:
Stability:
*/
int CountingSort(int *arr, size_t arr_size);
/****************************************************************************/
/*
Description: Performs merge sort on the input array.
Parameters: arr - a pointer to the array to sort.
			arr_size - the number of elements.
Return Value: (0) for success (1) for failure
Time Complexity: o(n * log n)
Space Complexity: o(n)
Stability:
*/
int MergeSort(int *arr, size_t arr_size);
/****************************************************************************/
/*
Description: Performs merge sort on the input array.
Parameters: arr - a pointer to the array to sort.
			arr_size - the number of elements.
			element_size - size of the array element data type.
			cmp_func - a compare function.
Return Value: (0) for success (1) for failure
Time Complexity: o(n * log n)
Space Complexity: o(n)
Stability:
*/
int MergeSortGeneric(void *arr, size_t arr_size, size_t element_size, cmp_func_t cmp_func);
/****************************************************************************/
/*
Description: Performs recursive quick sort on the input array.
Parameters: base - a pointer to the array to sort.
			nmemb - the number of elements.
			size - size of the array element data type.
			cmp_func - a compare function.
Return Value: (0) for success (1) for failure
Time Complexity: o(n * log n)
Space Complexity: o(log n)
Stability:
*/

int QuickSortGeneric(void *base, size_t nmemb, size_t size, cmp_func_t cmp_func);
/****************************************************************************/


int CountingForRadixSort(int *arr, size_t arr_size, int digit);
#endif
