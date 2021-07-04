/****************************************************************************
 *  FILENAME:  ex4.c      NAME:  Daniel Zaken    REVIEWER:  Peleg Rosenbaum *
 *                                                                          *
 *  POURPOSE:  Swap size_t, Swap size_t*                                    *
 *                                                                          *
 ****************************************************************************/
/*INCLUDE*/
#include <stdio.h> /*Required Standart input output*/
#include <stdlib.h> /*Required for allocation*/
#include <assert.h>  /*For assert*/

/*DECLERATION*/
void SwapSizet (size_t *,size_t *);
void SwapSizetPtr (size_t **, size_t **);

int main()
{
	size_t a=10, b=20;
	size_t *ptr_a = &a;
	size_t *ptr_b = &b;
			
	/*test 1*/	
	printf("vals : a = %lu,  b = %lu\n",a, b);
	
	SwapSizet(&a, &b);
	
	printf("vals : a = %lu,  b = %lu\n",a ,b);
	
	/*test 2*/	
	printf("adrs : ptr_a = %p,  ptr_b = %p\n",(void*)ptr_a,(void*)ptr_b);
	
	SwapSizetPtr(&ptr_a, &ptr_b); 
		
	printf("adrs : ptr_a = %p,  ptr_b = %p\n",(void*)ptr_a,(void*)ptr_b);
			
	return 0;
}

void SwapSizet (size_t *a,size_t *b)
{
	size_t temp = 0;
	
	assert(a);
	assert(b);
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void SwapSizetPtr (size_t **a, size_t **b)
{
	assert(a);
	assert(b);	
	
	SwapSizet ((size_t *)a, (size_t *)b);
}







