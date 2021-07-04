#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>/*For exit status*/

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"

sig_atomic_t current_pid = 0;
sig_atomic_t parent_pid = 0;

int main()
{
	current_pid = getpid();
	parent_pid = getppid();
	

	puts("***************************************");
	printf(YELLOW"Welcome to dummy program\n");
	printf(YELLOW"current pid = %d\nparent parent pid = %d\n", current_pid, parent_pid);
	puts("***************************************"DEFAULT);

	return EXIT_SUCCESS;
}
