#include <stdio.h> /* For printf and puts. */
#include <stdlib.h> /* For malloc and free. */
#include "fsa.h" /* For function declarations. */
#include "utl.h" /* For color utilities. */

/*
struct fsa
{
	size_t next_free;
	size_t num_of_blocks; 
	size_t block_size;
};

typedef struct block_header
{
	size_t next_free;
}block_header_t;

static void PrintFSA(const fsa_t *fsa);
*/
static void SimpleTest(void);

static void LessBlocksTest(void);

static void UnalignedTest(void);

static void NoSpaceTest(void);

int main()
{
	puts(BLUE"***************** SimpleTest *****************\n");
	SimpleTest();
	
	puts(BLUE"**************** LessBlocksTest ****************\n");
	LessBlocksTest();
	
	puts(BLUE"***************** UnalignedTest *****************\n");
	UnalignedTest();
	
	puts(BLUE"****************** NoSpaceTest ******************\n");
	NoSpaceTest();
	
	return 0;
}

void SimpleTest(void)
{
	fsa_t *fsa = NULL;
	int arr[] = {1, 2, 3, 4, 5};
	int *ptr_arr[5] = {NULL};
	size_t i = 0;
	/*size_t next_free = 0;*/
	size_t count = 0;
	size_t num_blocks = 5;
	size_t block_size = sizeof(int);
	size_t total_size = FSASuggestSize(num_blocks, block_size);
	int *ptr = (int *)malloc(total_size);
	
	if (total_size != 104)
	{
		printf(RED"ERROR! Suggested size fhoul be %d, not %lu.\n", 104, total_size);
	}
	else
	{
		printf(GREEN"PASS\n");
	}
	
	if (ptr == NULL)
	{
		puts(RED"Malloc failed.");
		return;
	}
	
	fsa = FSAInit(ptr, total_size, block_size);
	if (fsa == NULL)
	{
		puts(RED"Not enough memory for fsa.");
		free(ptr);
		return;
	}
	
	count = FSACountFree(fsa);
	if (count != num_blocks)
	{
		printf(RED"ERROR! Count is %lu, should be %lu.\n", count, num_blocks);
	}
	else
	{
		printf(GREEN"PASS\n");
	}	
	
	i = 0;
	while (count)
	{
		ptr_arr[i] = FSAAlloc(fsa);
		*(ptr_arr[i]) = arr[i];
		count = FSACountFree(fsa);
		++i;
	}
	
	while (count < num_blocks)
	{
		/*next_free = ((block_header_t *)((size_t)ptr_arr[count] - sizeof(block_header_t)))->next_free;*/
		FSAFree(ptr_arr[count]);
		/*
		if (fsa->next_free != next_free)
		{
			printf(RED"ERROR! fsa->next_free should be %lu not %lu.\n", 
					next_free, fsa->next_free);
		}
		*/
		count = FSACountFree(fsa);
	}
	printf(GREEN"PASS\n");
	
	free(ptr);
	printf(DEFAULT);
}

void LessBlocksTest(void)
{
	fsa_t *fsa = NULL;
	int arr[] = {1, 2, 3, 4, 5};
	int *ptr_arr[5] = {NULL};
	size_t i = 0;
	/*size_t next_free = 0;*/
	size_t count = 0;
	size_t num_blocks = 5;
	size_t block_size = sizeof(int);
	size_t total_size = FSASuggestSize(num_blocks, block_size);
	int *ptr = (int *)malloc(total_size / 2);
	if (ptr == NULL)
	{
		puts(RED"Malloc failed.");
		return;
	}
	
	if ((total_size / 2) != 52)
	{
		printf(RED"ERROR! Suggested size should be %d, not %lu.\n", 52, (total_size / 2));
	}
	else
	{
		printf(GREEN"PASS\n");
	}
	
	fsa = FSAInit(ptr, (total_size / 2), block_size);
	if (fsa == NULL)
	{
		puts(RED"Not enough memory for fsa.");
		free(ptr);
		return;
	}
	
	num_blocks = 1;
	count = FSACountFree(fsa);
	if (count != num_blocks)
	{
		printf(RED"ERROR! Count is %lu, should be %lu.\n", count, num_blocks);
	}
	else
	{
		printf(GREEN"PASS\n");
	}	
	
	i = 0;
	while (count)
	{
		ptr_arr[i] = FSAAlloc(fsa);
		*(ptr_arr[i]) = arr[i];
		count = FSACountFree(fsa);
		++i;
	}
	
	while (count < num_blocks)
	{
		/*next_free = ((block_header_t *)((size_t)ptr_arr[count] - sizeof(block_header_t)))->next_free;*/
		FSAFree(ptr_arr[count]);
		/*
		if (fsa->next_free != next_free)
		{
			printf(RED"ERROR! fsa->next_free should be %lu not %lu.\n", 
					next_free, fsa->next_free);
		}
		*/
		count = FSACountFree(fsa);
	}
	printf(GREEN"PASS\n");
	
	free(ptr);
	printf(DEFAULT);
}

