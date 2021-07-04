#include <stdio.h>
#include "bitwise.h"


int main()
{
	unsigned int arr[] = {3, 7, 9, 11, 137};
	unsigned int a = 32, b = 234;
	
	printf ("\033[34;1mPOW2\033[0m \n");/*blue msg*/	
	Pow2(1,3);
	Pow2(1,5);
	Pow2(2,8);
	puts("");
	
	printf ("\033[34;1mIS2POW - NO LOOP\033[0m \n");/*blue msg*/	
	Is2PowNoLoop(128);
	Is2PowNoLoop(127);
	Is2PowNoLoop(1024);
	Is2PowNoLoop(1028);
	puts("");
	
	printf ("\033[34;1mIS2POW - WITH LOOP\033[0m \n");/*blue msg*/	
	Is2Pow(128);
	Is2Pow(127);
	Is2Pow(1024);
	puts("");
	
	printf ("\033[34;1mADD ONE\033[0m \n");/*blue msg*/	
	AddOne(5);
	AddOne(32);
	AddOne(199);
	puts("");
	
	printf ("\033[34;1mTHREEE BITS SET PRINT\033[0m \n");/*blue msg*/	
	ThreeBitsPrint(arr, sizeof (arr) / sizeof(arr[0]));
	puts("");
	
	printf ("\033[34;1mBYTE MIRROR1\033[0m \n");/*blue msg*/	
	ByteMirror1(4356456);
	
	printf ("\033[34;1mBYTE MIRROR2\033[0m \n");/*blue msg*/	
	ByteMirror2(4356456);
	puts("");
	
	printf ("\033[34;1mBITS TWO AND SIX\033[0m \n");/*blue msg*/	
	BitsTwoAndSix(60);	
	BitsTwoAndSix(179);	
	puts("");
	
	printf ("\033[34;1mBITS TWO OR SIX\033[0m \n");/*blue msg*/	
	BitsTwoOrSix(60);	
	BitsTwoOrSix(200);
	BitsTwoOrSix(202);	
	puts("");
	
	printf ("\033[34;1mSWAP BITS THREE AND FIVE\033[0m \n");/*blue msg*/	
	SwapBitThreeAndFive(76);
	puts("");
	
	printf ("\033[34;1mCLOSE DIVIDED 16\033[0m \n");/*blue msg*/	
	ClosestDivided16(42);
	ClosestDivided16(63);
	ClosestDivided16(67);
	puts("");
	
	printf ("\033[34;1mSWAP WITH TWO\033[0m \n");/*blue msg*/	
	SwapWithTwo(&a,&b);
	puts("");
	
	printf ("\033[34;1mBITS TRUE COUNT\033[0m \n");/*blue msg*/	
	BitsTrueCount(7);
	BitsTrueCount(62);
	BitsTrueCount(50);
	puts("");
	
	printf ("\033[34;1mBITS TRUE COUNT NO LOOP\033[0m \n");/*blue msg*/	
	BitsTrueCountNoLoop(7);
	BitsTrueCountNoLoop(62);
	BitsTrueCountNoLoop(50);
	puts("");	
	
	printf ("\033[34;1mPRINTS FLOAT IN BINARY\033[0m \n");/*blue msg*/	
	PrintFloatBits(1.0);
	PrintFloatBits(3.0);
	PrintFloatBits(-1.53);
		
	return 0;
	
}
