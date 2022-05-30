#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdint.h>
#include "slc.h"

uint64_t cpu_time64_get(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec;
}

uint64_t cpu_time64_diffus(uint64_t timeBase)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec) - timeBase;
}

int func_call_test2(void *arg, char *buf, int len)
{
    uint64_t ed  = cpu_time64_diffus(*(uint64_t *)(buf));

//    printf("recv msg[%d]:%s, delay: %.3f ms\n", len, (char *)buf, ed/1000.f);
    printf("recv msg[%d]:, delay: %.3f ms\n", len, ed/1000.f);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("usage: %s ip_lc port_lc ip_rt port_rt flag\n", argv[0]);
        return -1;
    }
    
    uint16_t port_lc = strtoul(argv[2], NULL, 0);
    uint16_t port_rt = strtoul(argv[4], NULL, 0);
    int flag = strtoul(argv[5], NULL, 0);

    mHandle handle = commu_init(argv[1], port_lc, argv[3], port_rt, func_call_test2, NULL, flag);
    if (!handle)
        return -1;
    
    // int i = 0;
    char buf[1024] = {0};
    while (1)
    {
        //sprintf(buf, "hello commu %d !", i++);

        *(uint64_t *)(buf) = cpu_time64_get();
        commu_send(handle, buf, 8);

        sleep(1);
    }

    return 0;
}

int func_call_test(void *arg, char *buf, int len)
{
    uint64_t ed  = cpu_time64_diffus(*(uint64_t *)(buf+32));

    printf("recv msg[%d]:%s, delay: %.3f ms\n", len, (char *)buf, ed/1000.f);
    return 0;
}

int main333(int argc, char *argv[])
{
    mHandle handle;
    if (argc > 1)
    {
        printf("server init\n");
        handle = tcp_commu_init_server(9645, 20, 1024*1024, func_call_test, NULL, 0);
    }
    else
    {
        printf("clinet init\n");
        handle = tcp_commu_init_client(9645, "127.0.0.1", 1024*1024, func_call_test, NULL, 0);
    }
    
    if (!handle)
        return -1;
    
    int i = 0;
    char buf[1024*1024] = {0};
    while (1)
    {
        sprintf(buf, "hello commu %d !", i++);

        *(uint64_t *)(buf+32) = cpu_time64_get();
        if (argc > 1) tcp_commu_send(handle, buf, 64);

        sleep(1);
    }

    return 0;
}

int main999(int argc, char *argv[])
{
    mHandle handle;
    if (argc > 1)
    {
        printf("tx init\n");
        handle = udp_mult_tx_init("224.0.0.1", 4481, 0);
    }
    else
    {
        printf("rx init\n");
        handle = udp_mult_rx_init("224.0.0.1", 4481, func_call_test, NULL, 0);
    }
    
    if (!handle)
        return -1;
    
    int i = 0;
    char buf[1024*64] = {0};
    while (1)
    {
        sprintf(buf, "hello mult commu %d !", i++);

        *(uint64_t *)(buf+32) = cpu_time64_get();
        if (argc > 1) 
        {
            printf("mult tx:%d\n", udp_mult_send(handle, buf, 64));
        }
        sleep(1);
    }

    return 0;
}

#include <arpa/inet.h>

//仅供演示，使用全局变量可能存在多个客户端覆盖的问题
mHandle tcp_handle = NULL;

int connect_call_test(int client_fd, void *arg)
{
    uint32_t ip;
    uint16_t port;

    tcp_get_peer_info(client_fd, &ip, &port);

    struct in_addr in;
    in.s_addr = ip;

    printf("client:%s, port:%d connect!\n", inet_ntoa(in), port);

    tcp_handle = tcp_commu_apply(client_fd, 1024, func_call_test, NULL, 0);

    return 0;
}

int main_tcp_listen_test()
{
    char buf[] = "test";

    //当前程序开启监听，对端程序使用tcp_commu_init_client连接
    tcp_commu_listen_task_init(8848, connect_call_test, NULL);

    while (1)
    {
        sleep(1);
        if (tcp_handle)
        {
           tcp_commu_send(tcp_handle, buf, strlen(buf));
        }
    }
        
    return 0;    
}