void UnalignedTest(void)
{
	fsa_t *fsa = NULL;
	int arr[] = {1, 2, 3, 4, 5};
	int *ptr_arr[5] = {NULL};
	size_t i = 0;
	/*size_t next_free = 0;*/
	size_t count = 0;
	size_t num_blocks = 5;
	size_t block_size = sizeof(int);
	size_t total_size = FSASuggestSize(num_blocks, block_size);
	int *ptr = (int *)malloc(total_size);
	if (ptr == NULL)
	{
		puts(RED"Malloc failed.");
		return;
	}
	
	fsa = FSAInit(((char *)ptr + 3), total_size, block_size);
	if (fsa == NULL)
	{
		puts(RED"Not enough memory for fsa.");
		free(ptr);
		return;
	}
	
	num_blocks = 4;
	
	count = FSACountFree(fsa);
	if (count != num_blocks)
	{
		printf(RED"ERROR! Count is %lu, should be %lu.\n", count, num_blocks);
	}
	else
	{
		printf(GREEN"PASS\n");
	}	
	
	i = 0;
	while (count)
	{
		ptr_arr[i] = FSAAlloc(fsa);
		*(ptr_arr[i]) = arr[i];
		count = FSACountFree(fsa);
		++i;
	}
	
	while (count < num_blocks)
	{
		/*next_free = ((block_header_t *)((size_t)ptr_arr[count] - sizeof(block_header_t)))->next_free;*/
		FSAFree(ptr_arr[count]);
		/*
		if (fsa->next_free != next_free)
		{
			printf(RED"ERROR! fsa->next_free should be %lu not %lu.\n", 
					next_free, fsa->next_free);
		}
		*/
		count = FSACountFree(fsa);
	}
	printf(GREEN"PASS\n");
	
	free(ptr);
	printf(DEFAULT);
}

void NoSpaceTest(void)
{
	fsa_t *fsa = NULL;
	size_t block_size = sizeof(int);
	size_t total_size = 24;
	int *ptr = (int *)malloc(total_size);
	if (ptr == NULL)
	{
		puts(RED"Malloc failed.");
		return;
	}
	
	fsa = FSAInit(ptr, total_size, block_size);
	if (fsa == NULL)
	{
		puts(GREEN"PASS");
	}
	else
	{
		printf(RED"ERROR! fsa should be NULL.\n");
	}
	free(ptr);
	printf(DEFAULT);
}

/*
void PrintFSA(const fsa_t *fsa)
{
	size_t num_allocated = fsa->num_of_blocks - FSACountFree(fsa);
	block_header_t *start = (block_header_t *)((((char *)fsa) + sizeof(fsa_t)));
	
	while (num_allocated)
	{
		if ((size_t)start == ((size_t)fsa + start->next_free))
		{
			printf(YELLOW"%d ", *((int *)((size_t)start + sizeof(block_header_t))));
			--num_allocated;
		}
		start = (block_header_t *)(((char *)start) + (fsa->block_size));
	}
	puts("");
}
*/
