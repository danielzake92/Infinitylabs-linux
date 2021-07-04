/********************************************************************************
 *  FILENAME:  sorts.c  DEVELOPER: Daniel Zaken   TEAM: Blue
 *
 *  Reviwer:   Michael
 *
 *  PURPOSE:   Function for sorting lists
 *
 *******************************************************************************/
#include <assert.h>/*For assertion*/
#include <stdlib.h>/*for calloc*/
#include <string.h>

#include "sorts.h"/*Our sorts lib*/
#include "../../ds/include/utl.h"

#define MEMSWAP_FAIL -1
#define MIN_INDEX(a, b, arr) (arr[(a)] <= arr[(b)] ? (a) : (b))

static void Swap(int *a, int *b);
static int ArrMax(int *arr, size_t arr_size);
static int ArrMin(int *arr, size_t arr_size);
static size_t FindMaxDig(int *arr, size_t arr_size);
int CountingForRadixSort(int *arr, size_t arr_size, int digit);

static void Divide(int *arr, int *temp, size_t size);
static void Merge(int *arr1, size_t size1, int *arr2, size_t size2,
	 												int *arr_parent);

static void DivideGeneric(void *arr, void *temp, size_t size,
	 				size_t element_size, cmp_func_t cmp_func);

static void MergeGeneric(void *arr1, size_t size1, void *arr2, size_t size2,
	 					void *arr_parent,size_t element_size, cmp_func_t cmp_func);

static int Partitioning(void *base, size_t left, size_t right, size_t size,
	 													cmp_func_t cmp_func);

static int QSHelper(void* base, int size, int left, int right, cmp_func_t cmp_func);

/*static int MemSwap(void *memb1, void *memb2, size_t memb_size);*/

static void MemSwap(void *memb1, void *memb2, size_t memb_size);

