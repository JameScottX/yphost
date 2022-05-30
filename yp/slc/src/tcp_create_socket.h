#ifndef _TCP_CREATE_SOCKET_H_
#define _TCP_CREATE_SOCKET_H_

#include <stdint.h>

//int tcp
typedef int (*connect_call)(int client_fd, void *arg);

typedef struct 
{
	uint16_t port;
	connect_call call;
    void *arg;
}listen_info;

int tcp_create_server_listen(uint16_t port, uint32_t time);
int tcp_create_client_connect(uint16_t port, const char *ip);
void *tcp_listen_tsak(void *arg);
int tcp_get_peer_info(int fd, uint32_t *ip, uint16_t *port);

#endif