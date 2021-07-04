/****************************************************************************
 *  FILENAME:  DataTypes  NAME:  Daniel Zaken  REVIEWER:  Liad oz           *
 *                                                                          *
 *  POURPOSE:  Printing all the data sizes                                  *
 *                                                                          *
 ****************************************************************************/
 
#include <stdio.h> /*standart output required*/

void PrintDataTypes ();

int main()
{
	
	PrintDataTypes();
			
	return 0;
}

void PrintDataTypes ()
{
	
	puts("");
	printf(" sizeof(char) is               %lu bytes\n", sizeof(char));
	printf(" sizeof(signed char) is        %lu bytes\n", sizeof(signed char));
	printf(" sizeof(unsigned char) is      %lu bytes\n", sizeof(unsigned char));
	
	printf(" sizeof(short) is              %lu bytes\n", sizeof(short));
	printf(" sizeof(short int) is          %lu bytes\n", sizeof(short int));
	printf(" sizeof(signed short) is       %lu bytes\n", sizeof(signed short));
	printf(" sizeof(signed short int) is   %lu bytes\n", sizeof(signed short int));
	
	printf(" sizeof(int) is                %lu bytes\n", sizeof(int));
	printf(" sizeof(signed) is             %lu bytes\n", sizeof(signed));
	printf(" sizeof(signed int) is         %lu bytes\n", sizeof(signed int));
	printf(" sizeof(unsigned) is           %lu bytes\n", sizeof(unsigned));
	printf(" sizeof(unsigned int) is       %lu bytes\n", sizeof(unsigned int));
	
	printf(" sizeof(long) is               %lu bytes\n", sizeof(long));
	printf(" sizeof(long int) is           %lu bytes\n", sizeof(long int));
	printf(" sizeof(signed long) is        %lu bytes\n", sizeof(signed long));
	printf(" sizeof(signed long int) is    %lu bytes\n", sizeof(signed long int));
	
	printf(" sizeof(unsigned long) is      %lu bytes\n", sizeof(unsigned long));
	printf(" sizeof(unsigned long int) is  %lu bytes\n", sizeof(unsigned long int));
	
	printf(" sizeof(float) is              %lu bytes\n", sizeof(float));
	
	printf(" sizeof(double) is             %lu bytes\n", sizeof(double));
	printf(" sizeof(long double) is        %lu bytes\n", sizeof(long double));
	
	printf(" sizeof(size_t) is             %lu bytes\n", sizeof(size_t));
	
	printf(" sizeof(void*) is              %lu bytes\n", sizeof(void*));	
}










