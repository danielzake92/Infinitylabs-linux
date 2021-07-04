/********************************************************************************
 *  FILENAME:  pq_heap.c  DEVELOPER: Daniel Zaken   TEAM: Blue               
 *                                                                              
 *  Reviwer:                                                               
 *                                                                              
 *  PURPOSE:   Library for Modifying & creating Priority Queue         			
 *                                                                             *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/

#include "pq_heap.h" /*our header*/
#include "heap.h" /*our header*/
#include "utl.h" /*required for defines*/
/****************************************************************************/
struct priority_queue
{
    heap_t *queue;
};
/****************************************************************************/
p_queue_t *PQHeapCreate(pq_compare_func_t compare_func)
{
	p_queue_t *list = NULL;
	assert(compare_func);
	
	list = (p_queue_t *)malloc( sizeof(p_queue_t) );
	
	if (NULL == list) 
	{
		return NULL;
	}
	
	list->queue = HeapCreate(compare_func);
	
	if (NULL == list->queue) 
	{
		free(list);
		return NULL;
	}
	
	return list;
}
/****************************************************************************/
void PQHeapDestroy(p_queue_t *p_queue)
{
	assert(p_queue);
	
	HeapDestroy(p_queue->queue);
	
	p_queue->queue = NULL;
	
	free(p_queue);
}
/****************************************************************************/
int PQHeapEnqueue(p_queue_t *p_queue, void *data)
{
	assert(p_queue);
	
	return (HeapPush(p_queue->queue, data));
}
/****************************************************************************/
void *PQHeapDequeue(p_queue_t *p_queue)
{
	void *data = NULL;

	assert(p_queue);

	data = HeapPeek(p_queue->queue);

	if( FAIL == HeapPop(p_queue->queue))
	{
		return NULL;
	}
	
	return data;
}
/****************************************************************************/
void *PQHeapPeek(const p_queue_t *p_queue)
{
	assert(p_queue);
	
	return (HeapPeek(p_queue->queue));
}
/****************************************************************************/
int PQHeapIsEmpty(const p_queue_t *p_queue)
{
	assert(p_queue);
	
	return (HeapIsEmpty(p_queue->queue));
}
/****************************************************************************/
size_t PQHeapSize(const p_queue_t *p_queue)
{
	assert(p_queue);
	
	return (HeapSize(p_queue->queue));
}
/****************************************************************************/
void PQHeapClear(p_queue_t *p_queue)
{
	assert(p_queue);
	
	while( !HeapIsEmpty(p_queue->queue))
	{
		HeapPop(p_queue->queue);
	}
}
/****************************************************************************/
void *PQHeapErase(p_queue_t *p_queue, pq_match_func_t match_func, void *parameter)
{
	void *data = NULL;
	
	assert(p_queue);
	assert(match_func);
	
	data = HeapRemove(p_queue->queue, match_func, parameter);

	return(data);
}

