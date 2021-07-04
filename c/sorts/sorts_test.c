
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

#define MASSIVE_ARRAY 50
#define BLACK "\033[30;1m"
#define RED "\033[31;1m"
#define GREEN "\033[32;1m"
#define YELLOW "\033[33;1m"
#define BLUE "\033[34;1m"
#define PURPLE "\033[35;1m"
#define CYAN "\033[36;1m"
#define WHITE "\033[37;1m"
#define DEFAULT "\x1b[0;0m"

void INIT(void);
int random_array[MASSIVE_ARRAY];
int random_arr_qsort[MASSIVE_ARRAY];
int best_array[MASSIVE_ARRAY];
int best_arr_qsort[MASSIVE_ARRAY];
int worst_array[MASSIVE_ARRAY];
int worst_arr_qsort[MASSIVE_ARRAY];


typedef void(*f_ptr)(int*, size_t);
typedef int(*f_ptr2)(int*,size_t);
typedef int(*f_ptr3)(void*,size_t,size_t, cmp_func_t);

static void Print(int *arr, size_t size);
void TestComparison(f_ptr func );
int cmpfunc (const void * a, const void * b);
void TestLinear(f_ptr2 func);
int IsSorted(int *arr, size_t size);
void TestQS(f_ptr3 func);

int main()
{

	char chose = '0';

	f_ptr chosen = NULL;
	f_ptr2 chosen2 = NULL;
	f_ptr3 chosen3 = NULL;
	int arr[] = {38,100,43,3,10,82,9,100,102,103,-60,1000,2000,5000,8000};

	puts("which comparison sorting function would you like to test?");
	puts("\tFor bubble sort enter a");
	puts("\tFor selection sort enter b");
	puts("\tFor insertion sort enter c");
	puts("\tFor counting sort enter d");
	puts("\tFor radix sort enter e");
	puts("\tFor merge sort enter f");
	puts("\tFor quick sort enter g");
	puts("\n\nPRESS ESCAPE TO EXIT\n");
	chose = 0;

	while(chose != 27)
	{
		chose = getchar();

		switch(chose)
		{
			case 'a':
				chosen = BubbleSort;
				TestComparison(chosen);
				break;
			case 'b':
				chosen = SelectionSort;
				TestComparison(chosen);
				break;
			case 'c':
				chosen = InsertionSort;
				TestComparison(chosen);
				break;
			case 'd':
				chosen2 = CountingSort;
				TestLinear(chosen2);
				break;
			case 'e':
				chosen2 = RadixSort;
				TestLinear(chosen2);
				break;
			case 'f':
				chosen2 = MergeSort;
				TestLinear(chosen2);
				break;
			case 'g':
				chosen3 = QuickSortGeneric;
				TestQS(chosen3);
				break;
		}
	}







	Print(arr, 15);
	QuickSortGeneric(arr,15,sizeof(int),cmpfunc);
	Print(arr,15);
	if(IsSorted(arr,15))
	{
		puts("success");
	}

	return 0;
}




static void Print(int *arr, size_t size)
{
	size_t i = 0;
	for(; i<size; ++i)
	{
		printf("%d, ",arr[i]);
	}
	puts("");
}

void TestComparison(f_ptr func)
{

	clock_t tick = 0;
	clock_t tock = 0;
	double cpu_time_used;

	INIT();


	tick = clock();
	func(worst_array,MASSIVE_ARRAY);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for worst array is: %f\n",cpu_time_used);
	if(IsSorted(worst_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}

	tick = clock();
	qsort(worst_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for worst array for qsort is: %f\n",cpu_time_used);

	tick = clock();
	func(best_array,MASSIVE_ARRAY);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for best array is: %f\n",cpu_time_used);
	if(IsSorted(best_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}

	tick = clock();
	qsort(best_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for best array for qsort is: %f\n",cpu_time_used);

	tick = clock();
	func(random_array,MASSIVE_ARRAY);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for random array is: %f\n",cpu_time_used);
	if(IsSorted(random_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}
	tick = clock();
	qsort(random_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for random array for qsort is: %f\n",cpu_time_used);
}

void INIT(void)
{
	int i = 0;
	srand(time(NULL));
	for(; i< MASSIVE_ARRAY; ++i)
	{
		random_array[i] = rand() % MASSIVE_ARRAY;
		random_arr_qsort[i] = rand() % MASSIVE_ARRAY;;
		best_array[i] = i;
		best_arr_qsort[i] = i;
		worst_array[i] = MASSIVE_ARRAY - i;
		worst_arr_qsort[i] = MASSIVE_ARRAY - i;
	}

}

void TestLinear(f_ptr2 func)
{

	clock_t tick = 0;
	clock_t tock = 0;
	double cpu_time_used;

	INIT();

	Print(worst_array, 50);
	puts("");
	tick = clock();
	func(worst_array,MASSIVE_ARRAY);
	Print(worst_array, 50);
	puts("");
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for worst array is: %f\n",cpu_time_used);
	if(IsSorted(worst_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}

	tick = clock();
	qsort(worst_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for worst array for qsort is: %f\n",cpu_time_used);

	tick = clock();
	func(best_array,MASSIVE_ARRAY);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for best array is: %f\n",cpu_time_used);
	if(IsSorted(best_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}
	tick = clock();
	qsort(best_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for best array for qsort is: %f\n",cpu_time_used);

	tick = clock();
	func(random_array,MASSIVE_ARRAY);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for random array is: %f\n",cpu_time_used);
	if(IsSorted(random_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}

	tick = clock();
	qsort(random_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for random array for qsort is: %f\n",cpu_time_used);
}



void TestQS(f_ptr3 func)
{

	clock_t tick = 0;
	clock_t tock = 0;
	double cpu_time_used;

	INIT();

	Print(worst_array, 50);
	puts("");
	tick = clock();
	func(worst_array,MASSIVE_ARRAY,sizeof(int),cmpfunc);
	tock = clock();
	Print(worst_array, 50);
	puts("");
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for worst array is: %f\n",cpu_time_used);
	if(IsSorted(worst_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}

	tick = clock();
	qsort(worst_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for worst array for qsort is: %f\n",cpu_time_used);

	tick = clock();
	func(best_array,MASSIVE_ARRAY,sizeof(int),cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for best array is: %f\n",cpu_time_used);
	if(IsSorted(best_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}
	tick = clock();
	qsort(best_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for best array for qsort is: %f\n",cpu_time_used);

	tick = clock();
	func(random_array,MASSIVE_ARRAY,sizeof(int),cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for random array is: %f\n",cpu_time_used);
	if(IsSorted(random_array,MASSIVE_ARRAY))
	{
		printf(GREEN"SORTED SUCCESSFULLY\n"DEFAULT);
	}

	tick = clock();
	qsort(random_arr_qsort,MASSIVE_ARRAY, sizeof(int), cmpfunc);
	tock = clock();
	cpu_time_used = ((double) (tock - tick) / CLOCKS_PER_SEC);
	printf("time for random array for qsort is: %f\n",cpu_time_used);
}




int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


int IsSorted(int *arr, size_t arr_size)
{
  size_t i = 0;
  for(i = 0; i < arr_size - 1; ++i)
  {
    if(arr[i] > arr[i + 1])
    {

      return 0;
    }
  }
  return 1;
}
