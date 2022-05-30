#ifndef _UDP_CREATE_SOCKET_H_
#define _UDP_CREATE_SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"

int creat_udp_tx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip);
int creat_udp_rx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip);

typedef enum {
     UDP_TX,
     UDP_RX,
     UDP_TX_RX
}udp_type_t;  

typedef struct 
{
    int fd;
    udp_type_t type;
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    uint32_t client_addr_len;
    uint16_t port;
    char ip[64];
}udp_handle_t;

mHandle udp_creat_interface(udp_type_t type, uint16_t port, const char *ip);
int udp_delet_interface(mHandle _handle);
int udp_interface_send(mHandle _handle, char *buf, int len);
int udp_interface_recv(mHandle _handle, char *buf, int len, int nodelay);

#endif