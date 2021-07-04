/********************************************************************************
 *  FILENAME:  singly_linked_list.c  DEVELOPER: Daniel Zaken  TEAM: Blue        * 
 *                                                                              *
 *  REVIEWER: --------                                                          * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating DynamicVector Singly Linked List     *
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include <assert.h>/*Required for assert function*/
#include "singly_linked_list.h"/*Lib header*/
#define SUCCESS 0
#define FAILURE 1
/****************************************************************************/
typedef struct sll_node sll_node_t;

struct sll
{
	sll_node_t *head;
	sll_node_t *tail;
};
/****************************************************************************/
struct sll_node
{
	void *data;
	sll_iterator_t next;	
};
/****************************************************************************/

static sll_node_t *NodeAllocation(void);

/****************************************************************************/
static sll_node_t *NodeAllocation(void)
{
	return ( ( sll_node_t * )malloc( sizeof(sll_node_t) ) ); 
}

sll_t *SinglyLinkedListCreate(void)
{
	sll_t *list = NULL;
	sll_node_t *dummy = NULL;
	
	list = (sll_t*)malloc( sizeof(sll_t) );
	if ( !list ) return NULL;
	
	dummy = NodeAllocation();
	if ( !dummy ) 
	{
		free(list);
		return NULL;
	}
		
	dummy->data = (void*)(list);
	dummy->next = NULL;
	
	list->head = dummy;
	list->tail = dummy;
	
	return list;
}
/****************************************************************************/
void SinglyLinkedListDestroy(sll_t *list)
{
	sll_node_t *runner = NULL;
	sll_node_t *runner_next = NULL;
	
	assert(list);
	
	runner = list->	head;
	
	while( runner )
	{
		runner_next = runner->next;				
		free(runner);
		runner = runner_next;
	}
	
	list->head = NULL;/*heap to heap pointer*/
	list->tail = NULL;	
	
	free(list);
}
/****************************************************************************/
sll_iterator_t SinglyLinkedListBegin(const sll_t *list)
{
	assert(list);
	return (list->head);
}
/****************************************************************************/
sll_iterator_t SinglyLinkedListEnd(const sll_t *list)
{
	assert(list);
	return (list->tail);
}
/****************************************************************************/
sll_iterator_t SinglyLinkedListInsert(sll_iterator_t iterator, void *data)
{
	sll_node_t *new_node = NULL;
	
	assert(iterator);
	
	new_node = NodeAllocation();
	if ( new_node == NULL ) 
	{
		while( iterator->next != NULL ) /*get the dummy*/
		{
			iterator = iterator->next;
		}
		return iterator; /*returns dummy*/
	}
	
	
	new_node->next = iterator->next;
	iterator->next = new_node;
	new_node->data = iterator->data;
	iterator->data = data;
	
	if( new_node->next == NULL ) /*iterator->next is equal to dummy->next which is NULL*/ 
	{
		( (sll_t*)(new_node->data) )->tail = new_node; /*tail looks at new*/
	}
	
	return iterator;
}
/****************************************************************************/
sll_iterator_t SinglyLinkedListRemove( sll_iterator_t iterator)
{
	sll_node_t *temp = iterator->next;
	
	assert(iterator);
	
	if ( !temp )return iterator; /*if temp is dummy then return dummy*/
	
	iterator->data = temp->data;
	iterator->next = temp->next;
	
	free(temp);
	
	if( iterator->next == NULL ) /*iterator->next is equal to dummy->next which is NULL*/ 
	{
		( (sll_t*)(iterator->data) )->tail = iterator; 
	}
	
	return iterator->next;
}
/****************************************************************************/
sll_iterator_t SinglyLinkedListFind(match_func_t match_func, sll_iterator_t from,sll_iterator_t to,void *parameter)
{	
	int status = 0;
	assert(from);
	assert(to);
	
	while( !SinglyLinkedListIsMatchNode(from, to) )
	{
		status = match_func( from->data, parameter );
		
		if ( status == 1 )
		{
			return from;
		}
		from = from->next;
	}
	return to;	
}
/****************************************************************************/
sll_iterator_t SinglyLinkedListNext(const sll_iterator_t iterator)
{
	assert(iterator);
	return (iterator->next);
}
/****************************************************************************/
void *SinglyLinkedListGetData(const sll_iterator_t iterator)
{
	assert(iterator);
	return iterator->data;	
}
/****************************************************************************/
void SinglyLinkedListSetData(sll_iterator_t iterator, void *data)
{
	assert(iterator);
	assert(data);
	
	iterator->data = data;	
}
/****************************************************************************/
size_t SinglyLinkedListCount(const sll_t *list)
{
	sll_node_t *iterator = NULL;	
	size_t count = 0;
	assert(list);
	
	iterator = list->head;
	
	while( (iterator->next) )
	{
		++count;
		iterator = iterator->next;
	}
	return count;
}
/****************************************************************************/
int SinglyLinkedListIsEmpty(const sll_t *list)
{
	assert(list);
	return(list->head->next == NULL);
}
/****************************************************************************/
int SinglyLinkedListIsMatchNode( const sll_iterator_t iterator1, const sll_iterator_t iterator2 )
{
	assert(iterator1);
	assert(iterator2);
	return ( iterator1 == iterator2 );	
}
/****************************************************************************/
int SinglyLinkedListForEach(operation_func_t operation_func,sll_iterator_t from, sll_iterator_t to, void *parameter)
{
	int status = SUCCESS;
	assert(from);
	assert(to);
	assert(parameter);
    assert(operation_func);
	
	while( !SinglyLinkedListIsMatchNode(from, to) )
	{
		status = operation_func (from->data, parameter);
		if ( status == FAILURE )return status;
		from = from->next;
	}
	return status;
}
/****************************************************************************/
void SinglyLinkedListAppend(sll_t *list1, sll_t *list2)
{
	assert(list1);
	assert(list2);
	
	list1->tail->next = list2->head->next;
	list1->tail->data = list2->head->data;
	
	list1->tail = list2->tail;
	list1->tail->data = (void*)(list1);
	
	list2->head->data = (void*)(list2);
	list2->head->next = NULL;
	list2->tail = list2->head;
}
/****************************************************************************/







