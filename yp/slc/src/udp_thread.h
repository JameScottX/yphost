#ifndef _UDP_THREAD_H_
#define _UDP_THREAD_H_

#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"
#include "slc.h"

#define UDP_BUF_SIZE    (1024*64)

typedef struct 
{
    int run;
    int flag;
    pthread_t t_id_tx;
    pthread_t t_id_rx;
    sem_t lock;
    mHandle mq_tx;
    mHandle udp_tx;
    mHandle udp_rx;

    usr_call func;
    void *arg;

}udp_commu_t;

mHandle udp_commu_init(char *ip_lc, uint16_t port_lc, char *ip_rt, uint16_t port_rt, usr_call func, void *arg, int flag);
int udp_commu_del(mHandle _handle);

#endif