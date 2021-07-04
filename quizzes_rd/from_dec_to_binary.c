#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INT_BITS ((sizeof(int)) * (CHAR_BIT))

char ConvertBit(int num, int place);
void FromDecToBinary(int num, char *output);
void DecToBinaryRecHelper(int num ,char *output, int bit_num);

int main()
{
	char *output = (char*)malloc(INT_BITS + 1);

	FromDecToBinary(255, output);
	printf("%s\n",output );

	FromDecToBinary(INT_MAX, output);
	printf("%s\n",output );

	FromDecToBinary(INT_MIN, output);
	printf("%s\n",output );

	FromDecToBinary( (1<<0) + (1<<4) + (1<<8) + (1<<12) + (1<<16), output);
	printf("%s\n",output );

	FromDecToBinary( 0XBEEF, output);
	printf("%s\n",output );
	
	free(output);
	
	output = NULL;

 	return 0;
}


void FromDecToBinary(int num, char *output)
{
	output[INT_BITS] = '\0';
	DecToBinaryRecHelper(num,output, INT_BITS );
}
void DecToBinaryRecHelper(int num ,char *output, int bit_num)
{
	if( 0 == bit_num )
	{
		return;
	}
	
	output[INT_BITS - bit_num] = ConvertBit(num, bit_num);
	DecToBinaryRecHelper(num, output, bit_num - 1);
}

char ConvertBit(int num, int place)
{
	return( '0' + !!( num & ( 1 << (place - 1) ) ) );
}