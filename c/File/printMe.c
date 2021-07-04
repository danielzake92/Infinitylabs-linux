/****************************************************************************
 *  FILENAME:  PrintMe.c  NAME:  Daniel Zaken    REVIEWER:  Nitzan Holmes   *
 *                                                                          *
 *  POURPOSE:  PrintMe implementaion.                                       *
 *                                                                          *
 ****************************************************************************/
#include <stdio.h>
#define SIZE 10
void PrintInt(int num);

typedef struct print_me
{
	int num;
	void (*Print) (int); 	
} print_me_t;

int main()
{
	print_me_t a[SIZE] = {0};
	int i = 0;
	
	for(; i < SIZE; ++i)
	{
		a[i].num = i + 1 ;
		a[i].Print = PrintInt; 
		a[i].Print( a[i].num );
	}
		
	return 0;
}

void PrintInt(int num)
{
	printf("The in num is - %d\n", num);
}


