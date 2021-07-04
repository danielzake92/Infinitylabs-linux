/*****************************************************************************
 *	FILENAME:	udp_broadcast.c         AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:	Liad    													 *
 *																			 *
 *	PURPOSE:    Server with protocols               					     *
 *																			 *
 *****************************************************************************/
#include <sys/socket.h> //socket api
#include <netinet/in.h> // for sin family 
#include <sys/types.h> // portability with BSD 
#include <sys/time.h> //time_val struct
#include <sys/select.h> //select api
#include <stdio.h> //printf

#include "server_util.h"
/*****************************************************************************/

int main()
{
    int socket_fd = 0; 
    struct sockaddr_in srv_addr = {0};

    // socket create
    if( 0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0) ))
    {
        return SRV_SOCKET_ERR;
    }
    int broadcast = 1;

	setsockopt(socket_fd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(int));
    // init srv adr
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_BROADCAST;
    srv_addr.sin_port = htons(PORT);
   
    sendto(socket_fd, "ping", 5, 0,
          (const struct sockaddr*)&srv_addr, sizeof(srv_addr));
   
    close(socket_fd);
    return 0;
}

