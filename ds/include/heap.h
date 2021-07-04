/*****************************************************************************
 *	FILENAME:	heap.h		AUTHOR: Liad Oz		TEAM: Blue	   LAB: OL100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    API for Heap data structure.							     *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_HEAP_H__
#define __ILRD_HEAP_H__

#include <stddef.h> /* size_t */
#include "dynamic_vector.h"
/*****************************************************************************/
typedef struct heap heap_t;

/*
0 equal, positive bigger, negative smaller,
*/
typedef int(*h_cmp_func_t)(const void *lhs, const void *rhs);

/* 1 match, otherwise 0 */
typedef int(*h_match_func_t)(const void *lhs,const void *rhs);

typedef enum status
{
    SUCCESS = 0,
    FAIL = 1
} status_t;

typedef enum boolean
{
    FALSE = 0,
    TRUE = 1
}bool_t;


/********************************** README ***********************************/
/*
 * please include the header files (with complexity times) for code review.
 * don't forget implementing heapify.
 * including dynamic vector.
 */
/*****************************************************************************/
 /*
  * Description: Create a new empty Min Heap structure.
  * Return value: HeapCreate returns pointer to newly created heap or NULL if
  * memory allocation failed.
  * Time Complexity: O(1)
 */
heap_t *HeapCreate(h_cmp_func_t cmp_func);
/*****************************************************************************/
/*
 * Description: Destroy a given heap.
 * Return value: none
 * Time Complexity: O(1)
 */
void HeapDestroy(heap_t *heap);
/*****************************************************************************/
/*
 * Description: Insert new value into given heap.
 * Return value: 0 if placement was successful, 1 otherwise.
 * Placement may be unsuccessful if memory allocation fails.
 * Time Complexity: O(log(n))
 */
status_t HeapPush(heap_t *heap, const void *data);
/*****************************************************************************/
/*
 * Description: Remove element with the minimal value from the heap.
 * Return value: none
 * UB: Trying to pop an empty heap.
 * Time Complexity: o(log(n))
 */
status_t HeapPop(heap_t *heap);
/*****************************************************************************/
/*
 * Description: Get the value of the minimal element of the heap.
 * Return value: The value of the minimal element or NULL if the heap is empty.
 * Time Complexity: o(1)
 */
void *HeapPeek(const heap_t *heap);
/*****************************************************************************/
/*
 * Description: Get the total number of elements in the heap.
 * Return value: number of elements currently in the heap.
 * Time Complexity: o(1)
 */
size_t HeapSize(const heap_t *heap);
/*****************************************************************************/
/*
 * Description: Check whether given heap has elements.
 * Return value: 1 if heap is empty, 0 otherwise.
 * Time Complexity: o(1)
 */
bool_t HeapIsEmpty(const heap_t *heap);
/*****************************************************************************/
/*
 * Description: This function is searching an element with the value:
 * match_func using the match function, upon finding the first such element,
 * its removed from the heap and it's value is returned to the caller. If no
 * such element found in the heap, NULL is returned to the caller.
 * Return value: The value of the removed element or NULL if no element found.
 * Time Complexity: o(n)
 */
void *HeapRemove(heap_t *heap, h_match_func_t match_func, const void *data);
/*****************************************************************************/
#endif
