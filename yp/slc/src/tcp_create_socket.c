#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/select.h>
#include "tcp_create_socket.h"
#include "common.h"

int tcp_create_server_listen(uint16_t port, uint32_t time)
{
	int server_socket = 0;
	int client_socket = 0;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = 0;
	int one = 1;
	int ret;
	struct timeval timeout;
	fd_set fd_setting;

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port);

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		printf("Socket created failed:%d\n", server_socket);
		return -1;
	}

	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0)
	{
		printf("Socket set reuse failed!\n");
		close(server_socket);
		return -1;
	}

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
	{
		printf("Socket bind port failed!\n");
		close(server_socket);
		return -1;
	}

	if (listen(server_socket, 2))
	{
		printf("Server listen failed.\n");
		close(server_socket);
		return -1;
	}

    client_addr_len = sizeof(client_addr);


	FD_ZERO(&fd_setting);
	FD_SET(server_socket, &fd_setting);

	timeout.tv_sec = time;
	timeout.tv_usec = 0;

	ret = select(server_socket + 1, &fd_setting, NULL, NULL, &timeout);
	if (ret > 0)
	{
		if (FD_ISSET(server_socket, &fd_setting))
		{
			client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
			if (client_socket > 0)
			{
				printf("Export data port connected!\n\r");
			}
			else
			{
				printf("Accept failed, error code:%s.\n\r", strerror(errno));
			}
			close(server_socket);
		}
	}
	else if (ret == 0)
	{
		printf("Waitting datas timeout, quit!\n");
		close(server_socket);
		return -1;
	}
	else if (ret < 0)
	{
		printf("Error when waitting connect, quit!\n");
		close(server_socket);
		return -1;
	}

	close(server_socket);

	// while (read_len)
	// {
	// 	ret_send = send(client_socket, sendBuf, read_len, 0);
	// 	if (ret_send < 0)
	// 	{
	// 		printf("Send data failed\n");
	// 		return -1;
	// 	}
	// }

	return client_socket;
}

int tcp_create_client_connect(uint16_t port, const char *ip)
{
	int socket_client = 0;
	struct sockaddr_in client_addr;
	// int ret = 0;

	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(ip);
	client_addr.sin_port = htons(port);

	socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_client <= 0)
	{
		printf("socket_server:%d", socket_client);
		return -1;
	}

	if (connect(socket_client, (const struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
	{
		printf("connect faild!\n");
        close(socket_client);
		return -1;
	}

	// while (reset_len > 0)
	// {
	// 	read_len = recv(socket_client, buffer, read_len, 0);
	// }

    return socket_client;
}

void *tcp_listen_tsak(void *arg)
{
	listen_info *info = (listen_info *)arg;

	int server_socket = 0;
	int client_socket = 0;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = 0;
	int one = 1;
	int ret;
	struct timeval timeout;
	fd_set fd_setting;

	if (!info)
		return NULL;

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(info->port);

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		printf("Socket created failed:%d\n", server_socket);
		free(arg);
		return NULL;
	}

	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0)
	{
		printf("Socket set reuse failed!\n");
		close(server_socket);
		free(arg);
		return NULL;
	}

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
	{
		printf("Socket bind port failed!\n");
		close(server_socket);
		free(arg);
		return NULL;
	}

	if (listen(server_socket, 2))
	{
		printf("Server listen failed.\n");
		close(server_socket);
		free(arg);
		return NULL;
	}

    client_addr_len = sizeof(client_addr);

	while (1)
	{
		FD_ZERO(&fd_setting);
		FD_SET(server_socket, &fd_setting);

		timeout.tv_sec = 10;
		timeout.tv_usec = 0;

		ret = select(server_socket + 1, &fd_setting, NULL, NULL, &timeout);
		if (ret > 0)
		{
			if (FD_ISSET(server_socket, &fd_setting))
			{
				client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
				if (client_socket > 0)
				{
					printf("Client connected!\n\r");
					if (info->call)
						info->call(client_socket, info->arg);
				}
				else
				{
					printf("Accept failed, error code:%s.\n\r", strerror(errno));
				}
				//close(server_socket);
			}
		}
		else if (ret == 0)
		{
			//time out
			// printf("Waitting timeout, quit!\n");
			// close(server_socket);
			// return -1;
		}
		else if (ret < 0)
		{
			printf("Error when waitting connect, quit!\n");
			close(server_socket);
			free(arg);
			return NULL;
		}
	}

	close(server_socket);
	free(arg);

	return NULL;
}

int tcp_get_peer_info(int fd, uint32_t *ip, uint16_t *port)
{			

	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);

    // 获取数据放到sockaddr结构体

	if (getpeername(fd, (struct sockaddr*)&addr, &len))
	{
		printf("get peer info failed\n");
		return -1;
	}

	struct sockaddr_in *in = (struct sockaddr_in *)&addr;
	
	*ip = in->sin_addr.s_addr;
	*port = in->sin_port;

	return 0;
}