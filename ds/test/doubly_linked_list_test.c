#include <stdio.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "utl.h"


/* https://wb.infinitylabs.co.il/boards/h0acktQM0hYI8iIIfEn5r1Z1NN03V17MSxd6OAvTgSc- */

void test();

int main()
{
	printf ("%s*****************************************\n",RED);
	printf ("%sDaniel Z tests - the best you'll ever get\n",RED);
	printf ("%s*****************************************\n",RED);

	test();

	printf ("%s*****************************************\n",RED);
	printf ("%s---------------Test ended----------------\n",RED);
	printf ("%s*****************************************\n%s",RED,DEFAULT);

	return 0;
}

void test()
{
	/*size_t res = 0;*/
	int i = 5;
	int y = 7;
	int z = 8;
	dll_iterator_t ptr  = NULL;
	dll_iterator_t ptr2 = NULL;
/****************************************************************************/
	dll_t *list = DoublyLinkedListCreate();
	printf ("%sDoubly linked list Created\n",CYAN);
/****************************************************************************/
	printf ("%sIsEmpty - %s%d\n",WHITE,YELLOW ,DoublyLinkedListIsEmpty(list));
	printf ("%sInsert i = 5\n",CYAN);
	ptr = DoublyLinkedListInsert( DoublyLinkedListEnd(list), (int*)(&i) );
	printf("%si = %d\n",GREEN, (*(int*)DoublyLinkedListGetData(ptr) ) );
	printf("%scount = %lu\n",GREEN,DoublyLinkedListCount(list));

	printf ("%sPushBack y = 7\n",CYAN);
	ptr = DoublyLinkedListPushBack(list, (void*)(&y) );
	printf("%sy = %d\n",GREEN,(*(int*)DoublyLinkedListGetData(ptr) ) );
	printf("%scount = %lu\n",GREEN,DoublyLinkedListCount(list));

	printf ("%sInsert z = 8\n",CYAN);
	ptr = DoublyLinkedListInsert( DoublyLinkedListEnd(list), (int*)(&z) );
	printf("%sz = %d\n",GREEN ,(*(int*)DoublyLinkedListGetData(ptr) ) );
	printf("%scount = %lu\n",GREEN,DoublyLinkedListCount(list));
/****************************************************************************/
	printf ("%sInsert z = 8\n",CYAN);
	ptr2 = DoublyLinkedListNext(DoublyLinkedListBegin(list));
	ptr = DoublyLinkedListInsert( ptr2, (int*)(&z) );
	printf("%d\n", (*(int*)DoublyLinkedListGetData(ptr) ) );

/****************************************************************************/
	DoublyLinkedListDestroy(list);



}
