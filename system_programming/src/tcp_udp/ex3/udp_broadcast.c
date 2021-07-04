/*****************************************************************************
 *	FILENAME:	udp_broadcast.c         AUTHOR: Daniel Zaken  LAB: RD100	 *
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

    struct sockaddr_in srv_addr = {0};

    // socket create
    if( 0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0) ))
    {
        return UDP_SOCKET_ERR;
    }
    int broadcast = 1;

	setsockopt(socket_fd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(int));
    // init srv adr
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_BROADCAST;
    srv_addr.sin_port = htons(PORT);

   
    const char *msg = "broadcasted msg\n";
    sendto(socket_fd, msg, strlen(msg), 0,
          (const struct sockaddr*)&srv_addr, sizeof(srv_addr));
    puts("sended");
        sleep(1);
   

    close(socket_fd);
    return 0;
}

