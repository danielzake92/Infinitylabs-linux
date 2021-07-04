/****************************************************************************
 *  FILENAME:  SwitchCase.c  NAME: Daniel Zaken REVIEWER:  Peleg Rosenbaum  *
 *                                                                          *
 *  POURPOSE:  Switch case implementation                                   *
 *                                                                          *
 ****************************************************************************/

/*INCLUDE*/
#include <stdio.h>  /*required standart output*/
#include <stdlib.h>  /*required for exit*/
#define esc 27

void KeyBoardClick (void);
void CharPrint (unsigned char ch);

int main()
{
	KeyBoardClick();
	return 0;
}

void CharPrint (unsigned char ch)
{
	printf("%c Pressed\n", ch);
}

void KeyBoardClick (void)
{
	char ch = 0;
	
	puts("press any key, to exit press esc");
	system("stty -icanon -echo");
	
	do
	{	
		ch = getchar();
		
		switch (ch) 
		
		{
			case 'A' :
			{
				CharPrint(ch);
				continue;
			}
			case 'T' :
			{
				CharPrint(ch);
				continue;
			}
			case esc :
			{
				system("stty icanon echo");
				exit(0);
			}
			default :
			{
				break;
			}
		}
			
	} while(1);
	
}
