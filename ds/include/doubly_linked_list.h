/********************************************************************************
 *  FILENAME: singly_linked_list.h  DEVELOPER: Daniel Zaken  TEAM: Blue         * 
 *                                                                              *
 *  REVIEWER: Nely Nehemia                                                      * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying & creating Doubly Linked List                   *
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_DOUBLY_LINKED_LIST_H__
#define __ILRD_DOUBLY_LINKED_LIST_H__ 

#include <stddef.h> /*required for size_t type*/

/****************************************************************************/

/* update:
Insert, PushFront, PushBack - returns the new node iterator
Remove - returns the next node iterator
Splice - returns the last spliced (the one before "to")
Find - returns the 1st one found
FindMultiple - returns the number of found elements
PopBack, PopFront - returns the data of the popped node
*/
typedef struct dll dll_t;
typedef struct dll_node *dll_iterator_t;

/****************************************************************************/

/* Function used to find a specific iterator, returns a 0 value int if data is not a match and a non-zero int value if it is.  */
typedef int(*match_func_t)(const void *data, const void *parameter ); 

/****************************************************************************/

/* Operation function applied to each value held in list according to range supplied to DoublyLinkedListForEach function. Operation function returns 0 if application of operation is to continue to the next value in the list, and a non-zero value otherwise. */
typedef int(*operation_func_t)(void *data, void *parameter); 

/****************************************************************************/
/*
Description: create Doubly LinkedList (allocating space for it)
Parameters: void
Return Value: pointer for the list
Time Complexity: O(1)
*/
dll_t *DoublyLinkedListCreate(void);
/****************************************************************************/
/* 
Description: Free program allocations 
Parameters: 

				list -> pointer for the list
				
Return Value: void
Time Complexity: O(n)
*/
void DoublyLinkedListDestroy(dll_t *list);
/****************************************************************************/
/*
Description: Retrives the first object first valid (after head)
Parameters: 

				list -> pointer for the list

Return Value: first valid object
Time Complexity:O(1)
*/
dll_iterator_t DoublyLinkedListBegin(const dll_t *list);
/****************************************************************************/
/*
Description: retrive last obj  (Null terminator)
Parameters: 

				list -> pointer for the list

Return Value: last object which contains nothing but null (null termiantor)
Time Complexity:O(1)
*/
dll_iterator_t DoublyLinkedListEnd(const dll_t *list);

/****************************************************************************/
/*
Description: insert before iterator if it doesnt succedes than it returns null terminator 
Parameters: 

				where -> iterator to insert before him
				data  -> the data to insert into the new object

Return Value: The new object was inserted
Time Complexity:amortized O(1)
*/
dll_iterator_t DoublyLinkedListInsert(dll_iterator_t where, void *data);
/****************************************************************************/
/*
Description: insert from back if it doesnt succedes than it returns null terminator 
Parameters: 

				list -> pointer for the list
				data  -> the data to insert into the new object	

Return Value: The new object was inserted
Time Complexity: O(1)
*/
dll_iterator_t DoublyLinkedListPushBack(dll_t *list, void * data); /* like insert */
/****************************************************************************/
/*
Description: insert from front if it doesnt succedes than it returns null terminator 
Parameters: 

				list -> pointer for the list
				data  -> the data to insert into the new object	

Return Value: The new object was inserted
Time Complexity: O(1)
*/
dll_iterator_t DoublyLinkedListPushFront(dll_t *list, void * data);
/****************************************************************************/
/*
Description: Pop retrive and removes user data.
Parameters: 

				list -> pointer for the list
				
Return Value: The data of the removed object
Time Complexity:O(1)
*/
void *DoublyLinkedListPopBack(dll_t *list); /*for before tail */

void *DoublyLinkedListPopFront(dll_t *list); /*pop after head */

/****************************************************************************/
/*
Description: remove and return next iterator in list
Parameters: 

				to_remove -> The iterator to be removed

Return Value: The next iterator
Time Complexity:O(1);
*/

