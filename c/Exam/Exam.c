#include <stdio.h>
#include <string.h>
#include <assert.h>
/***********************************************************************************/
int FlipDigitsInNum(int num);
unsigned char ByteMirror(unsigned char num);
int BitCounts(unsigned char c);
char RotateLeft(char byte, unsigned int nbits);
void PtrSwap(int **p1, int **p2);
char *StrnCpy(char *dest, const char *src, size_t n);
int FlipBit(int val, unsigned int n);
unsigned long GetFibonacciElement(unsigned int n);
int Multiple(int num);
char * IntToString(int num, char *str);
void ReverseString(char *str);
/***********************************************************************************/
static unsigned char LUT[16] =
	{
		0 , 8 , 4 , 12,
		2 , 10, 6 , 14,
		1 , 9 , 5 , 13,
		3 , 11, 7 , 15
	};
/***********************************************************************************/
int main()
{	
	char *s1 = "hello";
	char s2[] ="hello";
	
	int a = 5;
	int b = 7;
	int *ptr_a = &a;
	int *ptr_b = &b;
	
	printf(" num : %d  inversed num : %d\n", 58, FlipDigitsInNum(58)); /*85*/
	printf(" num : %d  inversed num : %d\n", -520, FlipDigitsInNum(-520)); /*-25*/
/***********************************************************************************/	
	printf(" num : %d  mirrored num : %d\n", 5, ByteMirror(5)); /*160*/
/***********************************************************************************/	
	printf(" num : %d  on bits num : %d\n", 69, BitCounts(69)); /*4*/
	printf(" num : %d  after rotation of 11 : %d\n", 75, RotateLeft(75, 11)); /*90*/
	printf(" num : %d  after rotation of 11 : %d\n", 8, RotateLeft(8, 11)); /*64*/
/***********************************************************************************/	
	printf(" num : %d  after turning off bit 1 : %d\n", 5, FlipBit(5, 1)); /*7*/
/***********************************************************************************/
	printf("adrs : ptr_a = %p,  ptr_b = %p\n",(void*)ptr_a,(void*)ptr_b);
	PtrSwap(&ptr_a, &ptr_b); 
	printf("adrs : ptr_a = %p,  ptr_b = %p\n",(void*)ptr_a,(void*)ptr_b);
/***********************************************************************************/	
	printf("Fibonacci Index : %d  Fibonacci num : %lu\n", 1, GetFibonacciElement(1));
	printf("Fibonacci Index : %d  Fibonacci num : %lu\n", 2, GetFibonacciElement(2));
	printf("Fibonacci Index : %d  Fibonacci num : %lu\n", 3, GetFibonacciElement(3));
	printf("Fibonacci Index : %d  Fibonacci num : %lu\n", 4, GetFibonacciElement(4));
	printf("Fibonacci Index : %d  Fibonacci num : %lu\n", 5, GetFibonacciElement(5));
	printf("Fibonacci Index : %d  Fibonacci num : %lu\n", 6, GetFibonacciElement(6));
	printf("Fibonacci Index : %d  Fibonacci num : %lu\n", 7, GetFibonacciElement(7));
/***********************************************************************************/	
	printf(" num : %d  after multiplying by 8 : %d\n", -8, Multiple(-8)); 
/***********************************************************************************/	
	
	printf("%lu %lu %lu %lu\n", sizeof(s1), sizeof(s2), strlen(s1), strlen(s2)); 
	
	
	
	return 0;
}
/***********************************************************************************/
int FlipDigitsInNum(int num)
{
	int res = 0;
	int minus = 1;
	
	if(num < 0)
	{
		minus = -1;
		num *= -1;
	}
	
	while(num)
	{
		res = res*10 + num % 10;
		num /= 10;
	}
	return(res * minus);	
}
/***********************************************************************************/
unsigned char ByteMirror(unsigned char num)
{
	unsigned char res = 0;
	res = LUT[num & 0xF];
	res <<= 4;
	res |= LUT[(num >> 4) & 0xF ];
	return res;
}
/***********************************************************************************/
int BitCounts(unsigned char c)
{
	int count = 0;
	while(c)
	{
		++count;
		c = c & (c-1);
	}
	return count;
}
/***********************************************************************************/
char RotateLeft(char byte, unsigned int nbits)
{
	int rot = nbits % 8;
	char temp = byte >> (8 - rot);
	
	byte <<= rot;
	byte |= temp;
	return byte;
}
/***********************************************************************************/
void PtrSwap(int **p1, int **p2)
{
	int *temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
/***********************************************************************************/
char *StrnCpy(char *dest, const char *src, size_t n)
{
    char *dest_start = NULL;
    char *dest_end = NULL;
    assert(dest);
    assert(src);    
    
    dest_start = dest;
    dest_end = dest + n;
            
    while (dest < dest_end)
    {    
        if(!*src) /*arrived to NULL*/
        {
            *dest = '\0';
            ++dest;
        }
        else
        {
            *dest = *src;
			++dest;
			++src;
        }
    }
    
    *dest = '\0';    
    
    return dest_start ;
}
/***********************************************************************************/
int FlipBit(int val, unsigned int n)
{
	return( val ^ (1 << n) );
}
/***********************************************************************************/
unsigned long GetFibonacciElement(unsigned int n)
{
	int a = 0;
	int b = 1;
	int res = 1;
	
	while(n - 1)
	{
		res = a + b;
		a = b;
		b = res;
		--n;
	}
	return res;	
}
/***********************************************************************************/
int Multiple(int num)
{
	return(num << 3);
}
/***********************************************************************************/
char *IntToString(int num, char *str)
{	
	char *start = NULL;
	int minus = 1;
	printf("here");	
	
	
	assert(str);	
	
	start = str;
		
	if(num < 0)
	{
		minus = -1;
		num *= -1;
	}
	
	while(num)
	{	
		*str = (num % 10) + '0';
		num /= 10;
		++str;
	}
	
	if( minus == -1 )
	{
		*str = '-';
		++str;
	}
	
	*str = '\0';
	
	ReverseString( start );
	
	return( start );
}

void ReverseString(char *str)
{
	char *s = NULL;
	char *e = NULL;
	char temp = 0;
	assert(str);
	s = str;
	e = str + strlen(str);	
	
	while(s < e)
	{
		temp = *s;
		*s = *e;
		*e = temp;
		++s;
		++e;
	}
}


