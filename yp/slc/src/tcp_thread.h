#ifndef _TCP_THREAD_H_
#define _TCP_THREAD_H_

#include <stdint.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "slc.h"

typedef struct 
{
    uint32_t index;     //自动累加
    uint32_t size;      //单次数据长度
    uint64_t timestamp; //时间戳 us
    uint64_t user_arg;  //用户可以额外传一个参数
}data_header __attribute__((__aligned__(1)));

// typedef struct 
// {
//     int fd;         //数据收发描述符
//     int type;       //客户端 or 服务端
//     uint32_t buf_size;   //此为最大数据帧长度
//     char *buf;      //数据帧缓冲
//     const char *ip;
//     uint16_t port;
// }local_param;

typedef enum
{
    SERVER = 0,
    CLIENT
}TCP_TYPE;

typedef struct
{
    int fd;
    char *buf;
    uint32_t buf_size;
    pthread_t t_id;
    char ip[32];
    uint16_t port;
    TCP_TYPE type;
    uint32_t flag;
    usr_call func;
    void *arg;
    data_header header_tx;
    struct sockaddr_in client_addr;
}tcp_commu_t;

mHandle tcp_commu_init_server(uint16_t port, uint32_t timeout, uint32_t buf_size,usr_call func,void *arg, uint32_t flag);
mHandle tcp_commu_init_client(uint16_t port, const char *ip, uint32_t buf_size, usr_call func,void *arg, uint32_t flag);
int tcp_commu_send(mHandle _handle, void *buf, int len);
int tcp_commu_del(mHandle _handle);
int tcp_commu_get_client_info(mHandle _handle, uint32_t *ip, uint16_t *port);


#endif