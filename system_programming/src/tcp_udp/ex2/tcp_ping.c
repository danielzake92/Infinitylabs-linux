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
#include <fcntl.h> /* O_CREAT flag in sem init */
#include <sys/stat.h> //S_IRWXU
#include <semaphore.h> //semaphore

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

    // socket create
    if( 0 > (socket_fd = socket(AF_INET, SOCK_STREAM, 0) ))
    {
        return TCP_ERR;
    }

    InitServer(&srv_addr, PORT);

    printf("client : ask for connect\n");

    socklen_t len  = sizeof(srv_addr);
    if( 0 > (connect(socket_fd,(const struct sockaddr*)&srv_addr, len)))
    {
        printf("connect err\n");
        return TCP_ERR;
    }


    Ping(socket_fd);
    Ping(socket_fd);
    
    sem_t *sem = NULL;
    sem = sem_open("/sem",O_CREAT,S_IRWXU,0);

    close(socket_fd);

    sem_post(sem);
    sem_close(sem);
    
    return 0;
}
