/********************************************************************************
 *  FILENAME:  pq_heap.h  DEVELOPER: Daniel Zaken   TEAM: Green
 *
 *  Reviwer:   Itamar Aron
 *
 *  PURPOSE:   Library for Modifying & creating Priority Queue
 *
 *******************************************************************************/
#ifndef __ILRD_PRIORITY_QUEUE_H__
#define __ILRD_PRIORITY_QUEUE_H__

#include <stddef.h> /*required for size_t type*/
/****************************************************************************/


typedef int(*pq_compare_func_t)(const void *data1, const void *data2 ); /*default*/

typedef int(*pq_match_func_t)(const void *data, const void *parameter );

/*managmnet typedef */
typedef struct priority_queue p_queue_t;


/****************************************************************************/
/*
Description: creates priority queue.
Parameters:

				compare_func -> compare_func = default queue priority function

Return Value: returns the queue address
Time Complexity: O(1);
*/
p_queue_t *PQHeapCreate(pq_compare_func_t compare_func);
/****************************************************************************/
/*
Description: Free allocations
Parameters:

				queue -> The queue address

Return Value: void
Time Complexity: o(1)
*/
void PQHeapDestroy(p_queue_t *p_queue);
/****************************************************************************/
/*
Description: Enqueues new element
Parameters:

				p_queue -> The queue address
				data -> The data to be Enqueued

Return Value: int 0 if success 1 if fails
Time Complexity: o(log(n))
*/
int PQHeapEnqueue(p_queue_t *p_queue, void *data);   /* (FIFO)*/
/****************************************************************************/
/*
Description: Removes first element from queue and returns the data.
Parameters:

				p_queue -> The queue address

Return Value: Returns the data of the poped item
Time Complexity: o(log(n))
*/
void *PQHeapDequeue(p_queue_t *p_queue);
/****************************************************************************/
/*
Description: Returns the data of first element in queue
Parameters:

				p_queue -> The queue address

Return Value: returns the first data in the queue
Time Complexity: o(1)
*/
void *PQHeapPeek(const p_queue_t *p_queue);
/****************************************************************************/
/*
Description: checks if queue is empty.
Parameters:

				p_queue -> The queue address

Return Value: True(1) for empty queue false(0) non empty queue
Time Complexity: o(1)
*/
int PQHeapIsEmpty(const p_queue_t *p_queue);
/****************************************************************************/
/*
Description: returns number of elements in queue
Parameters:

				p_queue -> The queue address

Return Value: returns queue object number
Time Complexity: o(1)
*/
size_t PQHeapSize(const p_queue_t *p_queue);
	/****************************************************************************/
/*
Description: clears the queue
Parameters:

				p_queue -> The queue address

Return Value: void
Time Complexity: o(n * log(n))
*/
void PQHeapClear(p_queue_t *p_queue);
/****************************************************************************/
/*
Description: Removes the first element that matches and returns the data.
Parameters:

				p_queue -> The queue address
				match_func -> The matching function which according to an would be removed
			    parameter -> parameter to be adjusted in the match function

Return Value: returns the data of the object which has been removed
Time Complexity: o(n)
*/

void *PQHeapErase(p_queue_t *p_queue, pq_match_func_t match_func, void *parameter);
/****************************************************************************/

#endif
