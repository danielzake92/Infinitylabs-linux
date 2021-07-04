/****************************************************************************
 *  FILENAME:  ex4.c     NAME:  Daniel Zaken     REVIEWER:  Nitzan Holmes   *
 *                                                                          *
 *  POURPOSE:  Printing "Hello World!" in HEX_Decimal                       *
 *                                                                          *
 ****************************************************************************/
 
#include <stdio.h>  /*Required Standart input output*/

void PrintHello(); 

int main()
{
	
	PrintHello();
	
	return 0;
}

void PrintHello()
{

	char ch[] ={0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f,
	0x72, 0x6c, 0x64, 0x21, 0x22, 0x0a, 0x00};  /*Assigning*/
	
	printf("%s",ch);

}
