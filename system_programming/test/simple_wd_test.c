#include <stdio.h>
#include <stdlib.h>
#include "simple_wd.h"

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"


spawn_t g_func_lut[FUNC_NUM] = {ForkExec,SysExec };

int main(int argc, char *argv[])
{
	char *args[] = {"./dummy.out", NULL};
	wd_status_t status = SUCCESS;

	(void)argc;

	if( FORKEXEC == atoi(argv[1]) )
	{
		printf ("%s*****************************************\n",GREEN);
		printf ("%s---------------FORK EXEC tests---------------\n",GREEN);
		printf ("%s*****************************************\n",DEFAULT);

	}
	else if( SYSTEM == atoi(argv[1]) )
	{
		printf ("%s*****************************************\n",GREEN);
		printf ("%s---------------SYSTEM tests---------------\n",GREEN);
		printf ("%s*****************************************\n",DEFAULT);
	}

	status = g_func_lut[atoi(argv[1])](args[0], args);
		
	printf("status = %d", status);

	return 0;
}
