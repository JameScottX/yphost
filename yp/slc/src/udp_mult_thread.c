#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "udp_multicast.h"
#include "udp_mult_thread.h"

void* udp_mult_rx_func(void *_arg)
{
    int len = 0;
    char *buf = NULL;
    udp_mult_commu_t *handle = (udp_mult_commu_t *)_arg;
    struct sockaddr_in sender;
    //socklen_t sender_len=sizeof(sender);

    buf = malloc(UDP_MULT_BUF_SIZE);
    if (!buf)
    {
        printf("malloc error\n");
        return NULL;
    }
    memset(buf, 0, UDP_MULT_BUF_SIZE);

    // printf("recv start\n");
    
    //FIXME 阻塞接受这里不会退出
    while (handle->run)
    {
        len = multicast_recv(handle->sockfd, buf, UDP_MULT_BUF_SIZE, (struct sockaddr *)&sender);
        if(len <= 0)
        {
            printf("udp recv error:%d\n", len);
            sleep(1);
            continue;
        }
        // else if(len < 0)
        // {
        //     printf("udp recv error\n");
        //     break;
        // }

        // printf("udp recv\n");

        handle->func(handle->arg, buf, len);
        memset(buf, 0, UDP_MULT_BUF_SIZE);
    }

    free(buf);

    // handle->run = 2;

    return NULL;
}

mHandle udp_mult_tx_init(const char *ip, uint16_t port, int flag)
{
    udp_mult_commu_t *handle = (udp_mult_commu_t *)malloc(sizeof(udp_mult_commu_t));
    if(!handle)
    {
        printf("malloc error\n");
        return NULL;
    }

    memset(handle, 0, sizeof(udp_mult_commu_t));
    handle->flag = flag;

    if(creat_multicast_tx_socket(&handle->sockfd, &handle->peeraddr, port, ip))
    {
        printf("udp multicast tx creat failed\n");
        free(handle);
        return NULL;
    }

    // printf("tx fd:%d\n", handle->sockfd);

    return handle;    
}

mHandle udp_mult_rx_init(const char *ip, uint16_t port, usr_call func, void *arg, int flag)
{
    udp_mult_commu_t *handle = (udp_mult_commu_t *)malloc(sizeof(udp_mult_commu_t));
    if(!handle)
    {
        printf("malloc error\n");
        return NULL;
    }

    memset(handle, 0, sizeof(udp_mult_commu_t));
    handle->func = func;
    handle->arg = arg;
    handle->flag = flag;
    handle->run = 1;

    if(creat_multicast_rx_socket(&handle->sockfd, &handle->peeraddr, port, ip))
    {
        printf("udp multicast rx creat failed\n");
        free(handle);
        return NULL;
    }

    if (-1 == pthread_create(&handle->t_id, NULL, udp_mult_rx_func, (void *)handle))
    {
        printf("udp multicast rx thread create failed.\n\r");
        close(handle->sockfd);
        free(handle);
        return NULL;
    }

    // printf("rx fd:%d\n", handle->sockfd);

    return handle; 
}

int udp_mult_send(mHandle _handle, void *buf, int len)
{
    udp_mult_commu_t *handle = (udp_mult_commu_t *)_handle;

    return multicast_send(handle->sockfd, buf, len, (struct sockaddr *)&handle->peeraddr);
}


int udp_mult_del(mHandle _handle)
{
    // udp_mult_commu_t *handle = (udp_mult_commu_t *)_handle;

    //懒得写，后面有空再搞

    return 0;
}