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
/*****************************************************************************/

int main()
{
    int fd_write = 0;
    int fd_read = 0;
    char buffer[BUFFER_SIZE] = {0};
    size_t n = 0;
    
    mkfifo("ping_pipe.txt", S_IRWXU);//ptc
    mkfifo("pong_pipe.txt", S_IRWXU);//ctp
    
    fd_write = open("ping_pipe.txt", O_WRONLY);//ptc
    fd_read = open("pong_pipe.txt", O_RDONLY);//ctp


    for(n = 0; n < COUNTER; ++n)
    {
        write(fd_write, "ping", 5);

        read(fd_read,buffer, BUFFER_SIZE );
        printf("%s\n", buffer);

        sleep(1);
    }

    close(fd_write);
    close(fd_read);

    return 0;
}
//sysconf(_SC_PAGE_SIZE)
//O_RDONLY