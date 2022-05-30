#ifndef _UDP_MULTICAST_H_
#define _UDP_MULTICAST_H_

#include <stdint.h>
#include <netinet/in.h>

int creat_multicast_rx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip);
int creat_multicast_tx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip);

int multicast_recv(int sockfd, void *recv_buf, int len, struct sockaddr *peeraddr);
int multicast_send(int sockfd, void *send_buf, int len ,struct sockaddr *peeraddr);

#endif