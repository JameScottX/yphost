#include <pthread.h>
#include "udp_thread.h"
#include "udp_create_socket.h"
#include "common.h"

void* udp_rx_func(void *_arg)
{
    int len = 0;
    char *buf = NULL;
    udp_commu_t *handle = (udp_commu_t *)_arg;

    buf = malloc(UDP_BUF_SIZE);
    if (!buf)
    {
        printf("malloc error\n");
        return NULL;
    }
    memset(buf, 0, UDP_BUF_SIZE);
    
    //FIXME 阻塞接受这里不会退出
    while (handle->run)
    {
        len = udp_interface_recv(handle->udp_rx, buf, UDP_BUF_SIZE, handle->flag & COMMU_FLAG_NODELAY);
        if(len <= 0) //FIXME 无法识别接收超时和接收失败
        {
            continue;
        }
        // else if(len < 0)
        // {
        //     printf("udp recv error\n");
        //     break;
        // }

        handle->func(handle->arg, buf, len);
        memset(buf, 0, UDP_BUF_SIZE);
    }

    free(buf);

    handle->run = 2;

    return NULL;
}

int udp_commu_del(mHandle _handle)
{
    udp_commu_t *handle = (udp_commu_t *)_handle;

    handle->run = 0;

    udp_delet_interface(handle->udp_tx);
    udp_delet_interface(handle->udp_rx);

    free(handle);

    return 0;
}

mHandle udp_commu_init(char *ip_lc, uint16_t port_lc, char *ip_rt, uint16_t port_rt, usr_call func, void *arg, int flag)
{
    udp_commu_t *handle = (udp_commu_t *)malloc(sizeof(udp_commu_t));
    if(!handle)
    {
        printf("malloc error\n");
        return NULL;
    }

    memset(handle, 0, sizeof(udp_commu_t));
    handle->func = func;
    handle->arg = arg;
    handle->flag = flag;
    handle->run = 1;

    handle->udp_tx = udp_creat_interface(UDP_TX, port_rt, ip_rt);
    if(!handle->udp_tx)
    {
        printf("udp interface tx creat failed\n");
        return NULL;
    }

    handle->udp_rx = udp_creat_interface(UDP_RX, port_lc, ip_lc);
    if(!handle->udp_rx)
    {
        printf("udp interface rx creat failed\n");
        udp_delet_interface(handle->udp_tx);
        return NULL;
    }

    if (-1 == pthread_create(&handle->t_id_rx, NULL, udp_rx_func, (void *)handle))
    {
        printf("udp rx thread create failed.\n\r");
        udp_delet_interface(handle->udp_tx);
        udp_delet_interface(handle->udp_rx);
        return NULL;
    }

    return handle;
}