#include <stdio.h>
#include <stdlib.h>/*for rand*/
#include <time.h> /*for clock*/
#include "search.h"
#include "../../ds/include/utl.h"
/****************************************************************************/
#define TIME_DIFF(start, end) (((double)((end) - (start))) / CLOCKS_PER_SEC)
#define SIZE1 1800000 /*almost sorted*/
#define SIZE2 25000 /*sorted*/
#define SIZE3 50000 /*unsorted array*/

#define SIZE4 50000 /*almost sorted*/
#define SIZE5 25000 /*sorted*/
#define SIZE6 50000 /*unsorted array*/
/****************************************************************************/
typedef int (*compar_t)(const void *, const void*);
typedef int(*func_t)(const int *arr, int last_index, int data);

/****************************************************************************/
void CreateSorted(int *arr, size_t size, int upper, int lower);

void PrintArr(const int *arr, size_t size);
int IsSorted(const int *arr, size_t size);
int cmpfunc (const void *a, const void *b);

void BinarySearchTest(void);
void SearchTest1 (func_t func, int index_to_find ,char *search_kind);

/****************************************************************************/
/****************************************************************************/
int main()
{
	printf ("%s*****************************************\n",PURPLE);
	printf ("%s---------------SEARCH tests---------------\n",PURPLE);
	printf ("%s*****************************************\n",PURPLE);

	BinarySearchTest();
	SearchTest1(BinarySearchIter, SIZE1/2,"BinarySearchIter");
	SearchTest1(BinarySearchRec, SIZE1/2,"BinarySearchRec");

	printf ("%s*****************************************\n",PURPLE);
	printf ("%s---------------SEARCH ended----------------\n",PURPLE);
	printf ("%s*****************************************\n",PURPLE);
	return 0;
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void BinarySearchTest(void)
{
	int arr[10] = {1, 10, 45, 32, 68, 88, 945, 1234, 234567, 58673923};
	int val = 88;
	int index = 0;

	index = BinarySearchRec(arr, 9, val);

	printf(DEFAULT"the index is = %d \n", index);

}
/****************************************************************************/
/****************************************************************************/
void CreateSorted(int *arr, size_t size, int upper, int lower)
{
	size_t i = 0;
    srand(time(NULL)); /* Seed random generator. */

    for (i = 0; i < size ; ++i)
    {
        arr[i] = (rand() % (upper - lower + 1)) + lower;
    }
	qsort(arr, size, sizeof(int), cmpfunc);
}
/****************************************************************************/
/****************************************************************************/
void PrintArr(const int *arr, size_t size)
{
    for (; size > 0; --size)
    {
        printf("%d ", *arr);
        ++arr;
    }
    puts("");
}
/****************************************************************************/
/****************************************************************************/
int IsSorted(const int *arr, size_t size)
{
	size_t i = 0;

	for(; i < size - 1 ; ++i )
	{
		if(arr[i] > arr[i + 1])
		{
			return 0;
		}

	}
	return 1;
}
/****************************************************************************/
/****************************************************************************/
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


void SearchTest1 (func_t func, int index_to_find ,char *search_kind)
{
	int arr[SIZE1] = {0};
	clock_t start = 0;
	clock_t end = 0;
	double time_taken = 0;
	int index = 0;

	printf (CYAN"--------------%s-------------\n",search_kind );

	printf (WHITE"ARR(sorted array): size = %d, range = {%d -> %d}\n",SIZE1, SIZE1/2, -SIZE1/2 );
	printf (WHITE"---------------------------------------------------------\n");
	CreateSorted(arr, SIZE1, SIZE1/2, -SIZE1/2);
	start = clock();
	index = func(arr, SIZE1 - 1,arr[index_to_find] );
	end = clock();
	time_taken = TIME_DIFF(start, end);
	printf(YELLOW"time_taken = "GREEN"%.7f \n"DEFAULT, time_taken);
	printf(YELLOW"index = "GREEN"%d \n"DEFAULT, index);

	if ( arr[index_to_find] == arr[index])
	{
		printf(GREEN"SUCCESS\n");
	}
	else
	{
		printf(RED"FAILURE\n"DEFAULT);
	}
}
