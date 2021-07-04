/*****************************************************************************
 *	FILENAME:	tcp_udp.hp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:   TCP UDP util         							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_TCP_UDP_HPP__
#define __ILRD_RD100_TCP_UDP_HPP__

/*****************************************************************************/
#include <netinet/ip.h> // struct sockaddr_in 
void Ping(int fd);
void Pong(int fd);

void InitServer(struct sockaddr_in * srv, int port);

/*****************************************************************************/
#endif // __ILRD_RD100_IPC_HPP__

