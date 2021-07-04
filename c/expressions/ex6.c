/****************************************************************************
 *  FILENAME:  ex6.c     NAME:  Daniel Zaken     REVIEWER:  Nitzan Holmes   *
 *                                                                          *
 *  POURPOSE:  int inversing                                                *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>  /*Required Standart input output */

/*prototypes*/
int Rotate(int); 
void Test(int, int);

int main()
{
	/*TESTS*/
	Test(Rotate(0),0);  
	Test(Rotate(1),1); 
	Test(Rotate(10),1);  
	Test(Rotate(20),2);	
	Test(Rotate(12340),4321); 
	Test(Rotate(12340345),54304321);  
	Test(Rotate(2140483631),1363840412);  
	Test(Rotate(36000),63);  
	Test(Rotate(-24000),-42);  
		
	return 0;
}

int Rotate(int num)
{
		
	int res = 0;
		
	while(num)
	{
	res = num % 10 + res * 10;  /*the mod 10 get the last digit and *10 pushes it*/
	
	num /= 10;  /*when reaches to zero the loop is over*/
	}
		
	return res;  
}

/*
 *    Test - Rotate INT
 */	
void Test(int res,int correct)
{

	if (res==correct)
	{
		printf ("%d - ", correct);
		printf ("\033[32;1m OK \033[0m\n");
	}
	else
	{
		printf ("%d - ", res);
		printf ("\033[31;1m NOT OK \033[0m\n");
	}
}	




