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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> //wait
#include <fcntl.h> 
#include <string.h>

#define BUFFER_SIZE 6
#define COUNTER 3

int main()
{
    int fd_write = 0;
    int fd_read = 0;
    char buffer[BUFFER_SIZE] = {0};
    size_t n = 0;

    fd_read = open("ping_pipe.txt", O_RDONLY);//ptc
    fd_write = open("pong_pipe.txt", O_WRONLY);//ctp

    for(n = 0; n < COUNTER; ++n)
    {
        read(fd_read,buffer, BUFFER_SIZE );
        printf("%s\n", buffer);
        
        sleep(1);
        
        write(fd_write, "pong", 5);
    }

    close(fd_write);
    close(fd_read);

    unlink("ping_pipe.txt");
    unlink("pong_pipe.txt");

    
    return 0;
}
