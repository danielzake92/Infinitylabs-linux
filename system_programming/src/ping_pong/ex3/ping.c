#include <stdlib.h>/*For atoi*/
#include <stdio.h> /*Basic prints*/
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> /*wait*/
#include <unistd.h> /*sleep*/
#include <signal.h> 

static int g_is_sig2_accept = 0;

void EX3( pid_t pong_pid);
static void EX3_SIGUSR2_Handler(int signal_number);

int main(int argc, char *argv[])
{
	pid_t pong_pid = 0;
	(void)argc;

	if( argv[0] == NULL )
	{
		printf("Command line arg error\n");
		return EXIT_SUCCESS;
	}

	pong_pid = atoi(argv[1]);

	EX3(pong_pid);

	return 0;
}

void EX3( pid_t pong_pid)
{

	struct sigaction sa = {0};
    sa.sa_handler = &EX3_SIGUSR2_Handler;
    sigaction(SIGUSR2, &sa, NULL);

    kill(pong_pid, SIGUSR1);

    while( 1 )
	{
        while( 0 == g_is_sig2_accept)
        {
            /*busy*/
        }
        printf("Pong\n");
        kill(pong_pid, SIGUSR1);
        g_is_sig2_accept = 0;

	}
    wait(&pong_pid);

}

static void EX3_SIGUSR2_Handler(int signal_number)
{
    (void)signal_number;
    g_is_sig2_accept = 1;
    sleep(1);   
}
          



