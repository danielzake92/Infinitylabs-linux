/********************************************************************************
 *  FILENAME:  sorts.c  DEVELOPER: Daniel Zaken   TEAM: Blue
 *
 *  Reviwer:   Elizabeta
 *
 *  PURPOSE:   Function for sorting lists
 *
 *******************************************************************************/
#include <assert.h>/*For assertion*/
#include <stdlib.h>/*for calloc*/
#include "search.h"/*Our sorts lib*/
#include "../../ds/include/utl.h"

#define MIN_INDEX(a, b, arr) (arr[(a)] <= arr[(b)] ? (a) : (b))
#define NOT_FOUND -1

static int BinarySearchRecHelper(const int *arr,int low ,int last_index, int data);

/****************************************************************************/
int BinarySearchIter(const int *arr, int last_index, int data)
{
	int low = 0;
	int mid = 0;

	assert(arr);

	while( low <= last_index )
	{
		mid = (low + last_index) / 2;

		if( arr[mid] == data )
		{
			return mid;
		}

		if( data > arr[mid])
		{
			low = mid + 1;
			continue;
		}
		last_index = mid - 1;
	}

	return NOT_FOUND;
}

int BinarySearchRec(const int *arr, int last_index, int data)
{
	assert(arr);
	return BinarySearchRecHelper(arr, 0, last_index, data);
}

static int BinarySearchRecHelper(const int *arr,int low ,int last_index, int data)
{
	int mid = 0;
	assert(arr);

	mid = ( last_index + low ) / 2;

	if( arr[mid] == data )
	{
		return mid;
	}

	if( low >= last_index )
	{
		return NOT_FOUND;
	}

	if( data > arr[mid] )
	{
		return BinarySearchRecHelper(arr ,mid + 1 , last_index, data);
	}
	return BinarySearchRecHelper(arr ,low , mid - 1, data);
}

/****************************************************************************/
/****************************************************************************/
