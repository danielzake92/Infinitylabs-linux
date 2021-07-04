/****************************************************************************
 *  FILENAME:  LUT.C      NAME:  Daniel Zaken   REVIEWER:  Peleg Rosenbaum  *
 *                                                                          *
 *  POURPOSE:  LUT Array for 256 function ptrs                              *
 *                                                                          *
 ****************************************************************************/

/*INCLUDE*/
#include <stdio.h>  /*required standart output*/
#include <stdlib.h>  /*required for exit*/
#define ESC 27
#define SIZE 256

void LUTclick (void);

void CharPrint (unsigned char ch);

typedef void (*print_ptr_t)(unsigned char);

int main()
{
	system("stty -icanon -echo");
	
	LUTclick();	
	
	system("stty icanon echo");
	return 0;
}

void CharPrint (unsigned char ch)
{
	printf("%c Pressed\n", ch);
}

void Nothing (unsigned char ch)
{
	(void)ch;
}


void LUTclick (void)
{
	unsigned char ch = 0 ;
	int i = 0;
	static print_ptr_t PtrArr[SIZE] = {NULL};
	
	for (; i < SIZE ;i++)
	{
		PtrArr[i] = Nothing;
	}
	
	PtrArr['A'] = CharPrint;
	PtrArr['T'] = CharPrint;
	
	while(ch != ESC)
	{	
		ch = getchar();
		(PtrArr[ch])(ch);
	}
	
}

