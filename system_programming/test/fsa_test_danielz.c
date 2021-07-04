#include <stdio.h>
#include <stdlib.h>
#include "fsa.h"
#include "utl.h"

void Test(void);



int main()
{	
	
	printf ("%s*****************************************\n",BLUE);
	printf ("%s---------------PRJ 1 tests---------------\n",BLUE);
	printf ("%s*****************************************\n",BLUE);
	
	puts(DEFAULT);
	
	Test();
		
	puts(DEFAULT);		
		
	printf ("%s*****************************************\n",BLUE);
	printf ("%s---------------Test ended----------------\n",BLUE);
	printf ("%s*****************************************\n%s",BLUE,DEFAULT);
	
	return 0;
}
/****************************************************************************/

void Test(void)
{
	size_t total_size = 400;
	size_t block_size = 100;
	int inc = 3;
	void *space = malloc( total_size );
	void *s1, *s2, *s3;
	
	fsa_t* space_fsa = FSAInit( ((char*)space + inc) , total_size - inc, block_size);
	printf(YELLOW"suggestion for 10 blocks of size %lu = %lu, shuld be 1144\n"DEFAULT,block_size,FSASuggestSize(10,block_size));
	
	puts(GREEN"Initialize");
	printf(YELLOW"how many free = %lu, should be 3\n"DEFAULT,FSACountFree(space_fsa));
/****************************************************************************/
	puts(GREEN"Allocating s1");
	s1 = FSAAlloc(space_fsa);
	printf(YELLOW"how many free = %lu, should be 2\n"DEFAULT,FSACountFree(space_fsa));	
/****************************************************************************/
	puts(GREEN"Allocating s2");
	s2 = FSAAlloc(space_fsa);
	printf(YELLOW"how many free = %lu, should be 1\n"DEFAULT,FSACountFree(space_fsa));		
/****************************************************************************/	
	puts(GREEN"Allocating s3");
	s3 = FSAAlloc(space_fsa);
	printf(YELLOW"how many free = %lu, should be 0\n"DEFAULT,FSACountFree(space_fsa));	
/****************************************************************************/	
	puts(GREEN"free s1");
	FSAFree(s1);
	printf(YELLOW"how many free = %lu, should be 1\n"DEFAULT,FSACountFree(space_fsa));	
/****************************************************************************/	
	puts(GREEN"free s2");
	FSAFree(s2);
	printf(YELLOW"how many free = %lu, should be 2\n"DEFAULT,FSACountFree(space_fsa));	
/****************************************************************************/	
	puts(GREEN"free s3");
	FSAFree(s3);
	printf(YELLOW"how many free = %lu, should be 3\n"DEFAULT,FSACountFree(space_fsa));	
/****************************************************************************/	

	
	free(space);
	
}

