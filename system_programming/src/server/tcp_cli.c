/*****************************************************************************
 *	FILENAME:	tcp_cli.pong                 AUTHOR: Daniel Zaken  LAB: RD100	 *
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
#include <stdlib.h> //srand && rand
#include <time.h> //srand && rand
#include <stdio.h> //printf

#include "server_util.h"
/*****************************************************************************/

/*****************************************************************************/
static size_t RandCounter(size_t max_num, size_t min_num);

int main()
{
    int socket_fd = 0; 
    struct sockaddr_in srv_addr = {0};


    size_t counter = RandCounter(10, 3);

    for(; counter; --counter)
    {
        // socket create
        if( 0 > (socket_fd = socket(AF_INET, SOCK_STREAM, 0) ))
        {
            return SRV_SOCKET_ERR;
        }

        InitServer(&srv_addr, PORT);

        int yes = 1;
        setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int));

        socklen_t len  = sizeof(srv_addr);
        if( 0 > (connect(socket_fd,(const struct sockaddr*)&srv_addr, len)))
        {
            close(socket_fd);
            printf("TCP client : connect err\n");
            return SRV_SOCKET_ERR;
        }

        TcpClient(socket_fd);
        close(socket_fd);
    }
    
    return 0;
}
static size_t RandCounter(size_t max_num, size_t min_num)
{
     srand((unsigned)time(NULL));

     return(rand()%((max_num + 1) - min_num) + min_num);
}