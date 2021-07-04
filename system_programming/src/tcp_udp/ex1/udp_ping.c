/*****************************************************************************
 *	FILENAME:	udp_ping.c              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:	Itamar Aron													 *
 *																			 *
 *	PURPOSE:    UDP Protocol               					    		     *
 *																			 *
 *****************************************************************************/
#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket api
#include <unistd.h> //sleep
#include <netinet/in.h> // for sin family 
#include <netinet/ip.h> // ip communication 
#include <sys/types.h> // portability with BSD 

#include "tcp_udp.h"
/*****************************************************************************/
#define BUFFER_SIZE 8
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

    InitServer(&srv_addr, PORT);

    socklen_t len  = sizeof(srv_addr);
    int n = 0;
    const char *ping = "ping";
    size_t i = 0;

    for(i = 0 ; i < COUNTER; ++i)
    {
        sendto(socket_fd, ping, strlen(ping), MSG_CONFIRM,
            (const struct sockaddr*)&srv_addr, len);


        n = recvfrom(socket_fd, buffer, BUFFER_SIZE, MSG_WAITALL,
                    (struct sockaddr*)&srv_addr, &len);

        buffer[n] = 0;

        printf("client : %s\n", buffer);
        sleep(1);
    }

    close(socket_fd);

    return 0;
}
