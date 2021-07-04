#include <stdio.h>
#include <stdlib.h>
#include "fsa.h"
#include "utl.h"

static void FSATest(void);


int main()
{
	FSATest();
	return 0;
}



static void FSATest(void)
{
	char *original = NULL;
	fsa_t *fsa = NULL;
	size_t number_of_blocks = 10;
	size_t block_size = 5;
	size_t total_size = FSASuggestSize(number_of_blocks, block_size);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	void *block6 = NULL;
	void *block7 = NULL;
	
	printf("%sTotal Suggested Size: %s%lu\n",YELLOW,WHITE,total_size); 
	printf("%sNumber of Blocks: %s%lu\n",YELLOW,WHITE,number_of_blocks);
	printf("%sBlock Size: %s%lu\n",YELLOW,WHITE,block_size);
	

	original = (char *)malloc(total_size + sizeof(void*));
	
	puts(YELLOW"Initializing FSA\n");
	fsa = FSAInit((void *)(original), total_size, block_size);
	
	printf("%s Number of free blocks that can be allocated:%s %lu%s, should be%s %lu\n\n",YELLOW,WHITE,FSACountFree(fsa),YELLOW,WHITE,number_of_blocks);
	
	puts(YELLOW"Allocating 7 blocks\n");
	block1 =  FSAAlloc(fsa);
	block2 =  FSAAlloc(fsa);
	block3 =  FSAAlloc(fsa);
	block4 =  FSAAlloc(fsa);
	block5 =  FSAAlloc(fsa);
	block6 =  FSAAlloc(fsa);
	block7 =  FSAAlloc(fsa);

	printf("%s Number of free blocks that can be allocated:%s %lu%s, should be%s %lu\n\n",YELLOW,WHITE,FSACountFree(fsa),YELLOW,WHITE,number_of_blocks-7);

	puts("Freeing 7 blocks\n");
	
	FSAFree(block1);
	FSAFree(block2);
	FSAFree(block3);
	FSAFree(block4);
	FSAFree(block5);
	FSAFree(block6);
	FSAFree(block7);
	
	printf("%s Number of free blocks that can be allocated:%s %lu%s, should be%s %lu\n\n",YELLOW,WHITE,FSACountFree(fsa),YELLOW,WHITE,number_of_blocks);
	
	
	
	free(original);
}
