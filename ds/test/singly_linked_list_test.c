#include <stdio.h>/*Required for standard input ouput*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include "singly_linked_list.h"/*Required for our library functions*/

/*
* Prints all the elements in the list.
*/
static void PrintSll(const sll_t *list);

/*
* Sets all elements in the list to data.
*/
static void SetAllSll(const sll_t *list, void *data);

/*
* returns the iterator to the element at index.
*/
static sll_iterator_t GetIterAt(const sll_t *list, size_t index);

/*
* A function to add parameter to data.
*/
static int Add(void *data, void *parameter);

/*
* A function to set data = data * parameter.
*/
static int Multiply(void *data, void *parameter);

/*
* A function that matches if data == parameter.
*/
static int Match(const void *data, void *parameter);

int main()
{
	sll_iterator_t iter = NULL;
	size_t i = 0;
	int add_val = 3;
	int mult_val = 2;
	int match_val = 20;
	int value = -1;
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr2[] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 110};
	
	sll_t *list = SinglyLinkedListCreate();
	sll_t *list2 = SinglyLinkedListCreate();
	
	printf("Count: %lu\n", SinglyLinkedListCount(list));
	if(SinglyLinkedListIsEmpty(list))
	{
		puts("List is empty.");
	}
	else
	{
		puts("ERROR! List should be empty.");
	}
	
	
	for (i = 0; i < 10; i++)
	{
		SinglyLinkedListInsert(SinglyLinkedListEnd(list), &arr[i]);
	}
	
	for (i = 0; i < 10; i++)
	{
		SinglyLinkedListInsert(SinglyLinkedListEnd(list2), &arr2[i]);
	}
	PrintSll(list);
	puts("list 2 has: ");
	PrintSll(list2);
	
	printf("Count: %lu\n", SinglyLinkedListCount(list));
	if(!SinglyLinkedListIsEmpty(list))
	{
		puts("List isn't empty.");
	}
	else
	{
		puts("ERROR! List shouldn't be empty.");
	}
	
	SinglyLinkedListInsert(GetIterAt(list, 5), &value);
	
	PrintSll(list);
	printf("Count: %lu\n", SinglyLinkedListCount(list));
	
	SinglyLinkedListRemove(GetIterAt(list, 5));
	
	PrintSll(list);
	printf("Count: %lu\n", SinglyLinkedListCount(list));
	
	puts("\nUse ForEach on the list with a function that adds 3 to every node data:");
	SinglyLinkedListForEach(Add, 
							SinglyLinkedListBegin(list), 
							SinglyLinkedListEnd(list), 
							&add_val);
	PrintSll(list);
	
	puts("\nUse ForEach on the list with a function that multiplies every node data by 2:");
	SinglyLinkedListForEach(Multiply, 
							SinglyLinkedListBegin(list), 
							SinglyLinkedListEnd(list), 
							&mult_val);
	PrintSll(list);
	
	puts("\nFind the first node with value 20, from beginning to end:");
	iter = SinglyLinkedListFind(Match, 
								SinglyLinkedListBegin(list), 
								SinglyLinkedListEnd(list), 
								&match_val);
	printf("The returned iterator data is: %d\n", *((int *)SinglyLinkedListGetData(iter)));
	
	puts("\nFind the first node with value 20, from beginning to 6th node:");
	iter = SinglyLinkedListFind(Match, 
								SinglyLinkedListBegin(list), 
								GetIterAt(list, 5), 
								&match_val);
	puts("\nWe shouldn't find anything so the data in the returned iterator should be 18:");
	printf("The returned iterator data is: %d\n", *((int *)SinglyLinkedListGetData(iter)));
	
	puts("\nSet all nodes data to -1:");
	SetAllSll(list, &value);
	PrintSll(list);
	SinglyLinkedListAppend(list, list2);
	for (i = 0; i < 20; i++)
	{
		SinglyLinkedListRemove(SinglyLinkedListBegin(list));
		PrintSll(list);
		printf("Count: %lu\n", SinglyLinkedListCount(list));
	}
	printf("number of nodes in list2 after appending to list1: %lu\n",SinglyLinkedListCount(list2));
	SinglyLinkedListDestroy(list);
	
	return 0;
}

void PrintSll(const sll_t *list)
{
	sll_iterator_t iter = SinglyLinkedListBegin(list);
	while (SinglyLinkedListNext(iter))
	{
		printf("%d ", *((int *)SinglyLinkedListGetData(iter)));
		iter = SinglyLinkedListNext(iter);
	}
	printf("\n");
}

void SetAllSll(const sll_t *list, void *data)
{
	sll_iterator_t iter = SinglyLinkedListBegin(list);
	while (SinglyLinkedListNext(iter))
	{
		SinglyLinkedListSetData(iter, data);
		iter = SinglyLinkedListNext(iter);
	}
}

sll_iterator_t GetIterAt(const sll_t *list, size_t index)
{
	sll_iterator_t iter = SinglyLinkedListBegin(list);
	while (index)
	{
		iter = SinglyLinkedListNext(iter);
		--index;
	}
	
	return iter;
}

int Add(void *data, void *parameter)
{
	*((int *)data) += *((int *)parameter);
	return 0;
}

int Multiply(void *data, void *parameter)
{
	*((int *)data) *= *((int *)parameter);
	return 0;
}

int Match(const void *data, void *parameter)
{
	return (*((int *)data) == *((int *)parameter));
}
