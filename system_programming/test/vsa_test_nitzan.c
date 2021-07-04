#include <stdio.h>
#include<stdlib.h>
#include "utl.h"
#include "vsa.h"

#ifdef NDEBUG
        #define HEADER_SIZE 8
       
    #else
        #define HEADER_SIZE 16
       
    #endif
#define WORD 8

static size_t Allignment(size_t block_size);
void Test();


int main()
{
	
	#ifdef NDEBUG
        puts("**************RUNNING IN RELEASE MODE***********************");
       
    #else
        puts("**************RUNNING IN DEBUG MODE***********************"); 
       
    #endif
    
  	Test();
	return 0;
}

void Test()
{
	vsa_t *segment = NULL;
	void *my_alloc_to_save = NULL;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	size_t allocate_segment = 500;
	size_t largest_chunk = 0;
	size_t chunk_test;
	size_t all_block_one = 70;
	size_t all_block_two = 100;
	size_t all_block_three = 180;
	size_t all_block_four = 17;
	size_t all_block_five = 60;
	size_t left_over = 0;
	printf (GREEN"******************************************\n%s",DEFAULT);
	printf (WHITE"***********TESTING VSA FUNCTIONS**********\n%s",DEFAULT);
	printf (WHITE"***************Nitzan Holmes**************\n%s",DEFAULT);
	printf (GREEN"******************************************\n%s",DEFAULT);
	
	my_alloc_to_save = malloc(allocate_segment);
	segment = VSAInit(my_alloc_to_save, allocate_segment);
	
	largest_chunk = VSALargestChunkAvailable(segment);
	chunk_test = allocate_segment - (2 * (HEADER_SIZE));
	chunk_test = (chunk_test % WORD == 0 ? chunk_test : chunk_test - (WORD - (chunk_test % WORD)));
	
	if(chunk_test == largest_chunk && segment)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAInit SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAInit FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	all_block_one = Allignment(all_block_one);
	chunk_test = largest_chunk - all_block_one - HEADER_SIZE ;
	block1 = VSAAlloc(segment, all_block_one);
	largest_chunk = VSALargestChunkAvailable(segment);
	
	
	if(chunk_test == largest_chunk && block1)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAAlloc TEST1 SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAAlloc TEST1 FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	
	
	all_block_two = Allignment(all_block_two);
	chunk_test = largest_chunk - all_block_two - HEADER_SIZE ;
	block2 = VSAAlloc(segment, all_block_two);
	largest_chunk = VSALargestChunkAvailable(segment);
	
	if(chunk_test == largest_chunk && block2)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAAlloc TEST2 SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAAlloc TEST2 FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	
	
	
	
	all_block_three = Allignment(all_block_three);
	chunk_test = largest_chunk - all_block_three - HEADER_SIZE ;
	block3 = VSAAlloc(segment, all_block_three);
	largest_chunk = VSALargestChunkAvailable(segment);
	
	if(chunk_test == largest_chunk && block3)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAAlloc TEST3 SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAAlloc TEST3 FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	
	
	
	all_block_four = Allignment(all_block_four);
	chunk_test = largest_chunk - all_block_four - HEADER_SIZE ;
	block4 = VSAAlloc(segment, all_block_four);
	largest_chunk = VSALargestChunkAvailable(segment);
	
	if(chunk_test == largest_chunk && block4)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAAlloc TEST4 SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAAlloc TEST4 FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	
	
	all_block_five = Allignment(all_block_five);
	chunk_test = largest_chunk;
	block5 = VSAAlloc(segment, all_block_five);
	largest_chunk = VSALargestChunkAvailable(segment);
	left_over = largest_chunk;
	
	if(chunk_test == largest_chunk && block5 == NULL)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAAlloc TEST4 SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf(YELLOW"block5 should be NULL because not enough room to allocate. SUCCESS\n%s",DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAAlloc TEST4 FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	
	
	
	
	all_block_three = Allignment(all_block_three);
	VSAFree(block3);
	chunk_test = all_block_three;
	largest_chunk = VSALargestChunkAvailable(segment);
	
	
	if(chunk_test == largest_chunk)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAFree TEST1 SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAFree TEST1 FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	
	
	
	all_block_four = Allignment(all_block_four);
	VSAFree(block4);
	chunk_test = all_block_four + all_block_three + HEADER_SIZE + left_over + HEADER_SIZE;
	largest_chunk = VSALargestChunkAvailable(segment);
	
	
	if(chunk_test == largest_chunk)
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(CYAN"VSAFree TEST2 SUCCESS\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	else
	{
		printf (WHITE"******************************************************************\n%s",DEFAULT);
		printf(RED"VSAFree TEST2 FAIL\n%s",DEFAULT);
		printf(YELLOW"The largest chunk available you got is: %lu.... should be %lu\n%s",largest_chunk,chunk_test,DEFAULT);
		printf (WHITE"******************************************************************\n\n\n%s",DEFAULT);
	}
	
	
	free(my_alloc_to_save);
}


static size_t Allignment(size_t block_size)
{
	for(;block_size % WORD != 0; ++block_size);
	return block_size;
	
}
