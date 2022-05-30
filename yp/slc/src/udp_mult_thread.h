#ifndef _UDP_MULT_THREAD_H_
#define _UDP_MULT_THREAD_H_

#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <netinet/in.h>
#include "common.h"
#include "slc.h"

#define UDP_MULT_BUF_SIZE    (1024*64)

typedef enum
{
    UDP_MULT_TX = 0,
    UDP_MULT_RX
}UDP_MULT_TYPE;

typedef struct 
{
    int run;
    int flag;
    pthread_t t_id;
    sem_t lock;
    UDP_MULT_TYPE type; 
    int sockfd;
    struct sockaddr_in peeraddr;

    usr_call func;
    void *arg;

}udp_mult_commu_t;


mHandle udp_mult_tx_init(const char *ip, uint16_t port, int flag);
mHandle udp_mult_rx_init(const char *ip, uint16_t port, usr_call func, void *arg, int flag);
int udp_mult_send(mHandle _handle, void *buf, int len);
int udp_mult_del(mHandle _handle);

#endif