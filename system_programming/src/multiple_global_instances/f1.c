#include <stdio.h>

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"

int iii;

void function_in_f1_file(void)
{
	++iii;
	printf(YELLOW"Hi from function_in_f1_file from f1.c;  ");
	printf(YELLOW"Value of iii is: "GREEN"%d"YELLOW";   Address of iii is: "GREEN"%p\n", iii, &iii);
}