/****************************************************************************/
void BubbleSort(int *arr, size_t arr_size)
{
	size_t count = 0;
	size_t i = 0;
	size_t j = 0;
	assert(arr);
	do
	{
		count = 0;
		for( i = 0 ; i < (arr_size - 1 - j) ; ++i )
		{
			if( arr[i] > arr[i+1] )
			{
				Swap(arr + i, arr + i + 1);
				++count;
			}

		}
		++j;
	} while(count);
}
/****************************************************************************/
void InsertionSort(int *arr, size_t arr_size)
{
	size_t i = 0;
	size_t j = 0;
	assert(arr);

	for( i = 1 ; i < arr_size ; ++i )
	{
		for( j = i - 1 ; arr[j] > arr[j + 1] && (j + 1) > 0 ; --j)
		{
			Swap(arr + j, arr + j + 1);
		}
	}
}
/****************************************************************************/
void SelectionSort(int *arr, size_t arr_size)
{
	size_t i = 0;
	size_t j = 0;
	size_t min = 0;
	assert(arr);

	for( i = 0 ; i < arr_size - 1; ++i )
	{
		min = i;
		for( j = i + 1; j < arr_size ; ++j)
		{
			min = MIN_INDEX(min ,j, arr);
		}
		Swap(arr + i, arr + min);
	}
}
/****************************************************************************/
int RadixSort(int *arr, size_t arr_size)
{
	size_t max_dig = 0;
	int exp = 1;
	assert(arr);

	max_dig = FindMaxDig(arr, arr_size);

	while(max_dig)
	{
		if( FAIL == CountingForRadixSort(arr, arr_size, exp) )
		{
			return FAIL;
		}
		--max_dig;
		exp *= 10;
	}
	return SUCCESS;
}
/****************************************************************************/
int CountingSort(int *arr, size_t arr_size)
{
	size_t i = 0;
	int min = 0;
	int max = 0;
	int range = 0;
	int *count = NULL;
	int *output = NULL;
	size_t count_size = 0;
	assert(arr);

	min = ArrMin(arr, arr_size);
	max = ArrMax(arr, arr_size);

	range = max - min + 1;

	count_size = (size_t)(range);
	count = (int*)calloc( count_size ,sizeof(int));
	if ( NULL == count ) return FAIL;

	output = (int*)malloc( arr_size * sizeof(int));
	if( NULL == output )
	{
		free(count);
		return FAIL;
	}
	/*bucketing*/
	for (i = 0 ; i < arr_size ; ++i)
	{
		count[arr[i] - min] += 1;
	}

	/*accumalation for stability*/
	for (i = 1 ; i < count_size ; ++i)
	{
		count[i] += count[i - 1];
	}

	for (i = arr_size ; 0 < i ; --i)
	{
		output[count[arr[i - 1] - min] - 1] = arr[i - 1] - min;
		--count[arr[i - 1] - min];
	}

	for (i = 0 ; i < arr_size ; ++i)
	{
		arr[i] = output[i] + min;
	}

	free(count);
	free(output);
	return SUCCESS;
}
/****************************************************************************/
int CountingForRadixSort(int *arr, size_t arr_size, int exp)
{
	size_t i = 0;
	int *count = NULL;
	int *output = NULL;
	int min = -9;
	int max = 9;
	int base = 10;
	size_t count_size = max - min + 1;
	assert(arr);

	count = (int*)calloc( count_size ,sizeof(int));
	if ( NULL == count ) return FAIL;

	output = (int*)malloc( arr_size * sizeof(int));
	if( NULL == output )
	{
		free(count);
		return FAIL;
	}
	/*bucketing*/
	for (i = 0 ; i < arr_size ; ++i)
	{
		++count[(arr[i] / exp) % base + max];
	}

	/*accumalation*/
	for (i = 1 ; i < count_size ; ++i)
	{
		count[i] += count[i - 1];
	}

	for (i = arr_size  ; 0 < i ; --i)
	{
		output[count[(arr[i - 1] / exp) % base + max] - 1] = arr[i - 1] ;
		--count[(arr[i - 1] / exp) % base + max];
	}

	for (i = 0 ; i < arr_size ; ++i)
	{
		arr[i] = output[i];
	}

	free(count);
	free(output);
	return SUCCESS;
}
/****************************************************************************/
int MergeSort(int *arr, size_t arr_size)
{
	int *arr_temp = NULL;

	assert(arr);

	arr_temp = (int*)malloc(sizeof(int) * arr_size );
	if( NULL == arr_temp )return FAIL;

	Divide(arr, arr_temp, arr_size);

	free( arr_temp );
	return SUCCESS;
}
/***************************************************************************/
int QuickSortGeneric(void *base, size_t nmemb, size_t size, cmp_func_t cmp_func)
{
	QSHelper(base, size, 0, nmemb - 1, cmp_func);
	return SUCCESS;
}
/***************************************************************************/
static int QSHelper(void* base, int size, int left, int right, cmp_func_t cmp_func)
{
    int pivot_index = 0;

    if (left >= right)
    {
        return SUCCESS;
    }

    pivot_index = Partitioning(base, left, right, size, cmp_func);


    QSHelper(base, size, left, pivot_index - 1, cmp_func);
    QSHelper(base, size, pivot_index + 1, right, cmp_func);
		return SUCCESS;
}
/***************************************************************************/
static int Partitioning(void *base, size_t left, size_t right, size_t size,
	 													cmp_func_t cmp_func)
{
	void *i_runner = NULL;
	void *j_runner = NULL;

	size_t i = 0;
	int mid = (left + right) / 2;
	int pivot = left;

	void *pivot_ind = (void*)((char*)base + left * size );
	void *base_mid = (void*)((char*)base + mid * size );

	MemSwap( pivot_ind, base_mid, size);

	for(i = left + 1; i <= right; ++i)
	{
		i_runner = (void*)((char*)base + i * size);

		if( cmp_func(pivot_ind, i_runner) > 0 )
		{
			++pivot;
			j_runner = (void*)((char*)base + (pivot * size));

			MemSwap(i_runner, j_runner, size);
		}
	}
	j_runner = (void*)((char*)base + pivot * size);
	MemSwap(pivot_ind, j_runner, size );

	return pivot;
}
/***************************************************************************/
static void MemSwap(void *memb1, void *memb2, size_t memb_size)
{
    size_t i = 0;
    char temp = '\0';

    assert(memb1);
    assert(memb2);

    /* copies byte by byte */
    for (i = 0; i < memb_size; ++i)
    {
        temp = *((char *)memb1 + i);
        *((char *)memb1 + i) = *((char *)memb2 + i);
        *((char *)memb2 + i) = temp;
    }
}
/****************************************************************************/
static void Divide(int *arr, int *temp, size_t size)
{
	size_t r = size/2;
	size_t l = size - r;

	assert(arr);
	assert(temp);

	if( 1 < size )
	{
		Divide(arr, temp, l);
		Divide(arr + l, temp, r);
	}
	Merge(arr, l, arr + l, r, temp );
}
/****************************************************************************/
static void Merge(int *arr1, size_t size1, int *arr2, size_t size2,
	 												int *arr_parent)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	assert(arr1);
	assert(arr2);
	assert(arr_parent);
	/* puting the max number from each array at parent array */
	while( i < size1 && j < size2 )
	{
		if( arr1[i] <= arr2[j] )
		{
			arr_parent[k] = arr1[i];
			++i;
		}
		else
		{
			arr_parent[k] = arr2[j];
			++j;
		}
		++k;
	}
	/* filling the reserves from arr 1 */
	while( i < size1)
	{
		arr_parent[k] = arr1[i];
		++i;
		++k;
	}

	/* filling the reserves from arr 2 */
	while( j < size2)
	{
		arr_parent[k] = arr2[j];
		++j;
		++k;
	}
	/* copying from arr_parent which is temp to the real array to be changed */
	for(k = 0; k < size1 + size2 ; ++k )
	{
		arr1[k] = arr_parent[k];
	}
}
/****************************************************************************/
int MergeSortGeneric(void *arr, size_t arr_size, size_t element_size, cmp_func_t cmp_func)
{
	void *arr_temp = NULL;

	assert(arr);

	arr_temp = (void*)malloc(element_size * arr_size );
	if( NULL == arr_temp )return FAIL;

	DivideGeneric(arr, arr_temp, arr_size, element_size, cmp_func);

	free( arr_temp );
	return SUCCESS;
}
/****************************************************************************/
static void DivideGeneric(void *arr, void *temp, size_t size,
	 				size_t element_size, cmp_func_t cmp_func)
{
	size_t r = size/2;
	size_t l = size - r;

	assert(arr);
	assert(temp);

	if( 1 < size )
	{
		DivideGeneric(arr, temp, l, element_size, cmp_func);
		DivideGeneric((void*)((char*)arr + l * element_size), temp, r,
		 										element_size, cmp_func);
	}
	MergeGeneric(arr, l,(void*)((char*)arr + l * element_size), r,
	 								temp,element_size ,cmp_func );
}
/****************************************************************************/
static void MergeGeneric(void *arr1, size_t size1, void *arr2, size_t size2,
	 					void *arr_parent,size_t element_size, cmp_func_t cmp_func)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	int value = 0;

	assert(arr1);
	assert(arr2);
	assert(arr_parent);

	size1 *= element_size;
    size2 *= element_size;

	while( i < size1 && j < size2 )
	{
		value = cmp_func((void*)((char*)arr1 + i),(void*)(((char*)arr2) + j));

		if( value < 0 )

		{
			memcpy( (void*)((char*)arr_parent + k ), (void*)((char*)arr1 + i ),
			 													element_size);
			i += element_size;
		}
		else
		{
			memcpy( (void*)((char*)arr_parent + k ), (void*)((char*)arr2 + j ),
			 													element_size);
			j += element_size;
		}
		k += element_size;
	}

	while( i < size1 )
	{
		memcpy( (void*)((char*)arr_parent + k ), (void*)((char*)arr1 + i ),
		 													element_size);
		i += element_size;
		k += element_size;
	}

	while( j < size2 )
	{
		memcpy( (void*)((char*)arr_parent + k ), (void*)((char*)arr2 + j ),
		 													element_size);
		j += element_size;
		k += element_size;
	}

	for(i = 0; i < k; i += element_size)
	{
		memcpy( (void*)((char*)arr1 + i), (void*)((char*)arr_parent + i) ,
		 													element_size);
	}
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
static void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
/****************************************************************************/
static int ArrMax(int *arr, size_t arr_size)
{
	size_t i = 0;
	int max = 0;
	assert(arr);

	for(; i < arr_size ; ++i )
	{
		max = MAX(max, arr[i]);
	}
	return max;
}
/****************************************************************************/
static int ArrMin(int *arr, size_t arr_size)
{
	size_t i = 0;
	int min = 0;
	assert(arr);

	for(; i < arr_size ; ++i )
	{
		min = MIN(min, arr[i]);
	}
	return min;
}
/****************************************************************************/
static size_t FindMaxDig(int *arr, size_t arr_size)
{
	int max = 0;
	int max_negative = 0;
	size_t max_dig = 0;
	int base = 10;
	assert(arr);

	max = ArrMax(arr, arr_size);
	max_negative = -1 * ArrMin(arr, arr_size);

	if(max_negative > max)
	{
		max = max_negative;
	}

	while(max)
	{
		max /= base;
		++max_dig;
	}
	return max_dig;
}
