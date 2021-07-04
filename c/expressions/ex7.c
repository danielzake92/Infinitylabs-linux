/****************************************************************************
*  FILENAME:  ex7.c     NAME:  Daniel Zaken     REVIEWER:  Nitzan Holmes    *
 *                                                                          *
 *  POURPOSE:     Swaping int                                               *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>  /*Required Standart input output */

/* prototypes*/
void SwapInt(int*, int*); 

int main()
{
	/*test 1*/
	int a = 3, b = 5;
	printf("_a=%d,_b=%d\n",a,b);
	SwapInt(&a, &b);
	printf("a=%d,b=%d\n",a,b);
	
	/*test 2	*/
	a = 7, b = 34;
	printf("_a=%d,_b=%d\n",a,b);
	SwapInt(&a, &b);
	printf("a=%d,b=%d\n",a,b);
	
	return 0;
}

void SwapInt(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}






