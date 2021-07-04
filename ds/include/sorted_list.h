/********************************************************************************
 *  FILENAME:  sorted_list.c  DEVELOPER: Daniel Zaken   TEAM: Blue              * 
 *                                                                              *
 *  Reviwer:   Kim Ahafri                                                       * 
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating Sortedlist          			*
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_SORTED_LINKED_LIST_H__
#define __ILRD_SORTED_LINKED_LIST_H__

#include <stddef.h> /*required for size_t type*/
#include "doubly_linked_list.h" 
/****************************************************************************/


typedef int(*sl_compare_func_t)(const void *data1, const void *data2 ); /*default*/

typedef int(*sl_match_func_t)(const void *data, const void *parameter );  

typedef int(*sl_operation_func_t)(void *data, void *parameter); 
/*managmnet typedef */
typedef struct sorted_list s_list_t;

#ifdef NDEBUG  /*#ifdef _DEBUG*/

	/*iterator typedef release version*/
	typedef dll_iterator_t sl_iterator_t;

#else

	/*iterator typedef debug version*/
	typedef struct sl_iterator sl_iterator_t;

	/*iterator struct debug version*/
	struct sl_iterator
	{
		dll_iterator_t internal_itr;
		s_list_t *list;
	};

#endif

/*managmnet struct */		


/****************************************************************************/
/*
Description: creat list and store compare func in list.
Parameters: 

				sort_func -> sort_func = default list sort function

Return Value: 	retruns the list address
Time Complexity: O(1);
*/
s_list_t *SortedListCreate(sl_compare_func_t sort_func);
/****************************************************************************/
/*
Description: Free allocations 
Parameters: 

				list -> The list address
				
Return Value:   void
Time Complexity: O(n)
*/
void SortedListDestroy(s_list_t *list);
/****************************************************************************/
/*
Description: Returns first valid iterator
Parameters: 
	
				list -> The list pointer	
	
Return Value: returns the first valid iterator
Time Complexity: O(1)
*/
sl_iterator_t SortedListBegin(const s_list_t *list);
/****************************************************************************/
/*
Description: return tail
Parameters: 
	
				list -> The list pointer	

Return Value: returns the tail iterator which his dummy
Time Complexity: O(1)
*/
sl_iterator_t SortedListEnd(const s_list_t *list);
/****************************************************************************/
/*
Description: inserting elements in the right location .
when element is identical to other element: FIFO- whichever inserted first will be closer to the Head
Parameters:

				list -> The list pointer
				data -> The data to be inserted
 
Return Value: returns the iterator which was inserted
Time Complexity: O(n)
*/
sl_iterator_t SortedListInsert(s_list_t *list,  void *data);
/****************************************************************************/
/*
Description: remove given iterator
Parameters: 

				where -> represents the iterator to be removed

Return Value: returns the next iterator to the removed one
Time Complexity: O(1)
*/
sl_iterator_t SortedListRemove(sl_iterator_t where);
/****************************************************************************/
/*
Description: pop from end
Parameters: 

			list -> The list pointer

Return Value: returns the poped data 
Time Complexity: O(1)
*/
void *SortedListPopBack(s_list_t *list);
/****************************************************************************/
/*
Description: pop from front
Parameters: 

			list -> The list pointer

Return Value: returns the poped data 
Time Complexity: O(1)
*/
void * SortedListPopFront(s_list_t *list);
/****************************************************************************/
/*
Description: find given data in list
Parameters: 

			list -> The list pointer
			from -> find from iterator
			to -> find to iterator
			data -> data to be found

Return Value: retruns the found iterator, if not found then the null terminator is returned which is the tail
Time Complexity: O(n)
*/
sl_iterator_t SortedListFind(const s_list_t *list, sl_iterator_t from, sl_iterator_t to,const void *data);
/****************************************************************************/
/*
Description: find in list according to match func
Parameters: 

			from -> find from iterator
			to -> find to iterator
			match -> match function signature
			param -> param to be adjusted in the match function
			
Return Value: Returnes the found iterator if not found then the null terminator is returned which is the tail
Time Complexity: O(n)
*/
sl_iterator_t SortedListFindIf(sl_iterator_t from, sl_iterator_t to, match_func_t match_func, const void *param);
/****************************************************************************/
/*
Description:  end of list == DoublyLinkedListEnd 
Parameters: 

			iterator -> The iterator to get next for

Return Value: returns next object, if iterator is the terminating null then the null terminator is returned
Time Complexity: O(1)
*/
sl_iterator_t SortedListNext(sl_iterator_t iterator);
/****************************************************************************/
/*
Description: end of list == DoublyLinkedListBegin 
Parameters: 

			iterator -> The iterator to get previous from

Return Value: returns the previous object
Time Complexity: O(1)
*/
sl_iterator_t SortedListPrev(const sl_iterator_t cur); 
/****************************************************************************/
/*
Description: retrives data
Parameters: 

			iterator -> the iterator to get data from

Return Value: iterators data field
Time Complexity:  O(1)
*/
void *SortedListGetData(sl_iterator_t iterator);
/****************************************************************************/
/*
Description: count nodes (valid nodes)
Parameters: 

				list -> The list pointer

Return Value: returns list object number
Time Complexity: O(n)
*/
size_t SortedListCount(const s_list_t *list); /* how many valid nodes */
/****************************************************************************/
/*
Description: empty or not
Parameters: 

				list -> The list pointer

Return Value: True(1) for empty list false(0) non empty list
Time Complexity: O(1)
*/
int SortedListIsEmpty(const s_list_t *list);
/****************************************************************************/
/*
Description: Is nodes match
Parameters: 

				iterator1 -> iterator1 to be matched
				iterator2 -> iterator2 to be matched

Return Value: True(1) for match nodes false(0) non-matching nodes
Time Complexity: O(1)
*/
int SortedListIsMatchNode(const sl_iterator_t iterator1, const sl_iterator_t iterator2 );
/****************************************************************************/
/*
Description: Operation func manipulating *parameter on the data from_iter to to_iter 
as long the operation func return 0 the func continue.  
Parameters: 

				operation_func -> function to be operated "from - to" iterators
				from -> find from iterator
			    to -> to iterator
			    parameter -> parameter to be adjusted in the match function

Return Value:  returns the last value it stoped with
Time Complexity: O(n)
*/
int SortedListForEach(sl_operation_func_t operation_func, sl_iterator_t from, sl_iterator_t to, void *parameter);
/****************************************************************************/
/*
Description: Merging source list into destination list, destination list will contain all the object sorted
Parameters: 

			dest_list -> destination list
			src_list -> source list will remain empty

Return Value: void
Time Complexity: O(n)
*/
void SortedListMerge(s_list_t *dest_list, s_list_t *src_list);





/****************************************************************************/
#endif
