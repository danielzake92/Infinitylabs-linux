#include <stdlib.h>/*For exit status*/
#include <stdio.h> /*Basic prints*/
#include <string.h> /*memset*/
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> /*wait*/
#include <unistd.h> /*fork*/
#include <signal.h> 

#include "ping_pong.h"

static int g_is_sig1_accept = 0;

static void SIGUSR1_Handler(int signal_number);

int main()
{
	pp_status_t status = SUCCESS;
	struct sigaction sa = {0};

    sa.sa_handler = &SIGUSR1_Handler;
    sigaction (SIGUSR1, &sa, NULL);
	
	/*I process*/
	kill(getppid(), SIGUSR2);

	while(1 && SUCCESS == status )
	{
		printf("Ping\n");
        status = kill(getppid(), SIGUSR2);
        g_is_sig1_accept = 0;
		pause();

	}
	return EXIT_SUCCESS;
}

static void SIGUSR1_Handler(int signal_number)
{
	(void)signal_number;
    g_is_sig1_accept = 1;
    sleep(1);
}

