#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket api
#include <unistd.h> //sleep
#include <netinet/in.h> // for sin family 
#include <netinet/ip.h> // ip communication 
#include <sys/types.h> // portability with BSD 
#include "tcp_udp.h"

#define BUFFER_SIZE 128

void Pong(int fd)
{
    char buff[BUFFER_SIZE];

    read(fd, buff, sizeof(buff) );
    printf("%s\n", buff);
    sleep(1);

    const char *pong = "pong";
    write(fd, pong, sizeof(pong));
}

void Ping(int fd)
{
    char buff[BUFFER_SIZE];

    const char *ping = "ping";
    write(fd, ping, sizeof(ping));
    fflush(stdout);

    read(fd, buff, sizeof(buff) );
    printf("%s\n", buff);
    sleep(1);

}

void InitServer(struct sockaddr_in * srv, int port)
{
    srv->sin_family = AF_INET;
    srv->sin_addr.s_addr = INADDR_ANY;
    srv->sin_port = htons(port);
}
