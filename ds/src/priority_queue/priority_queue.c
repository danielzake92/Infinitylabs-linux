/********************************************************************************
 *  FILENAME:  sorted_list.c  DEVELOPER: Daniel Zaken   TEAM: Blue              * 
 *                                                                              *
 *  Reviwer:   Vladi                                                            * 
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating Priority Queue         			*
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include "sorted_list.h" /*required fro piping*/
#include "priority_queue.h" /*our header*/
#include "utl.h" /*required for defines*/
/****************************************************************************/
struct priority_queue
{
    s_list_t *queue;
};
/****************************************************************************/
p_queue_t *PriorityQueueCreate(pq_compare_func_t compare_func)
{
	p_queue_t *list = NULL;
	assert(compare_func);
	
	list = (p_queue_t *)malloc( sizeof(p_queue_t) );
	
	if (NULL == list) 
	{
		return NULL;
	}
	
	list->queue = SortedListCreate(compare_func);
	
	if (NULL == list->queue) 
	{
		free(list);
		return NULL;
	}
	
	return list;
}
/****************************************************************************/
void PriorityQueueDestroy(p_queue_t *p_queue)
{
	assert(p_queue);
	
	SortedListDestroy(p_queue->queue);
	
	p_queue->queue = NULL;
	
	free(p_queue);
}
/****************************************************************************/
int PriorityQueueEnqueue(p_queue_t *p_queue, void *data)
{
	assert(p_queue);
	
	return (SortedListIsMatchNode( SortedListEnd(p_queue->queue), SortedListInsert(p_queue->queue, data)));
}
/****************************************************************************/
void *PriorityQueueDequeue(p_queue_t *p_queue)
{
	assert(p_queue);
	
	return (SortedListPopFront(p_queue->queue));
}
/****************************************************************************/
void *PriorityQueuePeek(const p_queue_t *p_queue)
{
	assert(p_queue);
	
	return ( SortedListGetData( SortedListBegin (p_queue->queue)));
}
/****************************************************************************/
int PriorityQueueIsEmpty(const p_queue_t *p_queue)
{
	assert(p_queue);
	
	return ( SortedListIsEmpty(p_queue->queue));
}
/****************************************************************************/
size_t PriorityQueueSize(const p_queue_t *p_queue)
{
	assert(p_queue);
	
	return (SortedListCount(p_queue->queue));
}
/****************************************************************************/
void PriorityQueueClear(p_queue_t *p_queue)
{
	assert(p_queue);
	
	while( !SortedListIsEmpty(p_queue->queue))
	{
		SortedListPopFront(p_queue->queue);
	}
}
/****************************************************************************/
void *PriorityQueueErase(p_queue_t *p_queue, pq_match_func_t match_func, void *parameter)
{
	sl_iterator_t temp = {0};
	void *data = NULL;
	
	assert(p_queue);
	assert(match_func);
	
	temp = SortedListFindIf(SortedListBegin(p_queue->queue), SortedListEnd(p_queue->queue), match_func, parameter);
	
	if ( SortedListIsMatchNode( SortedListEnd(p_queue->queue), temp) )
	{
		return NULL;
	}
	
	data = SortedListGetData(temp); 
	SortedListRemove(temp);
	
	return(data);
}

