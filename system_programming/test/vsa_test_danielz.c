#include <stdio.h>
#include <stdlib.h>
#include "vsa.h"
#include "utl.h"

#define WORD sizeof(size_t)
#define INVALID 0

#define MAGIC_NUMBER 0x90909090
#define END 0xffffffff


void test1();
void test2();
void test3();

int main()
{	

	#ifdef NDEBUG
		#define HEADER_SIZE 8
		puts("-----------RLEASE----------");
	#else
		#define HEADER_SIZE 16	
		puts("-----------DEBUG-----------");
	#endif

	printf ("%s*****************************************\n",RED);
	printf ("%s            Daniel Z tests               \n",RED);
	printf ("%s*****************************************\n",RED);
	
	puts("");
	
	test1();
	
	puts("");
	
	test2();
	
	puts("");
	
	test3();
	
	puts("");
	
	printf ("%s*****************************************\n",RED);
	printf ("%s---------------Test ended----------------\n",RED);
	printf ("%s*****************************************\n%s",RED,DEFAULT);
	
	return 0;
}
/********************************************************************************
 *                                                                              *
 *                                                                              *
 *******************************************************************************/
void test1()
{
	size_t total_size = 400;
	void *space = malloc( total_size );
	void *s1, *s2; 
	vsa_t *space_vsa = NULL;
	size_t alloc1 = 120;
	size_t alloc2 = 140;
/****************************************************************************/	
	printf (GREEN"******************************************\n%s",DEFAULT);
	printf(GREEN"Initialize TEST1 with allocating %lu bytes\n",total_size);
	printf ("******************************************\n%s",DEFAULT);
	
	printf(WHITE"Allocs to be tried:\nAlloc1 = %lu  Alloc2 = %lu\n\n", alloc1, alloc2);
	
	space_vsa = VSAInit(space, total_size);
	puts(WHITE"NO ALLOCS"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa),total_size - HEADER_SIZE * 2);
	
/****************************************************************************/
	s1 = VSAAlloc(space_vsa, alloc1);
	puts(WHITE"ALLOC S1"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa),total_size - HEADER_SIZE * 3 - alloc1);
/****************************************************************************/
	s2 = VSAAlloc(space_vsa, alloc2);
	puts(WHITE"ALLOC S2"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa),total_size - HEADER_SIZE * 4 - alloc1 - alloc2 - 4);
/****************************************************************************/

	VSAFree(s2);
	puts(WHITE"FREE S2"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa), total_size - HEADER_SIZE * 3 - alloc1);			
	
	(void)s1;
	(void)s2;
	
	free(space);
}
/********************************************************************************
 *                                                                              *
 *                                                                              *
 *******************************************************************************/
void test2()
{
	size_t total_size = 500;
	size_t allignment = total_size - (total_size % WORD);
	void *space = malloc( total_size );
	void *s1, *s2; 
	vsa_t *space_vsa = NULL;
	size_t alloc1 = 120;
	size_t alloc2 = 140;
	
/****************************************************************************/	
	printf (GREEN"******************************************\n%s",DEFAULT);
	printf(GREEN"Initialize TEST2 with allocating %lu bytes\n",total_size);
	printf ("******************************************\n%s",DEFAULT);
	
	printf(WHITE"Allocs to be tried:\nAlloc1 = %lu  Alloc2 = %lu\n\n", alloc1, alloc2);
	
	space_vsa = VSAInit(space, total_size);
	puts(WHITE"NO ALLOCS"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa),allignment - HEADER_SIZE * 2);
	
/****************************************************************************/
	s1 = VSAAlloc(space_vsa, alloc1);
	puts(WHITE"ALLOC S1"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa),allignment - HEADER_SIZE * 3 - alloc1);
/****************************************************************************/
	s2 = VSAAlloc(space_vsa, alloc2);
	puts(WHITE"ALLOC S2"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa),allignment - HEADER_SIZE * 4 - alloc1 - alloc2 - 4);
/****************************************************************************/

	VSAFree(s2);
	puts(WHITE"FREE S2"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa), allignment - HEADER_SIZE * 3 - alloc1);			
	
	(void)s1;
	(void)s2;
	
	free(space);
}	
/********************************************************************************
 *                                                                              *
 *                                                                              *
 *******************************************************************************/
void test3()
{
	size_t total_size = 1448;
	size_t allignment = total_size - (total_size % WORD);
	void *space = malloc( total_size );
	void *s1, *s2, *s3, *s4, *s5; 
	vsa_t *space_vsa = NULL;
	size_t alloc1 = 120;
	size_t alloc2 = 200;
	size_t alloc3 = 600;
	size_t alloc4 = 64;
	size_t alloc5 = 304;
	size_t sum_allocs = alloc1 + alloc2 + alloc3 + alloc4 + alloc5;
	size_t offset = allignment - HEADER_SIZE * 7 - sum_allocs;
	size_t temp1 = 0;
	size_t temp2 = 0;
	size_t temp3 = 0;
/****************************************************************************/	
	printf (GREEN"******************************************\n%s",DEFAULT);
	printf(GREEN"Initialize TEST3 with allocating %lu bytes\n",total_size);
	printf ("******************************************\n%s",DEFAULT);
	
	printf(WHITE"Allocs to be tried:\nAlloc1 = %lu  Alloc2 = %lu  Alloc3 = %lu  Alloc4 = %lu  Alloc5 = %lu\n\n", alloc1, alloc2, alloc3, alloc4, alloc5);
	
	space_vsa = VSAInit(space, total_size);
	
	
/****************************************************************************/
	s1 = VSAAlloc(space_vsa, alloc1);
	s2 = VSAAlloc(space_vsa, alloc2);
	s3 = VSAAlloc(space_vsa, alloc3);
	s4 = VSAAlloc(space_vsa, alloc4);
	s5 = VSAAlloc(space_vsa, alloc5);
	
	if(s5 == NULL )
	{
		printf(GREEN"SUCCESS alloc 5 should be null\n");
	}
	else
	{
		puts(WHITE"ALLOC S1 TO S5"WHITE);
		printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa), offset );			
	}
	
/****************************************************************************/
/****************************************************************************/
	
	#ifdef NDEBUG
		#define HEADER_SIZE 8
		temp1 = 200;
	    temp2 = 328;
	    temp3 = 416;
	#else
		temp1 = 200;
	    temp2 = 336;
	    temp3 = 368;
	#endif
	
	VSAFree(s2);
	puts(WHITE"FREE S2"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa), temp1 );	
	
	VSAFree(s1);
	puts(WHITE"FREE S1"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa), temp2 );	
	
	VSAFree(s5);
	puts(WHITE"FREE S5"WHITE);
	printf(YELLOW"Largest chunck available = %lu, should be %lu\n"DEFAULT,VSALargestChunkAvailable(space_vsa), temp3 );
	
	
	(void)s1;
	(void)s2;
	(void)s3;
	(void)s4;
	(void)s5;	
	
	free(space);
}	

