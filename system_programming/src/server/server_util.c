#include <sys/socket.h> //socket api
#include <netinet/in.h> // for sin family 
#include <sys/types.h> // portability with BSD 
#include <sys/time.h> //time_val struct
#include <sys/select.h> //select api
#include <stdio.h> //fflush
#include <string.h> //strlen

#include <fcntl.h> //tcp to non blocking
#include "server_util.h"

void InitServer(struct sockaddr_in *srv, int port)
{
    srv->sin_family = AF_INET;
    srv->sin_addr.s_addr = INADDR_ANY;
    srv->sin_port = htons(port);
}
/*****************************************************************************/
srv_status_t UdpProtocolInit(sa_t *udp_srv,
                             size_t sa_size,
                             int *fd,
                             int port,
                             int block)
{
    if( SRV_FAIL == (*fd = socket(AF_INET, SOCK_DGRAM, 0) ))
    {
        return SRV_SOCKET_ERR;
    }

    InitServer(udp_srv, port);
    SetSockBlock(*fd, block);
    
    if( SRV_FAIL == (bind(*fd, (const struct sockaddr*)udp_srv,
             sa_size)) )
    {
        return SRV_BIND_ERR;
    }


    return SRV_SUCCESS;
}
/*****************************************************************************/
srv_status_t TcpProtocolInit(sa_t *tcp_srv,
                             size_t sa_size,
                             int *fd,
                             int port,
                             int block)
{
    int yes = 1;
    if( 0 > (*fd = socket(AF_INET, SOCK_STREAM, 0) ))
    {
        return SRV_SOCKET_ERR;
    }
    if (SRV_FAIL == setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)))
    {
        printf("setsockopt error\n");
        return SRV_OPT_ERR;
    }
    // init srvs
    InitServer(tcp_srv, port);


    SetSockBlock(*fd, block);

    if( SRV_FAIL == (bind(*fd, (const struct sockaddr*)tcp_srv,
             sa_size)) )
    {
        return SRV_BIND_ERR;
    }
    
    if( SRV_FAIL == (listen(*fd,10) ))
    {
        return SRV_LISTEN_ERR;
    }

    
    return SRV_SUCCESS;
}
/*****************************************************************************/
int SetSockBlock(int fd, int blocking)
{
    if (fd < 0) 
    {
        return SRV_FCNTL_ERR;
    }

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) 
    {
        return SRV_FCNTL_ERR;
    }

    flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);

    return ((fcntl(fd, F_SETFL, flags) == 0) ? SRV_SUCCESS : SRV_FCNTL_ERR);
}
/*****************************************************************************/
void TcpClient(int fd)
{
    char buff[BUFFER_SIZE];

    write(fd, "tcp client : ping", 18);

    read(fd, buff, BUFFER_SIZE );
    printf("%s\n", buff);
    sleep(1);
}
/*****************************************************************************/
srv_status_t TcpService(sa_t *tcp_cli, int tcp_fd)
{
    socklen_t len  = sizeof(tcp_cli);
    char buff[BUFFER_SIZE];
    int accepted_fd = 0;

    accepted_fd = accept(tcp_fd,(struct sockaddr*)&tcp_cli, &len);
    if(SRV_FAIL == accepted_fd)
    {
        return SRV_ACCEPT_ERR;
    }

    int read_ans = read(accepted_fd, buff, BUFFER_SIZE );

    if( SRV_FAIL == read_ans)
    {
        return SRV_READ_ERR;
    }

    printf("%s\n", buff);
    sleep(1);

    if (SRV_FAIL == write(accepted_fd, "TCP server : pong", 18) )
    {
        return SRV_WRITE_ERR;
    }

    /* empting socket */
    while(read_ans)
    {
        read_ans = read(accepted_fd, buff, BUFFER_SIZE );
    }
    printf("\ntcp connection close\n");

    close(accepted_fd);

    return SRV_SUCCESS;
}


/*****************************************************************************/
srv_status_t StdinService(int *to_stay)
{
    char buff[BUFFER_SIZE];

    if( SRV_FAIL == read(STDIN_FILENO, buff,BUFFER_SIZE ) )
    {
        *to_stay = SRV_FALSE;
        return SRV_READ_ERR;
    }

    if(!strncmp("quit\n", buff, 6))
    {
        *to_stay = SRV_FALSE;
    }
    if(!strncmp("ping\n", buff, 6))
    {
        printf("\npong\n");
    }
    return SRV_SUCCESS;
}
/*****************************************************************************/
srv_status_t UdpService(sa_t *udp_cli, int udp_fd)
{
    char buffer[BUFFER_SIZE];
    socklen_t len  = sizeof(udp_cli);
    int n = 0;

    n = recvfrom(udp_fd, (char*)buffer, BUFFER_SIZE, MSG_WAITALL,
                (struct sockaddr*)&udp_cli, &len);
    if( SRV_FAIL == n )
    {
        return SRV_READ_ERR;
    }

    buffer[n] = 0;
    printf("UDP server : %s\n", buffer);

    sleep(1);

    const char *pong = "pong";
    if(SRV_FAIL == sendto(udp_fd, pong, strlen(pong), MSG_CONFIRM,
        (const struct sockaddr*)&udp_cli, len))
    {
        return SRV_WRITE_ERR;
    }    

    return SRV_SUCCESS;   
}
/*****************************************************************************/

