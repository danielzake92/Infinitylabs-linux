/********************************************************************************
 *  FILENAME:  queue.h  DEVELOPER: Daniel Zaken   TEAM: Blue                    *
 *                                                                              *
 *  Reviwer:   Kim Aharfi                                                       *
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating Queue Data Structure 			*
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include "singly_linked_list.h"/*Lib header*/
#include "queue.h"/*Lib header*/
#define SUCCESS 0
#define FAILURE 1
/****************************************************************************/

struct queue
{
	sll_t *list;
};
/****************************************************************************/
queue_t *QueueCreate(void)
{
	queue_t *manage = (queue_t *)malloc( sizeof(queue_t) );
	if ( !manage ) return NULL;

	manage->list = SinglyLinkedListCreate();

	if( manage->list == NULL)
	{
		free(manage);
		return NULL;
	}

	return manage;
}
/****************************************************************************/
void QueueDestroy(queue_t *queue)
{
	assert(queue);
	SinglyLinkedListDestroy(queue->list);
	queue->list = NULL; /*Heap to heap ptr, dangling ptr aborted by NULL*/

	free(queue);
}
/****************************************************************************/
int QueueEnqueue(queue_t *queue, void *data)
{
	sll_iterator_t get = NULL;

	assert(queue);

	get = SinglyLinkedListInsert( SinglyLinkedListEnd(queue->list) , data);

	if( SinglyLinkedListIsMatchNode(get, SinglyLinkedListEnd(queue->list)))
	{
		return FAILURE;
	}

	return SUCCESS;
}

/****************************************************************************/
void QueueDequeue(queue_t *queue)
{
	assert(queue);
	assert( !QueueIsEmpty(queue) );
	SinglyLinkedListRemove(SinglyLinkedListBegin(queue->list));
}
/****************************************************************************/

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	assert( !QueueIsEmpty(queue) );
	return ( SinglyLinkedListGetData(SinglyLinkedListBegin(queue->list)) );
}

/****************************************************************************/
int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	return(SinglyLinkedListIsEmpty(queue->list));
}
/****************************************************************************/
size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	return(SinglyLinkedListCount(queue->list));
}
/****************************************************************************/

void QueueAppend(queue_t *queue1, queue_t *queue2)
{
	assert(queue1);
	assert(queue2);
	assert( !QueueIsEmpty(queue2) );

	SinglyLinkedListAppend(queue1->list, queue2->list);
}
/****************************************************************************/
