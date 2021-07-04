/*****************************************************************************
 *	FILENAME:	SERV_UTIL.h                AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:   SERVER UTIL           							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_SERV_UTIL_HPP__
#define __ILRD_RD100_SERV_UTIL_HPP__

#include <unistd.h>
/*****************************************************************************/
#define BUFFER_SIZE 128
#define PORT 8080
#define SRV_FAIL -1
#define SRV_TRUE 1
#define SRV_FALSE 0

#define MAXFD(a, b) ((a > b) ? (a) : (b))
/*****************************************************************************/
typedef struct addrinfo ai_t;
typedef struct sockaddr_in sa_t;
/*****************************************************************************/
typedef enum server_status
{
    SRV_SUCCESS = 0,
    SRV_BIND_ERR = -1,
    SRV_CONNECT_ERR = -2,
    SRV_LISTEN_ERR = -3,
    SRV_SOCKET_ERR = -4,
    SRV_ACCEPT_ERR = -5,
    SRV_FCNTL_ERR = -6,
    SRV_OPT_ERR = -7,
    SRV_READ_ERR = -8,
    SRV_WRITE_ERR = -9
}srv_status_t;


/*****************************************************************************/
srv_status_t UdpProtocolInit(sa_t *udp_srv,
                             size_t sa_size,
                             int *fd,
                             int port,
                             int block);

srv_status_t TcpProtocolInit(sa_t *tcp_srv,
                             size_t sa_size,
                             int *fd,
                             int port,
                             int block);

int SetSockBlock(int fd, int blocking);

void InitServer(sa_t* srv, int port);

void TcpClient(int fd);

srv_status_t UdpService(sa_t *udp_cli, int udp_fd);

srv_status_t StdinService(int *to_stay);

srv_status_t TcpService(sa_t *tcp_cli, int tcp_fd);



/*****************************************************************************/
#endif // __ILRD_RD100_SERV_UTIL__

