#include "udp_create_socket.h"

int creat_udp_tx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip)
{
    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*sockfd < 0)
    {
        printf("creat socket failed\n");
        *sockfd = 0;
        return -1;
    }

    bzero(peeraddr, sizeof(struct sockaddr_in));
    peeraddr->sin_family = AF_INET;
    peeraddr->sin_port = htons(port);

    if (strlen(ip))
        peeraddr->sin_addr.s_addr = inet_addr(ip);
    else
        peeraddr->sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_ANY);
    //peeraddr->sin_addr.s_addr = inet_addr(ip);

    return 0;
}
// #include <fcntl.h>
int creat_udp_rx_socket(int *sockfd, struct sockaddr_in *peeraddr, uint16_t port, const char *ip)
{
    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*sockfd < 0)
    {
        printf("creat socket failed\n");
        goto err;
    }

    int opt = 1;
    if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEPORT, (char *)&opt, sizeof(int)) == -1)
    {
        printf("set SO_REUSEPORT failed\n");
        goto err;
    }

    // int flag = 0;
    // if ((flag=fcntl(*sockfd, F_GETFL, NULL))<0)
    // {
    //     printf("fcntl F_GETFL failed\n");
    //     goto err;
    // }

    // if (fcntl(*sockfd, F_SETFL, flag | O_NONBLOCK) == -1)
    // {
    //     printf("fcntl F_GETFL failed\n");
    //     goto err;
    // }

    memset(peeraddr, 0, sizeof(struct sockaddr_in));
    peeraddr->sin_family = AF_INET;

    if (strlen(ip))
        peeraddr->sin_addr.s_addr = inet_addr(ip);
    else
        peeraddr->sin_addr.s_addr = htonl(INADDR_ANY);

    peeraddr->sin_port = htons(port);

    if (bind(*sockfd, (struct sockaddr *)peeraddr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("Binded failure!");
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

mHandle udp_creat_interface(udp_type_t type, uint16_t port, const char *ip)
{
    udp_handle_t *handle = (udp_handle_t *)malloc(sizeof(udp_handle_t));
    if (!handle)
    {
        printf("malloc failed\n");
        return NULL;
    }

    memset(handle, 0, sizeof(udp_handle_t));

    handle->port = port;
    handle->type = type;

    if (ip)
        strcpy(handle->ip, ip);

    switch (type)
    {
    case UDP_TX:
        /* code */
        if (creat_udp_tx_socket(&handle->fd, &handle->addr, handle->port, handle->ip))
        {
            printf("create udp socket error\n");
            break;
        }
        return handle;

    case UDP_RX:
        if (creat_udp_rx_socket(&handle->fd, &handle->addr, handle->port, handle->ip))
        {
            printf("create udp socket error\n");
            break;
        }
        return handle;

    case UDP_TX_RX:
        //not surport yet
    default:
        break;
    }

    free(handle);
    return NULL;
}

int udp_delet_interface(mHandle _handle)
{
    udp_handle_t *handle = (udp_handle_t *)_handle;

    if (handle)
    {
        if (handle->fd > 0)
            close(handle->fd);

        free(handle);
    }

    return 0;
}

int udp_interface_send(mHandle _handle, char *buf, int len)
{
    udp_handle_t *handle = (udp_handle_t *)_handle;

    return sendto(handle->fd, buf, len, 0, (struct sockaddr *)&handle->addr, sizeof(handle->addr));
}
int udp_interface_recv(mHandle _handle, char *buf, int len, int nodelay)
{
    udp_handle_t *handle = (udp_handle_t *)_handle;

    handle->client_addr_len = sizeof(handle->client_addr);

    return recvfrom(handle->fd, buf, len, nodelay ? MSG_DONTWAIT : 0, 
            (struct sockaddr *)&handle->client_addr, &handle->client_addr_len);
}
