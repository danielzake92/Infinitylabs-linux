/*****************************************************************************
 *	FILENAME:	unnamed_pipe.c            AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for ipc lib.					    		     *
 *																			 *
 *****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h> //printf & read & write
#include <unistd.h> //sleep
#include <sys/wait.h> //wait

#define COUNTER 3
#define BUFFER_SIZE 16

typedef enum UP_STATUS
{
    FORK_ERR = -1,
    SUCCESS = 0,
}up_status_t;

/*****************************************************************************/

void ClosePipes(int *p1, int *p2);

void ClosePipes(int *p1, int *p2)
{
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
}

int main()
{
    pid_t child_pid = 0;
    int parent_write_child_read[2] = {0};//0 is read 1 is write
    int child_write_parent_read[2] = {0};//0 is read 1 is write
    char buffer[BUFFER_SIZE];
    size_t n = 0;

    pipe(parent_write_child_read);
    pipe(child_write_parent_read);

    /* forking to child process */
    child_pid = fork();
    if( FORK_ERR == child_pid )
    {
        return FORK_ERR;
    }

    if ( 0 == child_pid ) /* child_process */
    {
        for( n = 0; n < COUNTER; n++)
        {
            read(parent_write_child_read[0], buffer, BUFFER_SIZE);
            printf("%s\n",buffer);
            sleep(1);
            write(child_write_parent_read[1],"pong", 5 );
        }
        ClosePipes(parent_write_child_read,child_write_parent_read);
        return SUCCESS;
    }
    for( n = 0; n < COUNTER; n++)
    {
        write(parent_write_child_read[1],"ping", 5 );
        read(child_write_parent_read[0], buffer, BUFFER_SIZE);
        printf("%s\n",buffer);
        sleep(1);
    }

    wait(NULL);

    ClosePipes(parent_write_child_read,child_write_parent_read);
    return SUCCESS;
}
