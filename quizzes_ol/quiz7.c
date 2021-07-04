#include <stdio.h>

void SwapInt1(int *a, int *b);
void SwapInt2(int *a, int *b);
void SwapInt3(int *a, int *b);
int BitCountsInByte(char b);

int main()
{
	int a = 5, b = 7;

	printf("(%d, %d)\n",a, b);
	
	SwapInt1(&a, &b);
	printf("(%d, %d)\n",a, b);

	SwapInt2(&a, &b);	
	printf("(%d, %d)\n",a, b);
	
	SwapInt3(&a, &b);	
	printf("(%d, %d)\n",a, b);
	
	printf("%d\n",BitCountsInByte(118));
	
	return 0;
}

void SwapInt1(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	
}
void SwapInt2(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
void SwapInt3(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int BitCountsInByte(char b)
{
	int count = 0;
	int i = 7;
	while(i > 0)
	{
		if ( ( b>>i & 3 ) == 3 )
		{
			++count;
		}
		
		--i;
	}
	return count;
}

int BitCounter(unsigned int n)
{
    int counter = 0;
    
    while(n)
    {
        ++counter;
        n &= (n-1);
    }
    return counter;
}





