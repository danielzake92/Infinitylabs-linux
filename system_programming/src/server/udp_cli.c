/*****************************************************************************
 *	FILENAME:	udp_cli1.c         AUTHOR: Daniel Zaken  LAB: RD100	         *
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
#include <string.h> //strlen
#include <stdio.h> //printf

#include "server_util.h"
/*****************************************************************************/

#define COUNTER 5

/*****************************************************************************/

int main()
{
    
    int socket_fd = 0; 
    char buffer[BUFFER_SIZE];

    struct sockaddr_in srv_addr = {0};

    if( 0 > (socket_fd = socket(AF_INET, SOCK_DGRAM, 0) ))
    {
        return SRV_SOCKET_ERR;
    }

    InitServer(&srv_addr, PORT);

    socklen_t len  = sizeof(srv_addr);
    int n = 0;
    const char *ping = "ping";

    size_t i = 0;

    for(i = 0; i < COUNTER; ++i)
    {
        sendto(socket_fd, ping, strlen(ping), MSG_CONFIRM,
            (const struct sockaddr*)&srv_addr, len);


        n = recvfrom(socket_fd, buffer, BUFFER_SIZE, MSG_WAITALL,
                    (struct sockaddr*)&srv_addr, &len);


        buffer[n] = 0;

        printf("UDP client : %s\n", buffer);
        sleep(1);
    }


    close(socket_fd);

    return 0;
}
#if 0
     printf("n = %d\n",n);    

        if( -1 == n )
        {
            break;
        }
#endif