dll_iterator_t DoublyLinkedListRemove( dll_iterator_t to_remove); 
/****************************************************************************/
/*
Description: find from between two iterators a match by a match function (from -> to [to_iterator not included])
Parameters: 

				match_func -> The match function signature
				from - > Start iterator
				to -> last iterator, not included in the matching
				parameter -> parameter to be used with match function 
				output_list -> if desiered a list of matching could be returned by using the FindMultiple
							   in order for this to work you will need to create a new list and insert a pointer [output_list]

Return Value: Retrievs the first matching iterator according to match function which was inserted,
			  or a number of matching which inserted into a list (by using Find Multiple).
			  
Time Complexity:O(n)
*/

/*return the matched iterator*/
dll_iterator_t DoublyLinkedListFind(match_func_t match_func, dll_iterator_t from,
 dll_iterator_t to,const void *parameter);
 
/* return lists of the found match iterators */
int DoublyLinkedListFindMultiple(match_func_t match_func, dll_iterator_t from,
 dll_iterator_t to,const void *parameter,dll_t * output_list); /* Returns how many found */
/****************************************************************************/
/*
Description: retrive next/previous available iterator
Parameters: 

				iterator -> itertor to get next from or prevoius from
				
Return Value: returns the next/previous iterator, beware using next function on
			  the null terminator or previous on the first object causes undefined behaviour
			  
Time Complexity:O(1)
*/

dll_iterator_t DoublyLinkedListNext(const dll_iterator_t iterator);/* end of list == DoublyLinkedListEnd*/

dll_iterator_t DoublyLinkedListPrev(const dll_iterator_t iterator);/* end of list == DoublyLinkedListBegin */

/****************************************************************************/
/*
Description: retrives stored data from iterator
Parameters: 

				iterator -> The iterator which holds the desiered data

Return Value: The data of the iterator
Time Complexity:O(1)
*/
void *DoublyLinkedListGetData(dll_iterator_t iterator);
/****************************************************************************/
/*
Description: Count the number of valid object in the list, excluding null terminator 
Parameters: 

				list -> pointer for the list

Return Value: The size of the list
Time Complexity:O(n)
*/
size_t DoublyLinkedListCount(const dll_t *list);
/****************************************************************************/
/*
Description: Check if the list is empty?
Parameters: 

				list -> pointer for the list

Return Value:  Returns True/False
Time Complexity:O(1)
*/
int DoublyLinkedListIsEmpty(const dll_t *list);
/****************************************************************************/
/*
Description: matches between nodes addresses 
Parameters: 

				iterator1 -> node1 to be mayched with node2
				iterator2 -> node2 to be matched with node1

Return Value: Returns True/False
Time Complexity:O(1)
*/
int DoublyLinkedListIsMatchNode( const dll_iterator_t iterator1, const dll_iterator_t iterator2 );
/****************************************************************************/
/*
Description: applying operation func in range from iterator ("from") to iterator ("to") [to_iterator not included]
Parameters: 

				operation_func -> The operation function signature
				from - > Start iterator
				to -> last iterator, wont be operated
				parameter -> parameter to be used with operation function 

Return Value: as long the func return 0 the operation continues otherwise stops. ***extra description at typedef declaration ****
Time Complexity:O(n)
*/
int DoublyLinkedListForEach(operation_func_t operation_func, dll_iterator_t from, dll_iterator_t to, void *parameter);
/****************************************************************************/
/*
Description:  Splicing from list2 by range into list1
Parameters: 

				where -> The spliced range from list2 enters previous "where" iterator.
				from -> The first iterator of the range to be spliced from list2.
				to -> The last iterator of the range to be spliced from list2, this object though is not included in the splicing.				
	
Return Value:  return the last spliced ( before end )
Time Complexity: O(1)
*/
dll_iterator_t DoublyLinkedListSplice(dll_iterator_t where, dll_iterator_t from, dll_iterator_t to);

/****************************************************************************/
#endif
