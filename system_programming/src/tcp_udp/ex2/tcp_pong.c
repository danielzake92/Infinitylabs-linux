/*****************************************************************************
 *	FILENAME:	tcp.pong                 AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:	Itamar Aron													 *
 *																			 *
 *	PURPOSE:    TCP Protocol            					    		     *
 *																			 *
 *****************************************************************************/
#include <stdio.h> //printf
#include <sys/socket.h> //sockets
#include <unistd.h> //sleep
#include <netinet/ip.h> // ip communication 
#include <semaphore.h> //semaphore
#include <fcntl.h> /* O_CREAT flag in sem init */
#include <sys/stat.h> //S_IRWXU

#include "tcp_udp.h"
/*****************************************************************************/
#define BUFFER_SIZE 8
#define PORT 8030
/*****************************************************************************/
typedef enum tcp_status
{
    TCP_ERR = -1,
    TCP_SUCCESS = 0
}tcp_status_t;


int main()
{
    int socket_fd = 0; 

    struct sockaddr_in srv_addr = {0};
    struct sockaddr_in cli_addr = {0};

    // socket create
    if( 0 > (socket_fd = socket(AF_INET, SOCK_STREAM, 0) ))
    {
        return TCP_ERR;
    }

    // init srv adr
    InitServer(&srv_addr, PORT);

    //setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (int*)1, sizeof(int));

    // bind socket into 
    if( 0 > (bind(socket_fd, (const struct sockaddr*)&srv_addr,
             sizeof(srv_addr))) )
    {
        return TCP_ERR;
    }

    printf("server : bind to port\n");

    // server listen
    if( TCP_ERR == (listen(socket_fd,1) ))
    {
        return TCP_ERR;
    }

    printf("server : listening\n");

    //server accept
    socklen_t len  = sizeof(cli_addr);
    int confirm_fd = accept(socket_fd,(struct sockaddr*)&cli_addr, &len);
    if(0 > confirm_fd)
    {
        return TCP_ERR;
    }

    printf("server : accepted\n");

    Pong(confirm_fd);
    Pong(confirm_fd);

    sem_t *sem = NULL;
    sem = sem_open("/sem",O_CREAT,S_IRWXU,0);
    sem_wait(sem);

    close(confirm_fd);
    close(socket_fd);

    sem_close(sem);
    sem_unlink("sem");

    return 0;
}

