/*****************************************************************************
* FILE:      ping_pong.h	           PURPOSE: Signals Ping Pong
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  Liad Oz                   STATUS: IMPL Tested
******************************************************************************/
/*INCLUDES*/
#include <stdlib.h>/*For exit status*/
#include <stdio.h> /*Basic prints*/
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> /*wait*/
#include <unistd.h> /*fork*/
#include <errno.h> /*perror*/
#include <signal.h> 

#include "ping_pong.h"

/*ex1*/
static void SIGUSR1_Handler(int signal_number);
static void SIGUSR2_Handler(int signal_number);

/*ex2*/
static void EX2_SIGUSR2_Handler(int signal_number);

/****************************************************************************/
/*                                   IMPL  EX1 & EX2                        */
/****************************************************************************/
pp_status_t PP_EX1( const char *path,char *const argv[])
{
    pid_t current_pid = -1;
    pp_status_t status = SUCCESS;
    struct sigaction sa = {0};

    (void)path;
    (void)argv;

    sa.sa_handler = &SIGUSR1_Handler;
    sigaction (SIGUSR1, &sa, NULL);

    sa.sa_handler = &SIGUSR2_Handler;
    sigaction (SIGUSR2, &sa, NULL);

    current_pid = fork();

    /*what if fork has failed*/
    if( FORK_ERR == current_pid) 
    {
        perror("FORK_ERR");
        return FORK_ERR;
    }

    /*if parent process than ...*/
    if( 0 < current_pid )
    {
        while( SUCCESS == status )
        {
            status = kill(current_pid, SIGUSR1);
            pause(); 
        }
     
        /*handleing returned status from child process*/
        wait(&status);
        if(EXEC_ERR == WEXITSTATUS(status))
        {
            perror("EXEC_ERR");
            return EXEC_ERR;
        }    
        else if ( SUCCESS != WEXITSTATUS(status) )
        {
            perror("NEW_PROCESS_ERR");
            return NEW_PROCESS_ERR;
        } 
    }
    else /*else child process ...*/
    {
        while(1 && SUCCESS == status )
        {
            sleep(1);
            status = kill(getppid(), SIGUSR2);
            pause();
        }
    }
   
    return status;

}
/****************************************************************************/
pp_status_t PP_EX2( const char *path,char *const argv[])
{
    pp_status_t status = SUCCESS;
    pid_t child_pid = -1;
	struct sigaction sa = {0};

    sa.sa_handler = &EX2_SIGUSR2_Handler;
    sigaction (SIGUSR2, &sa, NULL);

    child_pid = fork();

	if( 0 == child_pid)
	{
        execv(path, argv);
	}

    pause();

    while( SUCCESS == status )
	{
        printf("Pong\n");
        status = kill(child_pid, SIGUSR1);

        pause();
     
	}
    wait(&child_pid);

    return status;
}
/****************************************************************************/
static void EX2_SIGUSR2_Handler(int signal_number)
{
    (void)signal_number;
    sleep(1);   
}
/****************************************************************************/
static void SIGUSR1_Handler(int signal_number)
{
    (void)signal_number;
    write(STDOUT_FILENO, "ping\n", 6);
} 
/****************************************************************************/
static void SIGUSR2_Handler(int signal_number)
{
    (void)signal_number;
    write(STDOUT_FILENO, "pong\n", 6);
    sleep(1);   
}
/****************************************************************************/
#if 0
pp_status_t Spawn( const char *path,char *const argv[], pid_t *current_pid)
{
    int status = SUCCESS;

    assert(path);
    assert(argv);

    *current_pid = fork();

    if( FORK_ERR == *current_pid) 
    {
        perror("FORK_ERR");
        return FORK_ERR;
    }

    if( 0 < *current_pid )
    {
        wait(&status);
        if(EXEC_ERR == WEXITSTATUS(status))
        {
            perror("EXEC_ERR");
            return EXEC_ERR;
        }    
        else if ( SUCCESS != WEXITSTATUS(status) )
        {
            perror("NEW_PROCESS_ERR");
            return NEW_PROCESS_ERR;
        } 
    }
    else
    {
        execv(path,argv);
        perror("EXEC_ERR");
        return EXEC_ERR;
    }

    return status;
}
#endif
/****************************************************************************/
#if 0
pp_status_t PP_EX3( const char *path,char *const argv[])
{
    pp_status_t status = SUCCESS;
    pid_t ex3_pid = 0;

	struct sigaction sa = {0};
    sa.sa_handler = &EX3_SIGUSR2_Handler;
    sigaction(SIGUSR2, &sa, NULL);

    ex3_pid = atoi(argv[1]);

    printf("ex3_pid = %d\n", ex3_pid);

    kill(ex3_pid, SIGUSR1);
    /*pause();*/

    while(1 && SUCCESS == status )
	{
        while( 0 == g_is_sig2_accept)
        {
            /*busy*/
        }
        printf("Pong\n");
        sleep(1);   
        status = kill(ex3_pid, SIGUSR1);
        g_is_sig2_accept = 0;

	}
    wait(&ex3_pid);

    (void)path;

    return status;
}

static void EX3_SIGUSR2_Handler(int signal_number)
{
    (void)signal_number;
    g_is_sig2_accept = 1;
    sleep(1);   
}
#endif
/****************************************************************************/

