/*****************************************************************************
 *	FILENAME:	server.c              AUTHOR: Daniel Zaken  LAB: RD100	     *
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
#include <stdio.h> //fflush

#include "server_util.h"
/*****************************************************************************/

static void FdSet(fd_set *fdset,struct timeval *tv ,int tcp_fd, int udp_fd);
static void Destructor(int udp_fd, int tcp_fd);

/*****************************************************************************/

int main()
{
    sa_t tcp_srv = {0};
    sa_t udp_srv = {0};
    sa_t cli = {0};

    int udp_fd = 0; 
    UdpProtocolInit(&udp_srv,sizeof(udp_srv) ,&udp_fd, PORT, 0);

    int tcp_fd = 0; 
    TcpProtocolInit(&tcp_srv, sizeof(tcp_srv), &tcp_fd, PORT, 0);

    int max_fd = MAXFD(udp_fd, tcp_fd);

    fd_set fdset;
    struct timeval tv;

    srv_status_t status = SRV_SUCCESS;

    int to_stay = SRV_TRUE;

    int n_ready = 1;

    while(to_stay)    
    {
        FdSet(&fdset,&tv ,tcp_fd, udp_fd);
        
        n_ready = select(max_fd + 1, &fdset, NULL, NULL, &tv);

        if( 0 == n_ready )
        {
            printf("Time-out\n");
        }
        
        if (FD_ISSET(udp_fd, &fdset))
        {
            status = UdpService(&cli, udp_fd);
            if( SRV_SUCCESS != status )
            {
                Destructor(udp_fd, tcp_fd);
                return status;
            }
        }        

        if (FD_ISSET(tcp_fd, &fdset))
        {
            status = TcpService(&cli, tcp_fd);
            if( SRV_SUCCESS != status )
            {
                Destructor(udp_fd, tcp_fd);
                return status;
            }
            fflush(stdin);
        }

        if (FD_ISSET(STDIN_FILENO, &fdset))
        {
            if( SRV_SUCCESS != (StdinService(&to_stay)) )
            {
                Destructor(udp_fd, tcp_fd);
                return SRV_READ_ERR;
            }
        }

        puts("");
    }

    Destructor(udp_fd, tcp_fd);
    return 0;
}

static void FdSet(fd_set *fdset,struct timeval *tv ,int tcp_fd, int udp_fd)
{
    FD_ZERO(fdset);
    FD_SET(udp_fd,fdset);
    FD_SET(tcp_fd,fdset);
    FD_SET(STDIN_FILENO,fdset);

    tv->tv_sec = 7;
    tv->tv_usec = 0;
}

static void Destructor(int udp_fd, int tcp_fd)
{
    close(udp_fd);
    close(tcp_fd);
}





