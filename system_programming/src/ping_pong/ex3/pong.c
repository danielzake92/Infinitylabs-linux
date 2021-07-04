#include <stdlib.h>/*For exit status*/
#include <stdio.h> /*Basic prints*/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*sleep*/
#include <signal.h> 

static sig_atomic_t g_ping_pid = 0;
int g_is_sig1_accept = 0;

static void SIGUSR1_Handler(int sig, siginfo_t *info, void *ucontext);

int main()
{
	struct sigaction sa = {0};

	sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &SIGUSR1_Handler;
    sigaction(SIGUSR1, &sa, NULL);
	
	pause();

	while( 1 )
	{
		printf("Ping\n");
        kill(g_ping_pid, SIGUSR2);
        g_is_sig1_accept = 0;

        while( 0 == g_is_sig1_accept)
        {
            /*busy*/
        }
	}

	return 0;
}

static void SIGUSR1_Handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	g_ping_pid = info->si_pid;
	g_is_sig1_accept = 1;
	sleep(1);
}
          



