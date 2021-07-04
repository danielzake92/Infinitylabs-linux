/****************************************************************************
 *  FILENAME:  ex5.c     NAME:  Daniel Zaken     REVIEWER:  Nitzan Holmes   *
 *                                                                          *
 *  POURPOSE:  Caculation of 10^n                                           *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>  /*Required Standart input output */

/* prototypes*/
float PowerN(int); 
 
void Test(float, float);

int main()
{
	Test(PowerN(-3),1/1000.0);  
	Test(PowerN(-1),1/10.0);  
	Test(PowerN(0),1); 
	Test(PowerN(1),10);  
	Test(PowerN(2),100);  
	Test(PowerN(4),10000); 
	
	return 0;
}

/*
 *    Calculates 10^exp
 */	
float PowerN(int exp)
{
	float base = 10;  
	float res = 1;  /*float for negetive exponent*/
	int i;  
	
	/*if the exponent is negetive we need to inverse base*/	
	if (0 > exp) 
	
	{
		exp = -exp;
		base = 1 / base;
	}
		
	for (i = 0; i < exp; ++i)
	
	{
		res *= base;
	}
	
	return res;
}

/*
 *    Tester 10^exp
 */														
void Test(float res,float correct)
{
	
	if (res==correct)  /*if correct*/
	{
		printf ("correct=%f - res=%f ", correct, res);  /*corect num*/
		printf ("\033[32;1m OK \033[0m\n");  /*grn msg*/
	}
	else  /*if wrong*/
	{
		printf ("correct=%f - res=%f ", correct, res);  /*mistaken num*/
		printf ("\033[31;1m NOT OK \033[0m\n");  /*red msg*/
	}
}	




