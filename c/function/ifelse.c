/****************************************************************************
 *  FILENAME:  ifelse.C   NAME:  Daniel Zaken   REVIEWER:  Peleg Rosenbaum  *
 *                                                                          *
 *  POURPOSE:  if else implementation                                       *
 *                                                                          *
 ****************************************************************************/
 
/*INCLUDE*/
#include <stdio.h>  /*required standart output*/
#include <stdlib.h>  /*required for exit*/
#define esc 27

void KeyBoardClick (void);

int main()
{
	KeyBoardClick();
	return 0;
}

void KeyBoardClick (void)
{
	char ch = 0;
	
	puts("press any key, to exit press esc");
	
	system("stty -icanon -echo");
	
	do
	{	
		ch = getchar();
		if (ch == 'A' )
		{
			puts("A pressed");
			continue;
		}
		if (ch == 'T')
		{
			puts("T pressed");
			continue;
		}
		if (ch == esc)
		{
			puts("esc pressed");
			break;
		}
			
	} while(1);
	system("stty icanon echo");
	exit(0);
}
