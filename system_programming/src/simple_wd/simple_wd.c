/*****************************************************************************
* FILE:      simple_wd.c	           PURPOSE: Simple watchdog entrance point    
* DEVELOPER: Daniel Zaken              TEAM:    Yellow                       
*                                                                               
* REVIEWER:  		                   STATUS: Imp tested                          
******************************************************************************/
/*INCLUDES*/
#include <stdlib.h>/*For exit status*/
#include <stdio.h> /*Basic prints*/
#include <assert.h> /*asserts*/
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> /*wait*/
#include <unistd.h> /*fork*/
#include <errno.h> /*perror*/

#include "simple_wd.h"




wd_status_t ForkExec( const char *path,char *const argv[])
{
    pid_t current_pid = -1;
    int status = SUCCESS;

    assert(path);
    assert(argv);

    while( 1 )
    {
        current_pid = fork();
        if( FORK_ERR == current_pid) 
        {
            perror("FORK_ERR");
            return FORK_ERR;
        }

        if( 0 < current_pid )
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

        sleep(1);
    }
    return status;
}

wd_status_t SysExec( const char *path,char *const argv[])
{
    wd_status_t status = SUCCESS;

    assert(path);
    assert(argv);

    while( 1 )
    {
        status = system(path);

        if( FORK_ERR == status)
        {
            perror("FORK_ERR");
            return FORK_ERR;
        }

        if( SHELL_ERR == status)
        {
            perror("SHELL_ERR");
            return SHELL_ERR;
        }
        
        sleep(1);
    }
    return status;
}