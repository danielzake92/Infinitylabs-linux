/****************************************************************************
* FILE: bst.c  Purpose: library for avl data structure
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Nitzan Holmes  			STATUS: ImpTested
*
****************************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*asserts*/
#include <stdio.h>

#include "heap.h" /*my current lib*/
#include "utl.h"

#define HEAP_SIZE 32
/****************************************************************************
*                     Typedefs
****************************************************************************/
#define INVALID_INDEX 0xffffffffffffffef


/****************************************************************************
*                     Structs and enums
****************************************************************************/

typedef enum dir
{
	LEFT = 1,
	RIGHT = 2
}dir_t;

struct heap 
{
    dynamic_vector_t *vector;
    h_cmp_func_t cmp_func;
};

static size_t GetChildIndex(size_t cur_index, dir_t dir);

static size_t GetParentIndex(size_t cur_index);

static void SwapByIndex(heap_t *heap, size_t ind_a, size_t ind_b);

static size_t GetSuccessorIndex(heap_t *tree,size_t cur_index);

static void SiftUp(heap_t *tree, size_t cur_index);

static void SiftDown(heap_t *tree, size_t cur_index);
/*****************************************************************************/
/*****************************************************************************/
heap_t *HeapCreate(h_cmp_func_t cmp_func)
{
	heap_t *tree = NULL;
	
	assert(cmp_func);

	tree = (heap_t*)malloc( sizeof(heap_t) );
	if( NULL == tree )
	{
		return NULL;
	}

	if( NULL == tree )
	{
		free(tree);
		return NULL;
	}

	tree->vector = DynamicVectorCreate(HEAP_SIZE);
	tree->cmp_func = cmp_func;
	
	return tree;
}
/*****************************************************************************/
void HeapDestroy(heap_t *heap)
{
	assert(heap);

	DynamicVectorDestroy(heap->vector);

	heap->vector = NULL;

	free(heap);
}
/*****************************************************************************/
status_t HeapPush(heap_t *heap, const void *data)
{
	size_t cur_index = 0;
	assert(heap);

	if(FAIL == DynamicVectorPushBack(heap->vector, (void*)data))
	{
		return FAIL;
	}

	cur_index = DynamicVectorGetSize(heap->vector) - 1;
	SiftUp(heap, cur_index);

	return SUCCESS;
}
/*****************************************************************************/
status_t HeapPop(heap_t *heap)
{
	size_t cur_index = 0;
	assert(heap);

	if( 1 >= HeapSize(heap) )
	{
		return DynamicVectorPopBack(heap->vector);
	}

	SwapByIndex(heap, cur_index, HeapSize(heap) - 1);

	if(FAIL == DynamicVectorPopBack(heap->vector))
	{
		return FAIL;
	}

	SiftDown(heap, cur_index);

	return SUCCESS;

}
/*****************************************************************************/
void *HeapPeek(const heap_t *heap)
{
	assert(heap);

	return(DynamicVectorGetAt(heap->vector, 0));
}
/*****************************************************************************/

void *HeapRemove(heap_t *heap, h_match_func_t match_func, const void *data)
{
	size_t i = 0;
	size_t size = 0;
	size_t parent_ind = 0;
	int found = FALSE;
	int res = 0;
	void *value = NULL;
	assert(heap);
	assert(match_func);

	size = HeapSize(heap);
	
	for( i = 0 ; i < size ; ++i)
	{
		if( match_func((void*)DynamicVectorGetAt(heap->vector, i),
												data) == TRUE)
		{
			found = TRUE;
			break;
		}
	}

	if( FALSE == found )
	{
		return NULL;
	}
	
	value = DynamicVectorGetAt(heap->vector, i);

	SwapByIndex(heap, i, HeapSize(heap) - 1);

	if(FAIL == DynamicVectorPopBack(heap->vector))
	{
		return NULL;
	}

	if(HeapIsEmpty(heap))
	{
		return value;
	}

	
	if( INVALID_INDEX == (parent_ind = GetParentIndex(i)))
	{
		SiftDown(heap, i);
		return value;
	}

	res = heap->cmp_func( DynamicVectorGetAt( heap->vector, parent_ind),
							DynamicVectorGetAt( heap->vector, i));
	
	if(res > 0 )
	{
		SiftUp(heap, i)	;
		return value;
	}
	SiftDown(heap, i);
	return value;
}

/*****************************************************************************/
size_t HeapSize(const heap_t *heap)
{
	assert(heap);

	return( DynamicVectorGetSize(heap->vector) );
}
/*****************************************************************************/
bool_t HeapIsEmpty(const heap_t *heap)
{
	assert(heap);

	return( 0 == DynamicVectorGetSize(heap->vector) );
}

/*****************************************************************************/
/*******************************static function*******************************/
/*****************************************************************************/
static size_t GetParentIndex(size_t cur_index)
{
	if( 0 == cur_index )
	{
		return INVALID_INDEX;
	}

	return((cur_index - 1) / 2);
}
/*****************************************************************************/
static size_t GetChildIndex(size_t cur_index, dir_t dir)
{
	return( 2 * cur_index + dir );
}
/*****************************************************************************/
static size_t GetSuccessorIndex(heap_t *tree, size_t cur_index)
{
	size_t left_ind = GetChildIndex(cur_index, LEFT);
	size_t right_ind = GetChildIndex(cur_index, RIGHT);
	size_t max_ind = 0;
	int res = 0;

	assert(tree);

	max_ind = HeapSize(tree) - 1;

	if(HeapIsEmpty(tree))
	{
		return 0;
	}

	/*leaf case*/
	if( max_ind < left_ind && max_ind < right_ind )
	{
		return INVALID_INDEX;
	}
	/*only left*/
	if( max_ind < right_ind )
	{
		return left_ind;		
	}

	res = tree->cmp_func( DynamicVectorGetAt( tree->vector, left_ind),
							DynamicVectorGetAt( tree->vector, right_ind));

	if( 0 > res )
	{
		return left_ind;
	}	

	return right_ind;	
}
/*****************************************************************************/
static void SwapByIndex(heap_t *heap, size_t ind_a, size_t ind_b)
{
	void *temp = NULL;

	assert(heap);

	temp = DynamicVectorGetAt( heap->vector, ind_a);
	DynamicVectorSetAt(heap->vector, ind_a, DynamicVectorGetAt( heap->vector, ind_b));
	DynamicVectorSetAt(heap->vector, ind_b, temp);
}
/*****************************************************************************/
static void SiftUp(heap_t *tree, size_t cur_index)
{
	size_t parent = 0;
	int res = 0;

	assert(tree);
	while( INVALID_INDEX != GetParentIndex(cur_index))
	{
		parent = GetParentIndex(cur_index);
		res = tree->cmp_func( DynamicVectorGetAt( tree->vector, parent),
							DynamicVectorGetAt( tree->vector, cur_index));

		if( 0 > res )
		{
			break;
		}	
		SwapByIndex(tree, cur_index, parent);					  
		cur_index = parent;

	}
}
/*****************************************************************************/
static void SiftDown(heap_t *tree, size_t cur_index)
{
	size_t child = 0;
	int res = 0;


	assert(tree);

	while( INVALID_INDEX != GetSuccessorIndex(tree, cur_index))
	{
		child = GetSuccessorIndex(tree, cur_index);
		res = tree->cmp_func( DynamicVectorGetAt( tree->vector, cur_index),
							DynamicVectorGetAt( tree->vector, child));

		if( 0 > res )
		{
			break;
		}	
		SwapByIndex(tree, cur_index, child);					  
		cur_index = child;
	}
}