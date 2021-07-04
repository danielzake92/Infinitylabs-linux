#include <stdio.h>
#include "bitarray.h"
int main()
{	
	char *str = MallocToBitsArrayStr();
	
	
    printf ("\033[34;1mSet On - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrSetOn(10, 0)); /*11*/
	printf("%lu\n",BitsArrSetOn(5, 1)); /*7*/
	puts("");
/****************************************************************************/	
	printf ("\033[34;1mSet Off - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrSetOff(7, 1)); /*5*/
	puts("");
/****************************************************************************/	
	printf ("\033[34;1mSet Bit - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrSetBit(5, 1, 1)); /*7*/
	printf("%lu\n",BitsArrSetBit(7, 1, 0)); /*5*/
	puts("");	
/****************************************************************************/
	printf ("\033[34;1mGet bit - TEST\033[0m \n");/*blue msg*/	
	printf("%d\n",BitsArrGetBit(5, 1)); /*0*/
	printf("%d\n",BitsArrGetBit(7, 1)); /*1*/
	puts("");	
/****************************************************************************/
	printf ("\033[34;1mSet All - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrSetAll(5)); /*max size_t*/
	puts("");	
/****************************************************************************/
	printf ("\033[34;1mClear All - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrClearAll(5)); /*0*/
	puts("");			
/****************************************************************************/		
	printf ("\033[34;1mCount On - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrCountOn(15)); /*4*/
	puts("");
/****************************************************************************/		
	printf ("\033[34;1mCount On With Lut - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrLutCountOn(15)); /*4*/
	puts("");	
/****************************************************************************/	
	printf ("\033[34;1mCount Off - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrCountOff(15)); /*60*/
	puts("");
/****************************************************************************/	
	printf ("\033[34;1mFlip - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrFlip(5, 2)); /*1*/
	puts("");	
/****************************************************************************/	
	printf ("\033[34;1mArr To String - TEST\033[0m \n");/*blue msg*/	
	printf("%s\n",BitsArrToString(156, str)); /*1010*/
	puts("");		
/****************************************************************************/		
	printf ("\033[34;1mLeft Shift - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrLeftShift(5, 1)); /*10*/
	puts("");
/****************************************************************************/		
	printf ("\033[34;1mRight Shift - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrRightShift(10, 1)); /*5*/
	puts("");
/****************************************************************************/		
	printf ("\033[34;1mMiror - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrMirror(4294967296)); /*2147483648*/
	puts("");	
	
	printf ("\033[34;1mMiror2 - TEST\033[0m \n");/*blue msg*/	
	printf("%lu\n",BitsArrLutMirror(4294967296)); /*172*/
	puts("");	
	
	
	return 0;
}


