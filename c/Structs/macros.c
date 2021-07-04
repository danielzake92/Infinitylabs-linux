/****************************************************************************
 * FILENAME: macros.c 	AUTHOR: Daniel Zaken		REVIEWER: Nitzan Holmes *
 *																			*
 * PURPOSE: 																*
 *																			*
 ****************************************************************************/

#include <stdio.h>

#define MAX2(a, b) ( (a) > (b) ? (a) : (b))
#define MAX3(a, b, c) ( MAX2((a), (b)) > (c) ? MAX2((a), (b)) : (c) )
#define SIZEOF_VAR(var) (char*)((&var)+1) - (char*)(&var)
#define SIZEOF_TYPE(type) (size_t)( (type *)0 + 1 )  
/****************************************************************************/
union numbers
{
	int i;
	float f;
	double d;
};

struct x
{
	int i;
	char c;
	double d;
	short s;
};

struct card
{
	int suit : 30;
	int face_value : 2;
};


int main()
{
	int a = 5, b = 8, c = 40;
	int res1 = MAX2(a, b);
	int res2 = MAX3(a, b, c);
	
	printf ("\033[34;1m----------MAX2----------\033[0m \n");/*blue msg*/	
	printf("The maximum of (%d, %d) is - %d\n",a ,b , res1);
	
	printf ("\033[34;1m----------MAX3----------\033[0m \n");/*blue msg*/
	printf("The maximum of (%d, %d, %d) is - %d\n",a ,b ,c , res2);
	
	printf ("\033[34;1m--------SIZEOF_VAR--------\033[0m \n");/*blue msg*/
	printf("The sizeof(int) is - %lu\n", SIZEOF_VAR(a));
	
	printf("The sizeof(char) is - %lu\n", SIZEOF_TYPE(char));
	printf("The sizeof(char*) is - %lu\n", SIZEOF_TYPE(char *));
	
	printf("The sizeof(union numbers) is - %lu\n", SIZEOF_TYPE(union numbers));
	printf("The sizeof(struct x) is - %lu\n", SIZEOF_TYPE(struct x));
	printf("The sizeof(struct card) is - %lu\n", SIZEOF_TYPE(struct card));
	
	return 0;
}
