/****************************************************************************
 *  FILENAME:  ex1.c     NAME:  Daniel Zaken     REVIEWER:  Peleg Rosenbaum *
 *                                                                          *
 *  POURPOSE:  Swaping ints                                                 *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>  /*Required Standart input output*/ 
#include <assert.h>  /*for assert*/

/* prototypes */
void SwapInt(int*, int*); 

int main()
{
	/*test 1*/
	int a = 3, b = 5;
	printf("a=%d,b=%d\n",a,b);
	SwapInt(&a, &b);
	printf("a=%d,b=%d\n",a,b);
	
	/*test 2*/	
	a = 7, b = 34;
	printf("a=%d,b=%d\n",a,b);
	SwapInt(&a, &b);
	printf("a=%d,b=%d\n",a,b);
	
	return 0;
}

void SwapInt(int *a, int *b)
{	
	int temp = 0;
	
	assert(a);
	assert(b);
	
	temp = *a;
	*a = *b;
	*b = temp;
}






