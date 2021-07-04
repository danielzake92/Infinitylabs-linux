/****************************************************************************
 *  FILENAME:  MemCpy.c   NAME:  Daniel Zaken    REVIEWER:   Moshe Elisha   * 
 *                                                                          *
 *  POURPOSE:  Create LIB which implementes mem functions                   *
 *                                                                          *
 ****************************************************************************/
/*INCLUDES*/
#include <cstddef>
#include <cassert> /*assert required*/
#include <cstring>
#include <cstdio>
/*************************************************************/
void *MemCpy(void *dest, const void * src, size_t n)
{
	assert(dest);
	assert(src);
	
	char *char_dest = reinterpret_cast<char*>(dest);
	char *char_src = reinterpret_cast<char*>((const_cast<void*>(src)));
	char *end = reinterpret_cast<char*>((const_cast<void*>(src))) + n;

	while( reinterpret_cast<size_t>(char_dest) % sizeof(void*) && char_src < end )
	{	
		*char_dest = *char_src;
		++char_dest;	
		++char_src;	
	}

	void **void_des = reinterpret_cast<void**>(char_dest);
	void **void_src = reinterpret_cast<void**>(char_src);
	void **void_end = reinterpret_cast<void**>(end);

	while( static_cast<size_t>(void_end - void_src) > sizeof(void*) )
	{	
		*void_des = *void_src;
		++void_des;
		++void_src;
	}
	
	char_dest = reinterpret_cast<char*>(void_des);
	char_src = reinterpret_cast<char*>(void_src);

	while( char_src < end )
	{	
		*char_dest = *char_src;
		++char_dest;	
		++char_src;	
	}

	return dest;	
}

int main()
{
	char str5[40] = "good morning daniel good morning daniel";
	char str6[40] = "good morning daniel good morning daniel";

	memcpy(str5+2, str5+5, 20);
	MemCpy(str6+2, str6+5, 20);

	printf("str5 = %s\n str6 = %s\n", str5, str6);
	printf("%d\n", strcmp(str5, str6));


	return 0;
}

