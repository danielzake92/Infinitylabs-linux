/****************************************************************************
 * FILENAME: bitwise.c 	AUTHOR: Daniel Zaken		REVIEWER: Itamar Aron   *
 *																			*
 * PURPOSE: Bitwise operations for math problems                    		*
 *																			*
 ****************************************************************************/
#include <stdio.h>
#include "bitwise.h"

static int g_mask[16] = {0, 1, 1, 2,
                         1, 2, 2, 3,
                         1, 2, 2, 3, 
                         2, 3, 3, 4};

long Pow2(unsigned int x, unsigned int y)
{
	long res = 1;
	res = res << y ;
	res *= x;
	
	printf("the num is : %ld\n",res);
	
	return res;	
}

int Is2PowNoLoop(unsigned int n)
{	
	int res = n && !(n & (n-1)) ;
	
	printf("The number : %d  bool ans : %d\n",n, res);
	
	return n && !(n & (n-1)) ;
}
void Is2Pow(unsigned int n)
{
	unsigned int origin = n;
	unsigned int res = 0;
	for(;n > 2 ;)
        {
            n >>= 1;
        }
        
    if(n == 2)
    {
      res = 1; 
    }
    printf("The number : %d  bool ans : %d\n",origin, res);
    
}

int AddOne(int n)
{
	int old = n;
	int m = 1;
	while ( n & m )
	{
		n = n ^ m;
		m <<= 1;
	}
	
	n = n ^ m;
	
	printf("old num : %d  newnum : %d\n",old, n);
	
	return n;
}

void ThreeBitsPrint(unsigned int arr[], unsigned int size)
{
	unsigned int i = 0;
	for(; i < size ; ++i)
	{
		ThreeBitsTrue(arr[i]);
	}
}

void ThreeBitsTrue (unsigned int n)
{
	int origin = n;
	int counter = 0;
	
	while ( n )
	{
		if(n & 1)
		{
			++counter;
		}
		n >>= 1;
	}
	
	if ( 3 == counter )
	{
		printf("%d\n",origin);	
	}
}

void ByteMirror1(unsigned int n) /*didnt understood*/
{
	unsigned int num_bits = sizeof(n) * 8;
	unsigned int rev_num = 0;
	unsigned int i=0;
		
	for( ; i < num_bits ; ++i)
	{
		if( n & (1<<i) )
		{
			rev_num |= 1 <<( ( num_bits - 1 ) - i );
		}
	}
	printf("%u is the rev num of %u \n",rev_num, n );	

}

void ByteMirror2(unsigned int b) /*didnt understood*/
{
   unsigned int mask = 0xFFFF0000;
   unsigned int origin = b;
   b = (b & mask) >> 16 | (b & ~mask) << 16;
   
   mask = 0xFF00FF00;
   b = (b & mask) >> 8 | (b & ~mask) << 8;
   
   mask = 0xF0F0F0F0;
   b = (b & mask) >> 4 | (b & ~mask) << 4;
   
   mask = 0xCCCCCCCC;
   b = (b & mask) >> 2 | (b & ~mask) << 2;
   
   mask = 0xAAAAAAAA;
   b = (b & mask) >> 1 | (b & ~mask) << 1;
   
   printf("%u is the rev num of %u \n",b, origin);	
}

int BitsTwoAndSix(unsigned int num)
{
	unsigned int bit_two = 2;
	unsigned int bit_six = 32;
	
	int res =  ((num & bit_two) && (num & bit_six));
	
	printf("the num %d result = %d\n",num, res);
	
	return res;
}

int BitsTwoOrSix(unsigned int num) 
{
	unsigned int mask_two = 2;
	unsigned int mask_six = 32;
	unsigned int mask_two_and_six = 34;
	
	int res =  ((num & mask_two) || (num & mask_six) || (num & mask_two_and_six));
	
	printf("the num %d result = %d\n",num, res);
	
	return res;
}

int SwapBitThreeAndFive(unsigned int num) 
{	
	unsigned int origin = num;
	unsigned int third_bit = num & 4;
    unsigned int fifth_bit = num & 16;

    num -= third_bit + fifth_bit;
    num += (third_bit << 2) + (fifth_bit >> 2);

	printf("origin %d result = %d\n",origin, num);	
	
    return num;
}

int ClosestDivided16(unsigned int num)
{
	unsigned int origin = num;
	unsigned int n = 1;
	num /= 2;
	while (n < num)
	{
		n <<= 1;
	}
	
	printf("origin %d result = %d\n",origin, n);
	
	return n; 	
}

void SwapWithTwo(unsigned int *a, unsigned int *b)
{
	printf("before swap a = %d  b = %d \n",*a, *b);
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
	printf("after swap a = %d  b = %d \n",*a, *b);
}

int BitsTrueCount (unsigned int n)
{
	int origin = n;
	int counter = 0;
	
	while ( n )
	{
		if(n & 1)
		{
			++counter;
		}
		n >>= 1;
	}
	
	printf("the number of on bit in the number - %d are - %d \n",origin ,counter);
	
	return counter;	
	
}
int BitsTrueCountNoLoop ( int num)
{
	int origin = num;
	int counter = 0;
	
					
	while(num)
	{
		counter += g_mask[num & 15];
		num >>= 4; 
	}
			
	printf("the number of on bit in the number - %d are - %d \n",origin ,counter);
	
	return counter;	
	
}

void PrintFloatBits(float f_number)
{
    int *ptr = (int*)(&f_number);
    int i = 0;
    int num = 1;
    printf("%f\n\n", f_number);
    
    num <<= 30;
        
    printf(" %d", ( f_number < 0 ) ); 
    
    for( ; i<=30 ;i++)
    {
        printf(" %d",(0 != (*ptr & num)));    
        num >>= 1;
    }
    
    puts("");  
    puts("");    
}

