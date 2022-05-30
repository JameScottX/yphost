// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>
// #include <netinet/ip.h>
// #include <netdb.h>
// #include <unistd.h>
// #include <string.h>
// #include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "udp_multicast.h"

// #include "./include/stor_debug.h"

// #define LOG_TAG    "_MULTICAST_"
// #include "./include/stor_elog.h"

// DBG_SET_PRINT_LEVEL(DBG_PRINT_LEVEL_ERROR | DBG_PRINT_LEVEL_PRINT | DBG_PRINT_LEVEL_NOTICE | DBG_PRINT_LEVEL_DEBUG);

// int multicast_tx_thread()
// {
//     struct sockaddr_in peeraddr;
//     int sockfd;
//     void *send_buf;

//     sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//     if (sockfd < 0)
//     {
//         printf("creat socket failed\n");
//     }
//     printf("socket created success\n");

//     memset(&peeraddr, 0, sizeof(struct sockaddr_in));
//     peeraddr.sin_family = AF_INET;
//     peeraddr.sin_port = htons(MULTICAST_CMD_TX_PORT);
//     peeraddr.sin_addr.s_addr = inet_addr(MULTICAST_CMD_TX_ADDR);

//     while (1)
//     {
//         sendto(sockfd, send_buf, 99, 0,
//                    (struct sockaddr *)&peeraddr, sizeof(struct sockaddr_in));
//     }

//     return 0;    
// }

// int multicast_rx_thread()
// {
//     struct sockaddr_in peeraddr;
//     int sockfd;
//     void *recv_buf;
//     struct ip_mreq mreq;
//     unsigned int socklen, n;

//     sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//     if (sockfd < 0)
//     {
//         printf("creat socket failed\n");
//     }

//     bzero(&mreq, sizeof(mreq));
//     mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_CMD_RX_ADDR);
//     mreq.imr_interface.s_addr = htonl(INADDR_ANY);

//     if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq)) == -1)
//     {
//         printf("setsockopt failed\n");
//     }

//     memset(&peeraddr, 0, sizeof(peeraddr));
//     peeraddr.sin_family = AF_INET;
//     peeraddr.sin_addr.s_addr = htonl(INADDR_ANY);
//     peeraddr.sin_port = htons(MULTICAST_CMD_RX_PORT);

//     if (bind(sockfd, (struct sockaddr *)&peeraddr, sizeof(struct sockaddr_in)) == -1)
//     {
//         printf("Binded failure\n");
//     }

//     socklen = sizeof(struct sockaddr);

//     while(1)
//     {
//         n = recvfrom(sockfd, recv_buf, 99, 0, (struct sockaddr *)&peeraddr, &socklen);
//     }

//     return 0; 
// }

int creat_multicast_tx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip)
{
    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*sockfd < 0)
    {
        printf("creat socket failed:%s\n", strerror(errno));
        //log_e("creat socket failed:%s\n", strerror(errno));
        *sockfd = 0;
        return -1;
    }

    bzero(peeraddr, sizeof(struct sockaddr_in));
    peeraddr->sin_family = AF_INET;
    peeraddr->sin_port = htons(port);
    peeraddr->sin_addr.s_addr = inet_addr(ip);

    // int opt = 1;
	// if(setsockopt(*sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) < 0)
	// {
	// 	printf("[PC]Set socket option failed , SO_BROADCAST");
	// 	return -1;
	// }

    return 0;
}

int creat_multicast_rx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip)
{
    static struct ip_mreq mreq;

    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*sockfd < 0)
    {
        printf("creat socket failed:%s\n", strerror(errno));
        //log_e("creat socket failed:%s\n", strerror(errno));
        goto err;
    }


	int opt = 1;
	if(setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(int)) == -1)
	{
		printf("socket SO_REUSEPORT set failed:%s\n", strerror(errno));
        //log_e("socket SO_REUSEPORT set failed:%s\n", strerror(errno));
		goto err;
	}

	// if(setsockopt(*sockfd, SOL_SOCKET, SO_REUSEPORT, (char*)&opt, sizeof(int)) == -1)
	// {
	// 	printf("socket SO_REUSEPORT set failed:%s\n", strerror(errno));
    //     //log_e("socket SO_REUSEPORT set failed:%s\n", strerror(errno));
	// 	goto err;
	// }


    memset(peeraddr, 0, sizeof(struct sockaddr_in));
    peeraddr->sin_family = AF_INET;
    peeraddr->sin_addr.s_addr = htonl(INADDR_ANY);
    peeraddr->sin_port = htons(port);

    if (bind(*sockfd, (struct sockaddr *)peeraddr, sizeof(struct sockaddr_in)) == -1)
    {
        // printf("Binded failure\n");
        //perror("Binded failure!");
        printf("Binded failure:%s", strerror(errno));
        //log_e("Binded failure:%s", strerror(errno));
        goto err;
    }

	// int opt = 1;
	// if(setsockopt(*sockfd, SOL_SOCKET, SO_REUSEPORT, (char*)&opt, sizeof(int)) == -1)
	// {
	// 	printf("socket SO_REUSEPORT set failed:%s\n", strerror(errno));
    //     //log_e("socket SO_REUSEPORT set failed:%s\n", strerror(errno));
	// 	goto err;
	// }


    bzero(&mreq, sizeof(mreq));
    mreq.imr_multiaddr.s_addr = inet_addr(ip);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(*sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq)) != 0)
    {
        printf("setsockopt failed:%s\n", strerror(errno));
        //log_e("setsockopt failed:%s\n", strerror(errno));
        goto err;
    }

    return 0;

err:
    if (*sockfd > 0)
        close(*sockfd);
    if (*sockfd)
        *sockfd = 0;
    
    return -1;
}

int multicast_recv(int sockfd, void *recv_buf, int len, struct sockaddr *peeraddr)
{
    socklen_t socklen = sizeof(struct sockaddr);

    return recvfrom(sockfd, recv_buf, len, 0, (struct sockaddr *)peeraddr, &socklen);
}

int multicast_send(int sockfd, void *send_buf, int len ,struct sockaddr *peeraddr)
{
    return sendto(sockfd, send_buf, len, 0,
                   (struct sockaddr *)peeraddr, sizeof(struct sockaddr_in));
}