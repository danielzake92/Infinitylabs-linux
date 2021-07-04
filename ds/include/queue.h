/********************************************************************************
 *  FILENAME:  stack.h  DEVELOPER: Daniel Zaken   TEAM: Blue                    * 
 *                                                                              *
 *  Reviwer:   Kim Aharfi                                                       * 
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating Queue Data Structure 			*
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_QUEUE_H__
#define __ILRD_QUEUE_H__
/****************************************************************************/
#include <stddef.h> /*required for size_t type*/


/****************************************************************************/

typedef struct queue queue_t; /* queue_t: queue data structure */

/****************************************************************************/
/*
Description: Creates a new queue
Parameters: None
Return Value: Pointer to newly created queue
Time Complexity: O(1)
*/
queue_t *QueueCreate(void);

/****************************************************************************/
/*
Description: Destroys the input queue
Parameters: 
	-queue_t queue: Queue data structure
Return Value: None
Time Complexity: O(n)
*/
void QueueDestroy(queue_t *queue);

/****************************************************************************/
/*
Description: Adds an element to the back of the queue
Parameters: 
	-queue_t queue: Queue data structure
	-void *data: data to be added to back of queue
Return Value: int representing success, 0, or failure,1.
Time Complexity: O(1) on average but 0(n) in case of allocation failure
*/
int QueueEnqueue(queue_t *queue, void *data);

/****************************************************************************/
/*
Description: removes the element at the front of the queue
Parameters: 
	-queue_t queue: Queue data structure
Return Value: None
Time Complexity: O(1)
*/
void QueueDequeue(queue_t *queue);

/****************************************************************************/

/*
Description: Returns the element at the front of the queue
Parameters: 
	-const queue_t queue: Queue data structure
Return Value: element at the front of the queue
Time Complexity: O(1)
*/
void *QueuePeek(const queue_t *queue);
/****************************************************************************/

/*
Description: determines whether the queue is empty
Parameters: 
	-const queue_t queue: Queue data structure
Return Value: returns 0 if queue is not empty, and 1 otherwise
Time Complexity: O(1)
*/
int QueueIsEmpty(const queue_t *queue);

/****************************************************************************/

/*
Description: returns the size of the input queue
Parameters: 
	-const queue_t queue: Queue data structure
Return Value: 
Time Complexity: O(n)
*/
size_t QueueSize(const queue_t *queue);

/****************************************************************************/
/*
Description: Append queue2 to the end of queue1, leaving queue2 empty
Parameters: 
	-queue_t queue1: queue to be appended to
	-queue_t queue2: queue whose contents are appended to queue1
Return Value: None
Time Complexity: O(1)
*/
void QueueAppend(queue_t *queue1, queue_t *queue2);

/****************************************************************************/
#endif
