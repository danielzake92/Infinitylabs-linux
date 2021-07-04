#include <stdio.h>
#include <stdlib.h>
#include "ping_pong.h"

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"

ex_t g_func_lut[2] = {PP_EX1, PP_EX2};

int main(int argc, char *argv[])
{
	char *args[3] = {NULL};
	int num = atoi(argv[1]);

	args[0] = "./pong.out";
	args[1] = argv[2];
	args[2] = NULL;

	(void)argc;


	if( EX1 == num )
	{
		printf ("%s*****************************************\n",GREEN);
		printf ("%s---------------EX1 tests-----------------\n",GREEN);
		printf ("%s*****************************************",GREEN);
		puts(DEFAULT);
	}
	else if( EX2 == num )
	{
		printf ("%s*****************************************\n",GREEN);
		printf ("%s---------------EX2 tests-----------------\n",GREEN);
		printf ("%s*****************************************",GREEN);
		puts(DEFAULT);
	}

	g_func_lut[num](args[0], args);
		
	return 0;
}
