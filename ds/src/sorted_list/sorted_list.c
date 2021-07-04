/********************************************************************************
 *  FILENAME:  sorted_list.c  DEVELOPER: Daniel Zaken   TEAM: Blue              * 
 *                                                                              *
 *  Reviwer:   Kim Ahafri                                                       * 
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating Sortedlist          			*
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include <stdio.h>/*Required for dynamic memory allocation functions*/
#include "doubly_linked_list.h"
#include "sorted_list.h" 
#include "utl.h"

static dll_iterator_t StoD(sl_iterator_t iterator)
{
    #ifdef NDEBUG
        return(    iterator );
    #else
        return(    iterator.internal_itr );    
    #endif
}


static sl_iterator_t DtoS(dll_iterator_t iterator)
{
    #ifdef NDEBUG
        return(    iterator );
    #else
        struct sl_iterator temp;
        temp.internal_itr = iterator;  
        temp.list = NULL;      
        return(temp);
    #endif
}

struct sorted_list
{
    dll_t *list;
    sl_compare_func_t sl_compare_func;
};
/****************************************************************************/
s_list_t *SortedListCreate(sl_compare_func_t sort_func)
{
	s_list_t *slist = NULL;
	
	assert(sort_func);
	slist = (s_list_t*)malloc( sizeof(s_list_t) );
	
	if ( slist == NULL ) 
	{
		return NULL;
	}
	
	slist->list = DoublyLinkedListCreate();
	
	if ( slist->list == NULL ) 
	{
		free(slist);
		return NULL;
	}
	
	slist->sl_compare_func = sort_func;
	return slist;
}
/****************************************************************************/
void SortedListDestroy(s_list_t *list)
{
	assert(list);
	
	DoublyLinkedListDestroy(list->list);
	list->list = NULL;
	list->sl_compare_func = NULL;
	
	free(list);
}
/****************************************************************************/
void *SortedListGetData(sl_iterator_t iterator)
{    
    assert(StoD(iterator));
    return DoublyLinkedListGetData(StoD(iterator));    
}
/****************************************************************************/
sl_iterator_t SortedListBegin(const s_list_t *list)
{	
	assert(list);
	return (DtoS(DoublyLinkedListBegin(list->list)));
}
/****************************************************************************/
sl_iterator_t SortedListEnd(const s_list_t *list)
{
	assert(list);
	return (DtoS(DoublyLinkedListEnd(list->list)));
}
/****************************************************************************/
sl_iterator_t SortedListInsert(s_list_t *list,  void *data)
{
	sl_compare_func_t cpr_func = NULL;
	dll_iterator_t iter = NULL;
	dll_iterator_t end = NULL;
	
	assert(data);
	assert(list);
	
	iter = DoublyLinkedListBegin(list->list);
	end = DoublyLinkedListEnd(list->list);
	cpr_func = list->sl_compare_func;
	
	while( !DoublyLinkedListIsMatchNode(iter, end) && cpr_func( DoublyLinkedListGetData(iter) ,data ) <= 0  )
	{
		iter = DoublyLinkedListNext(iter);
	}
	
	return( DtoS( DoublyLinkedListInsert( iter, data ))); 
}
/****************************************************************************/
void *SortedListPopBack(s_list_t *list)
{
	assert(list);
	return(DoublyLinkedListPopBack(list->list));
}
/****************************************************************************/
void *SortedListPopFront(s_list_t *list)
{
	assert(list);
	return(DoublyLinkedListPopFront(list->list));
}
/****************************************************************************/
sl_iterator_t SortedListFind(const s_list_t *list, sl_iterator_t from, sl_iterator_t to,const void *data)
{
	sl_compare_func_t cpr_func = NULL;
	assert(list);
	assert(StoD(from));
	assert(StoD(to));
	cpr_func = list->sl_compare_func;
	
	while( cpr_func( DoublyLinkedListGetData(StoD(from)) ,data ) < 0 &&  !DoublyLinkedListIsMatchNode(StoD(from), StoD(to)) )
	{
		from = SortedListNext(from);
	}
	
	if (cpr_func( DoublyLinkedListGetData(StoD(from)) ,data ) == 0)
	{
		return from;
	}
	return to;	
}
/****************************************************************************/
sl_iterator_t SortedListFindIf(sl_iterator_t from, sl_iterator_t to, match_func_t match_func, const void *param)
{
	assert(match_func);
	assert(StoD(from));
	assert(StoD(to));
	
	return(DtoS( DoublyLinkedListFind( match_func, StoD(from),StoD(to) ,param)));
}
/****************************************************************************/
sl_iterator_t SortedListRemove(sl_iterator_t where)
{
	assert(StoD(where));
	return(DtoS(DoublyLinkedListRemove(StoD(where))));
}
/****************************************************************************/
sl_iterator_t SortedListNext(const sl_iterator_t iterator)
{
	assert(StoD(iterator));
	return (DtoS(DoublyLinkedListNext(StoD(iterator))));
}
/****************************************************************************/
sl_iterator_t SortedListPrev(const sl_iterator_t iterator)
{
	assert(StoD(iterator));
	return (DtoS(DoublyLinkedListPrev(StoD(iterator))));
}
/****************************************************************************/
size_t SortedListCount(const s_list_t *list)
{
	assert(list);
	return(DoublyLinkedListCount(list->list));
}
/****************************************************************************/
int SortedListIsEmpty(const s_list_t *list)
{
	assert(list);
	return(DoublyLinkedListIsEmpty(list->list));
}
/****************************************************************************/
int SortedListIsMatchNode(const sl_iterator_t iterator1, const sl_iterator_t iterator2 )
{
	assert(StoD(iterator1));
	assert(StoD(iterator2));
	return(DoublyLinkedListIsMatchNode(StoD(iterator1), StoD(iterator2)));
}
/****************************************************************************/
int SortedListForEach(sl_operation_func_t operation_func, sl_iterator_t from, sl_iterator_t to, void *parameter)
{
    assert(StoD(from));
    assert(StoD(to));
    assert(operation_func);
    
    return (DoublyLinkedListForEach(operation_func,StoD(from), StoD(to), parameter));
}
/****************************************************************************/
void SortedListMerge(s_list_t *dest_list, s_list_t *src_list)
{
	dll_iterator_t where = NULL; /*list1*/
	dll_iterator_t from = NULL; /*list2*/
	dll_iterator_t to = NULL;  /*list2*/
	dll_iterator_t end1 = NULL; /*list1*/
	sl_compare_func_t cpr_func = NULL;
	
	assert(dest_list);
	assert(src_list);
	assert(dest_list->sl_compare_func == src_list->sl_compare_func);
	
	cpr_func = dest_list->sl_compare_func;
	
	where = DoublyLinkedListBegin(dest_list->list);
	from = DoublyLinkedListBegin(src_list->list);
	to = DoublyLinkedListNext(from);
	end1 = DoublyLinkedListEnd(dest_list->list);
	
	while( !SortedListIsEmpty(src_list) && !DoublyLinkedListIsMatchNode(where, end1))
	{	
		while( cpr_func(DoublyLinkedListGetData(where), DoublyLinkedListGetData(from)) < 0 && !DoublyLinkedListIsMatchNode(where, end1) ) /*where <= from */
		
		{
			where = DoublyLinkedListNext(where);
		}
		
		while( cpr_func(DoublyLinkedListGetData(where), DoublyLinkedListGetData(to)) >= 0 ) /*where => to */ 
		{
			to = DoublyLinkedListNext(to);
		}
		
		DoublyLinkedListSplice( where, from, to);
		
		from = to;
		to = DoublyLinkedListNext(from);
		where = DoublyLinkedListNext(where);
	}
}

/*https://wb.infinitylabs.co.il/boards/PjQh305kpVHPqemtvdnlw7IBKFKhiOJOf25MMWShSCU-#0,1130,0.8*/

