/********************************************************************************
 *  FILENAME:  sorts_test.c  DEVELOPER: Daniel Zaken   TEAM: Blue
 *
 *  Reviwer:   Michael
 *
 *  PURPOSE:   Function for sorting lists
 *
 *******************************************************************************/

#include <stdio.h>		/* printf() */
#include <stdlib.h>		/* srand(), qsort(), malloc(), free() */
#include <time.h>		/* time_t */

#include "sorts.h"

#define SMALL_ARRAY (100)
#define BIG_ARRAY (50000)
#define FIVE_K_ARRAY (5000)

/* Initializes array with random values */
static void RandomizeArr(int *arr, size_t arr_size);

/* Initializes array with negative random values */
static void RandomizeArrNegative(int *arr, size_t arr_size);

/* Initializes array with half negative and half positive random values */
static void RandomizeArrNegativePositive(int *arr, size_t arr_size);

/* Initializes array in reverse sorted order */
static void ReverseSortedArr(int *arr, size_t arr_size);

/* Initializes array in sorted order, except first & last that're swapped */
static void NearlySortedArr(int *arr, size_t arr_size);

/* Initializes array with random values between upper & lower */
void CreateRandomArr(int *arr, size_t size, int upper, int lower);

/* Prints if array sorting succeeded or failed */
static int SortTest(int *arr, size_t arr_size, int line);

/* Benchmark function for time comparison */
static void Qsort(int *arr, size_t arr_size);
static int cmp_func(const void * a, const void * b);

/* static arrays for tests */
static int small_random[SMALL_ARRAY] = {0};
static size_t small_random_size = SMALL_ARRAY;

static int arr[BIG_ARRAY] = {0};
static size_t arr_size = BIG_ARRAY;

static int test_arr[FIVE_K_ARRAY] = {0};

/* Time evaluation components */
static clock_t start_time = 0;
static clock_t end_time = 0;
static double cpu_time_used = 0;

/*****************************************************************************/

void Test1(char *sort_name, void (*fun_ptr)(int *arr, size_t arr_size));
void Test2(char *sort_name, int (*fun_ptr)(int *arr, size_t arr_size));
void Test3(char *sort_name);
void Test4(char *sort_name);

void SortGenericTest(char *sort_name,
int (*fun_ptr)(void *arr, size_t arr_size, size_t element_size,
											cmp_func_t cmp_func));

int main()
{
	void (*bubble_ptr)(int *arr, size_t arr_size) = &BubbleSort;
	void (*insertion_ptr)(int *arr, size_t arr_size) = &InsertionSort;
	void (*selection_ptr)(int *arr, size_t arr_size) = &SelectionSort;

	int (*counting_ptr)(int *arr, size_t arr_size) = &CountingSort;
	int (*radix_ptr)(int *arr, size_t arr_size) = &RadixSort;
	int (*merge_ptr)(int *arr, size_t arr_size) = &MergeSort;

	int (*merge_generic_ptr)(void *arr, size_t arr_size, size_t element_size,
									cmp_func_t cmp_func) = &MergeSortGeneric;

	int (*quick_generic_ptr)(void *base, size_t nmemb, size_t size,
							cmp_func_t cmp_func) = &QuickSortGeneric;

    /* Use current time as seed for random generator */
    srand(time(NULL));

	Test1("BubbleSort", bubble_ptr);
	Test1("InsertionSort", insertion_ptr);
	Test1("SelectionSort", selection_ptr);

	Test2("CountingSort", counting_ptr);
	Test2("RadixSort", radix_ptr);

	Test3("CountingSort");

	Test4("RadixSort");

	Test2("MergeSort", merge_ptr);

	SortGenericTest("MergeSortGeneric", merge_generic_ptr);

	SortGenericTest("QuickSortGeneric", quick_generic_ptr);

    return 0;
}

