/*****************************************************************************
 *	FILENAME:	udp_cli1.c         AUTHOR: Daniel Zaken  LAB: RD100	         *
 *																			 *
 *	REVIEWER:	Itamar Aron													 *
 *																			 *
 *	PURPOSE:    UDP Broadcas Protocol.	    				    		     *
 *																			 *
 *****************************************************************************/
#include <stdio.h> //printf
#include <string.h> // strlen
#include <sys/socket.h>
#include <unistd.h> //sleep
#include <netinet/in.h> // for sin family 
#include <netinet/ip.h> // ip communication 
#include <sys/types.h> // portability with BSD 

#include "tcp_udp.h"
/*****************************************************************************/
#define BUFFER_SIZE 128
#define PORT 8080
#define COUNTER 3

/*****************************************************************************/
typedef enum udp_status
{
    UDP_BIND_ERR = -1,
    UDP_SOCKET_ERR = -1,
    UDP_SUCCESS = 0
}udp_status_t;

int main()
{
    int socket_fd = 0; 
    char buffer[BUFFER_SIZE];

    struct sockaddr_in srv_addr = {0};

    if( 0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0) ))
    {
        return UDP_SOCKET_ERR;
    }

    int broadcast = 1;

    setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&broadcast,sizeof(int));

    InitServer(&srv_addr, PORT);

        // bind socket into 
    if( 0 > (bind(socket_fd, (const struct sockaddr*)&srv_addr,
             sizeof(srv_addr))) )
    {
        printf("bind err\n");
        return UDP_BIND_ERR;
    }

    socklen_t len  = sizeof(srv_addr);
    int n = 0;

    
    n = recvfrom(socket_fd, buffer, BUFFER_SIZE, MSG_WAITALL,
                (struct sockaddr*)&srv_addr, &len);
    buffer[n] = 0;
    printf("client : %s", buffer);
    sleep(1);

    close(socket_fd);

    return 0;
}
