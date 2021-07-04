/*****************************************************************************
 *	FILENAME:	udp_pong.c              AUTHOR: Daniel Zaken  LAB: RD100	 *
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
    struct sockaddr_in cli_addr = {0};

    // socket create
    if( 0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0) ))
    {
        return UDP_SOCKET_ERR;
    }

    // init srv adr
    InitServer(&srv_addr, PORT);
    // bind socket into 
    if( 0 > (bind(socket_fd, (const struct sockaddr*)&srv_addr,
             sizeof(srv_addr))) )
    {
        return UDP_BIND_ERR;
    }

    socklen_t len  = sizeof(cli_addr);

    int n = 0;
    size_t i = 0;

    for(i = 0 ; i < COUNTER; ++i)
    {

        n = recvfrom(socket_fd, (char*)buffer, BUFFER_SIZE, MSG_WAITALL,
                    (struct sockaddr*)&cli_addr, &len);

        buffer[n] = 0;
        printf("server : %s\n", buffer);

        sleep(1);

        const char *pong = "pong";
        sendto(socket_fd, pong, strlen(pong), MSG_CONFIRM,
            (const struct sockaddr*)&cli_addr, len);

    }

    close(socket_fd);
    return 0;
}