void Test1(char *sort_name, void (*fun_ptr)(int *arr, size_t arr_size))
{
	size_t n_fails = 0;
	size_t n_tests = 0;

	printf("-----------------%s TEST1 START-------------------\n\n", sort_name);

	start_time = 0;
	end_time = 0;
	RandomizeArr(small_random, small_random_size);

	printf("1. small random array sort.\n");
	Qsort(small_random, small_random_size);

	/* calculates sorting time */
    start_time = clock();
    (*fun_ptr)(small_random, small_random_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for small random array: %f\n", cpu_time_used);

	n_fails += SortTest(small_random, small_random_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArr(arr, arr_size);

	printf("2. random array sort.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    (*fun_ptr)(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	qsort(arr, arr_size, sizeof(int), cmp_func);

	printf("3. already sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    (*fun_ptr)(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for already sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArrNegative(arr, arr_size);

	printf("4. random negative array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    (*fun_ptr)(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random negative array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArrNegativePositive(arr, arr_size);

	printf("5. random half negative & half positive array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    (*fun_ptr)(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random half negative & half positive"
     										"array.: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	ReverseSortedArr(arr, arr_size);

	printf("6. reverse sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    (*fun_ptr)(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for reverse sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	NearlySortedArr(arr, arr_size);

	printf("7. nearly sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    (*fun_ptr)(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for nearly sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	printf("%s tests success rate: %d%%\n", sort_name,
	((int)(((n_tests - n_fails) / ((float)n_tests)) * 100)));

	printf("\n-----------------%s TEST1 END-------------------\n\n", sort_name);
}

void Test2(char *sort_name, int (*fun_ptr)(int *arr, size_t arr_size))
{
	size_t n_fails = 0;
	size_t n_tests = 0;

	printf("-----------------%s TEST2 START-------------------\n\n", sort_name);

	start_time = 0;
	end_time = 0;
	RandomizeArr(small_random, small_random_size);

	printf("1. small random array sort.\n");
	Qsort(small_random, small_random_size);

	/* calculates sorting time */
    start_time = clock();
    n_fails += (*fun_ptr)(small_random, small_random_size);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for small random array: %f\n", cpu_time_used);

	n_fails += SortTest(small_random, small_random_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArr(arr, arr_size);

	printf("2. random array sort.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)(arr, arr_size);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	qsort(arr, arr_size, sizeof(int), cmp_func);

	printf("3. already sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
     n_fails += (*fun_ptr)(arr, arr_size);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for already sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArrNegative(arr, arr_size);

	printf("4. random negative array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)(arr, arr_size);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random negative array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArrNegativePositive(arr, arr_size);

	printf("5. random half negative & half positive array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)(arr, arr_size);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random half negative & half positive"
    										" array.: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	ReverseSortedArr(arr, arr_size);

	printf("6. reverse sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)(arr, arr_size);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for reverse sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	NearlySortedArr(arr, arr_size);

	printf("7. nearly sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)(arr, arr_size);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for nearly sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	printf("%s tests success rate: %d%%\n", sort_name,
	((int)(((n_tests - n_fails) / ((float)n_tests)) * 100)));

	printf("\n-----------------%s TEST2 END-------------------\n\n", sort_name);
}

void Test3(char *sort_name)
{
	printf("-----------------%s TEST3 START-------------------\n\n", sort_name);

	start_time = 0;
	end_time = 0;
	CreateRandomArr(test_arr, FIVE_K_ARRAY, 1000, 1);
	Qsort(test_arr, FIVE_K_ARRAY);

	start_time = clock();
    CountingSort(test_arr, FIVE_K_ARRAY);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CountingSort time for random array (5k elements) in the range of"
    										" 1 to 1000: %f\n", cpu_time_used);

    printf("\n-----------------%s TEST3 END-------------------\n\n", sort_name);
}

void Test4(char *sort_name)
{
	printf("-----------------%s TEST4 START-------------------\n\n", sort_name);

	start_time = 0;
	end_time = 0;
	CreateRandomArr(test_arr, FIVE_K_ARRAY, 1000000, -100);
	Qsort(test_arr, FIVE_K_ARRAY);

	start_time = clock();
    RadixSort(test_arr, FIVE_K_ARRAY);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("RadixSort time for random array (5k elements) in the range of -100"
    										" to 1000000: %f\n", cpu_time_used);

    printf("\n-----------------%s TEST4 END-------------------\n\n", sort_name);
}

void SortGenericTest(char *sort_name,
int (*fun_ptr)(void *arr, size_t arr_size, size_t element_size,
											cmp_func_t cmp_func))
{
	size_t n_fails = 0;
	size_t n_tests = 0;

	printf("-----------------%s TEST START-------------------\n\n", sort_name);

	start_time = 0;
	end_time = 0;
	RandomizeArr(small_random, small_random_size);

	printf("1. small random array sort.\n");
	Qsort(small_random, small_random_size);

	/* calculates sorting time */
    start_time = clock();
    n_fails += (*fun_ptr)((void *)small_random, small_random_size, sizeof(int),
    																 cmp_func);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for small random array: %f\n", cpu_time_used);

	n_fails += SortTest(small_random, small_random_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArr(arr, arr_size);

	printf("2. random array sort.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)((void *)arr, arr_size, sizeof(int), cmp_func);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	qsort(arr, arr_size, sizeof(int), cmp_func);

	printf("3. already sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
     n_fails += (*fun_ptr)((void *)arr, arr_size, sizeof(int), cmp_func);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for already sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArrNegative(arr, arr_size);

	printf("4. random negative array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)((void *)arr, arr_size, sizeof(int), cmp_func);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random negative array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	RandomizeArrNegativePositive(arr, arr_size);

	printf("5. random half negative & half positive array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)((void *)arr, arr_size, sizeof(int), cmp_func);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for random half negative & half positive"
    										" array.: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	ReverseSortedArr(arr, arr_size);

	printf("6. reverse sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)((void *)arr, arr_size, sizeof(int), cmp_func);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for reverse sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	start_time = 0;
	end_time = 0;
	NearlySortedArr(arr, arr_size);

	printf("7. nearly sorted array.\n");
	Qsort(arr, arr_size);

	start_time = clock();
    n_fails += (*fun_ptr)((void *)arr, arr_size, sizeof(int), cmp_func);
    end_time = clock();
    ++n_tests;
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting algorithm time for nearly sorted array: %f\n", cpu_time_used);

	n_fails += SortTest(arr, arr_size, __LINE__);
	++n_tests;

	printf("%s tests success rate: %d%%\n", sort_name,
	((int)(((n_tests - n_fails) / ((float)n_tests)) * 100)));

	printf("\n-----------------%s TEST END-------------------\n\n", sort_name);
}

/***********************static functions**************************************/

static void Qsort(int *arr, size_t arr_size)
{
   	int *temp_arr = NULL;
   	size_t i = 0;

   	temp_arr = (int *)malloc(arr_size * sizeof(int));

   	if (NULL == temp_arr)
	{
		printf("Qsort malloc failed");

		return;
	}

	for (i = 0; i < arr_size; ++i)
	{
		temp_arr[i] = arr[i];
	}

	start_time = 0;
	end_time = 0;

	start_time = clock();
	qsort(temp_arr, arr_size, sizeof(int), cmp_func);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Benchmark time (qsort): %f\n", cpu_time_used);

    free(temp_arr);
    temp_arr = NULL;
}

static int cmp_func (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}

static void RandomizeArr(int *arr, size_t arr_size)
{
   size_t i = 0;

   for (i = 0; i < arr_size; ++i)
    {
        arr[i] = rand() % BIG_ARRAY;
    }
}

static void RandomizeArrNegativePositive(int *arr, size_t arr_size)
{
   size_t i = 0;

   for (i = 0; i < arr_size; ++i)
    {
        arr[i] = (rand() % BIG_ARRAY);

        if (i % 2 == 0)
        {
        	arr[i] *= (-1);
        }
    }
}

static void RandomizeArrNegative(int *arr, size_t arr_size)
{
   size_t i = 0;

   for (i = 0; i < arr_size; ++i)
    {
        arr[i] = (-1) * (rand() % BIG_ARRAY);
    }
}

static void ReverseSortedArr(int *arr, size_t arr_size)
{
   int i = arr_size - 1;
   int j = 0;

   while (0 <= i)
   {
   		arr[i] = j;
   		++j;
   		--i;
   }
}

static void NearlySortedArr(int *arr, size_t arr_size)
{
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
    {
        arr[i] = i;
    }

	arr[0] = arr[arr_size - 1];
	arr[arr_size - 1] = 0;
}

static int SortTest(int *arr, size_t arr_size, int line)
{
	size_t i = 0;

	printf("Sorting algorithm test result: ");

	for (i = 0; i < arr_size - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Sorting test failed in line %d!\n\n", line);

			return (1);
		}
	}

	printf("Sorting test was successfull!\n\n");

	return (0);
}

void CreateRandomArr(int *arr, size_t size, int upper, int lower)
{
    size_t i = 0;

    /* Seed random generator */
    srand(time(NULL));

    for (i = 0; i < size; ++i)
    {
        *arr = (rand() % (upper - lower + 1)) + lower;
        ++arr;
    }
}

/* END OF FILE */
