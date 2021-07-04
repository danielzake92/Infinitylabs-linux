/********************************************************************************
 *  FILENAME: Doubly_linked_list.c  DEVELOPER: Daniel Zaken  TEAM: Blue         * 
 *                                                                              *
 *  REVIEWER: Nely Nehemia                                                      * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating Doubly Linked List                   *
 *                                                                              *
 *******************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include "doubly_linked_list.h"
#include "utl.h"
/****************************************************************************/
/****************************************************************************/


typedef struct dll_node node_t;

struct dll_node /*node struct*/
{
	void *data;
	node_t *next;
	node_t *prev;	
};
/****************************************************************************/
struct dll /*managment struct*/
{
	node_t head;
	node_t tail;
};
/****************************************************************************/
static node_t *NodeAllocation(void);
/****************************************************************************/
dll_t *DoublyLinkedListCreate(void)
{
	dll_t *list = NULL;
	
	list = (dll_t*)malloc( sizeof(dll_t) );
	
	if ( list == NULL ) 
	{
		return NULL;
	}
	
	list->head.data = (void*)(list);
	list->head.next = &(list->tail);
	list->head.prev = NULL;
	
	list->tail.data = (void*)(list);
	list->tail.next = NULL;
	list->tail.prev = &(list->head);
	
	return(list);	
}
/****************************************************************************/
void DoublyLinkedListDestroy(dll_t *list)
{
    node_t *runner = NULL;
    node_t *runner_next = NULL;
    
    assert(list);
    
    runner = (list->head).next;
    
    while(runner->next)
    {
        runner_next = runner->next;
        free(runner);
        runner = runner_next;
    }

    free(list);
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListBegin(const dll_t *list)
{
	assert(list);
	return (list->head).next;	
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListEnd(const dll_t *list)
{	
	assert(list);
	return ( (node_t *)(&(list->tail)) );
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListInsert(dll_iterator_t where, void *data)
{
    node_t *new_node = NULL;
    assert(where);
    
    new_node = NodeAllocation(); /*possible to upgrade this functions with initializations*/
    
    if ( new_node == NULL ) 
    {
        while( where->next != NULL ) 
        {
            where = where->next;
        }
        return where;
    }
    
    new_node->next = where;
    where->prev->next = new_node;
    
    new_node->prev = where->prev;
    where->prev = new_node;
    
    new_node->data = data;
    
    return new_node;
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListPushBack(dll_t *list, void *data)
{
	assert(list);
	return ( DoublyLinkedListInsert( &(list->tail), data) );
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListPushFront(dll_t *list, void *data)
{
	assert(list);
	return ( DoublyLinkedListInsert( list->head.next, data) );
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListRemove( dll_iterator_t to_remove)
{
	node_t *temp = NULL;
	
	assert(to_remove);
	temp = to_remove->next;
	
	if( temp == NULL ) /*if temp == null than to_remove is tail*/
	{
		return to_remove; /*which means return tail*/
	}
	
	to_remove->prev->next = temp;
	temp->prev = to_remove->prev;
	free(to_remove);
	
	return(temp);
}
/****************************************************************************/
void *DoublyLinkedListPopBack(dll_t *list)
{
	void *temp = NULL;
	assert(list);
	assert( !DoublyLinkedListIsEmpty(list));
	
	temp = list->tail.prev->data;
	DoublyLinkedListRemove( list->tail.prev);
	return ( temp );
}
/****************************************************************************/
void *DoublyLinkedListPopFront(dll_t *list)
{
	void *temp = NULL;
	assert(list);
	assert( !DoublyLinkedListIsEmpty(list));
	
	temp = list->head.next->data;
	DoublyLinkedListRemove( list->head.next);
	return ( temp );
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListFind(match_func_t match_func, dll_iterator_t from, dll_iterator_t to,const void *parameter)
{
	int status = FALSE;
	assert(from);
	assert(to);
	assert(match_func);
	
	while( !DoublyLinkedListIsMatchNode(from, to) )
	{
		status = match_func( from->data, parameter );
		
		if ( status == TRUE )
		{
			return from;
		}
		from = from->next;
	}
	return from;	
}
/****************************************************************************/
int DoublyLinkedListFindMultiple(match_func_t match_func, dll_iterator_t from, dll_iterator_t to,const void *parameter,dll_t * output_list)
{
	int status = FALSE;
	int count = 0;
	assert(output_list);
	assert(from);
	assert(to);
	assert(match_func);
	
	while( !DoublyLinkedListIsMatchNode(from, to) )
	{
		status = match_func( from->data, parameter );
		
		if ( status == TRUE )
		{
			DoublyLinkedListPushBack(output_list, from->data);
			++count;
		}
		from = from->next;
	}
	return count;	
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListNext(const dll_iterator_t iterator)
{
	assert (iterator);
	return iterator->next;
}
/****************************************************************************/
dll_iterator_t DoublyLinkedListPrev(const dll_iterator_t iterator)
{
	assert (iterator);
	return iterator->prev;
}
/****************************************************************************/
void *DoublyLinkedListGetData(dll_iterator_t iterator)
{
	assert(iterator);
	return(iterator->data);
}
/****************************************************************************/
size_t DoublyLinkedListCount(const dll_t *list)
{
	node_t *runner = NULL;	
	size_t count = 0;
	assert(list);
	
	runner = (list->head).next;
	
	while(runner->next)
	{
		++count;
		runner = runner->next;
	}
	return count;
}
/****************************************************************************/
int DoublyLinkedListIsEmpty(const dll_t *list)
{
	assert(list);
	return( DoublyLinkedListIsMatchNode( (node_t *)(list->head).next, (node_t *)(&(list->tail)) ));
}
/****************************************************************************/
int DoublyLinkedListIsMatchNode( const dll_iterator_t iterator1, const dll_iterator_t iterator2 )
{
	assert(iterator1);
	assert(iterator2);	
	return ( iterator1 == iterator2 );
}
/****************************************************************************/

int DoublyLinkedListForEach(operation_func_t operation_func, dll_iterator_t from, dll_iterator_t to, void *parameter)
{
    int status = SUCCESS;
    assert(from);
    assert(to);
    assert(operation_func);
    
    while(  status == SUCCESS && !DoublyLinkedListIsMatchNode(from, to) ) 
    {
        status = operation_func (from->data, parameter);
        from = from->next;
    }
    return status;
}
/****************************************************************************/
/*
dll_iterator_t DoublyLinkedListSplice(dll_iterator_t where, dll_iterator_t from, dll_iterator_t to)
{
	node_t *temp = NULL;
	
	assert(where);
	assert(from);
	assert(to);
	
	if( DoublyLinkedListIsMatchNode(where, from) )
	{
		DoublyLinkedListPrev(to);
	}

	temp = to->prev;
	
	where->prev->next = from;
	from->prev->next = to;
	to->prev = from->prev;
	
	from->prev = where->prev;
	
	temp->next = where;
	
	return temp;		
}
*/

dll_iterator_t DoublyLinkedListSplice(dll_iterator_t where, 
                                    dll_iterator_t from, 
                                    dll_iterator_t to)
{
    node_t *where_prev = NULL;
    node_t *from_prev = NULL;
    node_t *to_prev = NULL;
    
    assert(where);
    assert(from);
    assert(to);

    if (from == where)
    {
        return to->prev;
    }
    
    where_prev = where->prev;
    from_prev = from->prev;
    to_prev = to->prev;
    
    where_prev->next = from;
    from->prev = where_prev;
    where->prev = to->prev;
    to_prev->next = where;
    
    to->prev = from_prev;
    from_prev->next = to;
    
    return to_prev;
}
/****************************************************************************/
static node_t *NodeAllocation(void)
{
	return ( (node_t*)malloc( sizeof(node_t) ) ); 
}
