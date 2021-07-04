#include <stdio.h> /* For printf and puts. */

#include "sorted_list.h" /* For function declarations. */
#include "utl.h" /* For utilities. */

/*
* Prints all the elements in the list.
*/
static void PrintSl(const s_list_t *list);

/*
* returns the iterator to the element at index.
*/
static sl_iterator_t GetIterAt(const s_list_t *list, size_t index);

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
/*
static int Match(const void *data, const void *parameter);
*/

/*
* A function that matches if data % parameter == 0.
*/
static int MatchDivisible(const void *data, const void *parameter);

static int Comparator(const void *data1, const void *data2);

int main()
{
	#ifdef NDEBUG
		sl_iterator_t iter = NULL;
	#else
		sl_iterator_t iter = {NULL, NULL};
	#endif
	
	size_t i = 0;
	int add_val = 3;
	int mult_val = 2;
	int match_val = 8;
	int value = -1;
	int div_val = 3;
	int popped_val = 0;
	int arr[] = {10, 9, 4, 3, 5, 6, 8, 7, 2, 1};
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr3[] = {8, 1, 5, 9, 2};
	int arr4[] = {4, 10, 3, 6, 7};
	int arr_res[] = {8, 10, 12, 14, 16, 18, 20, 22, 24, 26};
	int arr_res1[] = {8, 10, 12, 14, 18, 20, 22, 24, 26};
	int arr_res2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	
	s_list_t *list1 = NULL;
	s_list_t *list2 = NULL;
	s_list_t *list = SortedListCreate(Comparator);
	
	puts(BLUE"IsEmpty tests:");
	if(SortedListIsEmpty(list) && 0 == SortedListCount(list))
	{
		printf(GREEN"PASS\n");
	}
	else
	{
		printf(RED"ERROR! List should be empty.\n");
		printf("Count: %lu\n", SortedListCount(list));
		PrintSl(list);
	}
	
	
	for (i = 0; i < 10; i++)
	{
		SortedListInsert(list, &arr[i]);
	}
	
	if(!SortedListIsEmpty(list) && 10 == SortedListCount(list))
	{
		printf(GREEN"PASS\n");
	}
	else
	{
		printf(RED"ERROR! List shouldn't be empty.\n");
		printf("Count: %lu\n", SortedListCount(list));
		PrintSl(list);
	}
	
	puts(BLUE"\nTest if resulting list is sorted:");
	for (i = 0; i < 10; i++)
	{
		if (arr1[i] != *((int *)SortedListGetData(GetIterAt(list, i))))
		{
			printf(RED"ERROR! Value at index %lu should be %d\n.", i, arr_res[i]);
			printf("Count: %lu\n", SortedListCount(list));
			PrintSl(list);
		}
	}
	printf(GREEN"PASS\n");
	
	puts(BLUE"\nUse ForEach on the list with a function that adds 3 to every node data.");
	SortedListForEach(Add, 
					SortedListBegin(list), 
					SortedListEnd(list), 
					&add_val);
	
	puts(BLUE"Use ForEach on the list with a function that multiplies every node data by 2.");
	SortedListForEach(Multiply, 
					SortedListBegin(list), 
					SortedListEnd(list), 
					&mult_val);
	
	for (i = 0; i < 10; i++)
	{
		if (arr_res[i] != *((int *)SortedListGetData(GetIterAt(list, i))))
		{
			printf(RED"ERROR! Value at index %lu should be %d\n.", i, arr_res[i]);
			printf("Count: %lu\n", SortedListCount(list));
			PrintSl(list);
		}
	}
	printf(GREEN"PASS\n");
	
	printf(BLUE"\nInsert -1:\n");
	SortedListInsert(list, &value);
	if (-1 != *((int *)SortedListGetData(SortedListBegin(list))))
	{
		printf(RED"ERROR! value at begin should be -1.\n");
		printf("Count: %lu\n", SortedListCount(list));
		PrintSl(list);
	}
	else
	{
		printf(GREEN"PASS\n");
	}
	
	puts(BLUE"\nRemove at index 5:");
	SortedListRemove(GetIterAt(list, 5));
	if (18 != *((int *)SortedListGetData(GetIterAt(list, 5))))
	{
		printf(RED"ERROR! value at index 5 should be 18.\n");
		printf("Count: %lu\n", SortedListCount(list));
		PrintSl(list);
	}
	else
	{
		printf(GREEN"PASS\n");
	}
	
	puts(BLUE"\nPopFront:");
	if (-1 != *((int *)SortedListPopFront(list)))
	{
		printf(RED"ERROR! Popped value should be -1.\n");
		printf("Count: %lu\n", SortedListCount(list));
		PrintSl(list);
	}
	else
	{
		printf(GREEN"PASS\n");
	}
	
	puts(BLUE"\nFind the first node divisible by 3, from beginning to end:");
	iter = SortedListFindIf(SortedListBegin(list), 
							SortedListEnd(list),
							MatchDivisible,
							&div_val);
	match_val = 12;
	if (match_val != *((int *)SortedListGetData(iter)))
	{
		printf(RED"ERROR! The returned value %d should be %d.", 
		*((int *)SortedListGetData(iter)), match_val);
		printf("Count: %lu\n", SortedListCount(list));
		PrintSl(list);
	}
	else
	{
		printf(GREEN"PASS\n");
	}
	
	match_val = 14;
	puts(BLUE"\nFind the first node with value 14, from beginning to end:");
	iter = SortedListFind(list, 
						SortedListBegin(list), 
						SortedListEnd(list), 
						&match_val);
	if (match_val != *((int *)SortedListGetData(iter)))
	{
		printf(RED"ERROR! The returned value %d should be %d.", 
		*((int *)SortedListGetData(iter)), match_val);
		printf("Count: %lu\n", SortedListCount(list));
		PrintSl(list);
	}
	else
	{
		printf(GREEN"PASS\n");
	}
	
	puts(BLUE"\nPopBack until empty:");
	i = SortedListCount(list) - 1;
	while (!SortedListIsEmpty(list))
	{
		popped_val = *((int *)SortedListPopBack(list));
		if (arr_res1[i] != popped_val)
		{
			printf(RED"ERROR! The popped value %d should be %d.\n", popped_val, arr_res1[i]);
			printf("Count: %lu\n", SortedListCount(list));
			PrintSl(list);
		}
		--i;
	}
	printf(GREEN"PASS\n");
	
	SortedListDestroy(list);
	
	list1 = SortedListCreate(Comparator);
	list2 = SortedListCreate(Comparator);
	
	for (i = 0; i < 5; i++)
	{
		SortedListInsert(list1, &arr3[i]);
		SortedListInsert(list2, &arr4[i]);
	}
	
	puts(BLUE"\nlist1 and list2:");
	printf(YELLOW);
	PrintSl(list1);
	PrintSl(list2);

	SortedListMerge(list1, list2);
	
	puts(BLUE"\nMerge list1 and list2, list1 is the result of the merge, list2 should be emptied:");
	
	for (i = 0; i < 10; i++)
	{
		if (arr1[i] != *((int *)SortedListGetData(GetIterAt(list1, i))))
		{
			printf(RED"ERROR! Value at index %lu should be %d\n", i, arr1[i]);
			printf("Count: %lu\n", SortedListCount(list1));
			PrintSl(list1);
		}
	}
	if (SortedListIsEmpty(list2) && (10 == SortedListCount(list1)))
	{
		
		printf(GREEN"PASS\n");
		printf("List1:\n");
		PrintSl(list1);
	}
	else
	{
		printf(RED"ERROR! list2 should be empty and list1 should have 10 elements.");
		printf("List1 count: %lu\n", SortedListCount(list1));
		PrintSl(list1);
		printf("List2 count: %lu\n", SortedListCount(list2));
		PrintSl(list2);
	}
	
	puts(BLUE"\nPopFront until empty:");
	i = SortedListCount(list1) - 1;
	while (!SortedListIsEmpty(list1))
	{
		popped_val = *((int *)SortedListPopFront(list1));
		if (arr_res2[i] != popped_val)
		{
			printf(RED"ERROR! The popped value %d should be %d.\n", popped_val, arr_res2[i]);
			printf("Count: %lu\n", SortedListCount(list1));
			PrintSl(list1);
		}
		--i;
	}
	printf(GREEN"PASS\n");

	SortedListDestroy(list1);
	SortedListDestroy(list2);
	
	puts(DEFAULT);
	
	return 0;
}

void PrintSl(const s_list_t *list)
{
	#ifdef NDEBUG
		sl_iterator_t iter = SortedListBegin(list);
		while (SortedListNext(iter))
		{
			printf("%d ", *((int *)SortedListGetData(iter)));
			iter = SortedListNext(iter);
		}
		printf("\n");
	#else
		sl_iterator_t iter = SortedListBegin(list);
		while (SortedListNext(iter).internal_itr)
		{
			printf("%d ", *((int *)SortedListGetData(iter)));
			iter = SortedListNext(iter);
		}
		printf("\n");
	#endif
}

sl_iterator_t GetIterAt(const s_list_t *list, size_t index)
{
	sl_iterator_t iter = SortedListBegin(list);
	while (index)
	{
		iter = SortedListNext(iter);
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

int MatchDivisible(const void *data, const void *parameter)
{
	return (*((int *)data) % *((int *)parameter) == 0);
}

int Comparator(const void *data1, const void *data2)
{
	return *((int *)data1) - *((int *)data2); 
}

/*
int Match(const void *data, const void *parameter)
{
	return (*((int *)data) == *((int *)parameter));
}
*/
