#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "common.h"
#include "tcp_create_socket.h"
#include "tcp_thread.h"
#include "slc.h"

void* tcp_rx_func(void *_arg)
{
    tcp_commu_t *handle = (tcp_commu_t *)_arg;

    data_header header;

    int index = 0;
    int read_len = 0;
    int rest_len = 0;
    
    while (1)
    {
        rest_len = sizeof(data_header);

        //read header
        while (rest_len)
        {
            read_len = read(handle->fd, (char *)&header + index, rest_len);
            if (0 >= read_len)
            {
                printf("tcp read failed\n");
                return NULL;
            }

            rest_len -= read_len;
            index += read_len;
        }
        
        //read data
        index = 0;
        rest_len = header.size;

        if (rest_len > handle->buf_size)
        {
            printf("msg len error\n");
            continue;
        }
        
        while (rest_len)
        {
            read_len = read(handle->fd, handle->buf + index, rest_len);
            if (0 >= read_len)
            {
                printf("tcp read failed\n");
                return NULL;
            }
            
            rest_len -= read_len;
            index += read_len;
        }

        handle->func(handle->arg, handle->buf, header.size);
    }

    return NULL;
}

int tcp_commu_listen_task_init(uint16_t port, connect_call call, void *arg)
{
    listen_info *info = (listen_info *)malloc(sizeof(listen_info *));

    info->port = port;
    info->call = call;
    info->arg = arg;

    pthread_t id;
    if (-1 == pthread_create(&id, NULL, tcp_listen_tsak, (void *)info))
    {
        printf("tcp listen task create failed.\n");
        return -1;
    }    

    return 0;
}

mHandle tcp_commu_apply(int client_fd, uint32_t buf_size, usr_call func, void *arg, uint32_t flag)
{
    if (client_fd <= 0)
    {
        printf("client fd error\n");
        return NULL;
    }

    tcp_commu_t *handle = (tcp_commu_t *)malloc(sizeof(tcp_commu_t));

    if (!handle)
    {
        printf("malloc failed\n");
        return NULL;
    }
    
    memset(handle, 0, sizeof(tcp_commu_t));

    handle->flag = flag;
    // handle->port = port;
    handle->type = SERVER;
    handle->buf_size = buf_size;
    handle->func = func;
    handle->arg = arg;

    handle->buf = malloc(handle->buf_size);
    if (!handle->buf)
    {
        printf("malloc failed\n");
        free(handle);
        return NULL;
    }

    memset(handle->buf, 0, handle->buf_size);

    handle->fd = client_fd;

    if (-1 == pthread_create(&handle->t_id, NULL, tcp_rx_func, (void *)handle))
    {
        printf("tcp thread create failed.\n");
        close(handle->fd);
        free(handle->buf);
        free(handle);
        return NULL;
    }

    return handle;
}

mHandle tcp_commu_init_server(uint16_t port, uint32_t timeout, uint32_t buf_size,usr_call func,void *arg, uint32_t flag)
{
    tcp_commu_t *handle = (tcp_commu_t *)malloc(sizeof(tcp_commu_t));

    if (!handle)
    {
        printf("malloc failed\n");
        return NULL;
    }
    
    memset(handle, 0, sizeof(tcp_commu_t));

    handle->flag = flag;
    handle->port = port;
    handle->type = SERVER;
    handle->buf_size = buf_size;
    handle->func = func;
    handle->arg = arg;

    handle->buf = malloc(handle->buf_size);
    if (!handle->buf)
    {
        printf("malloc failed\n");
        free(handle);
        return NULL;
    }

    memset(handle->buf, 0, handle->buf_size);

    handle->fd = tcp_create_server_listen(handle->port, timeout);
    if (0 >= handle->fd)
    {
        printf("tcp init faild\n");
        free(handle->buf);
        free(handle);

        return NULL;
    }

    if (-1 == pthread_create(&handle->t_id, NULL, tcp_rx_func, (void *)handle))
    {
        printf("tcp thread create failed.\n");
        close(handle->fd);
        free(handle->buf);
        free(handle);
        return NULL;
    }

    return handle;
}

mHandle tcp_commu_init_client(uint16_t port, const char *ip, uint32_t buf_size, usr_call func,void *arg, uint32_t flag)
{
    tcp_commu_t *handle = (tcp_commu_t *)malloc(sizeof(tcp_commu_t));

    if (!handle)
    {
        printf("malloc failed\n");
        return NULL;
    }
    
    memset(handle, 0, sizeof(tcp_commu_t));

    strcpy(handle->ip, ip);
    handle->flag = flag;
    handle->port = port;
    handle->type = CLIENT;
    handle->buf_size = buf_size;
    handle->func = func;
    handle->arg = arg;

    handle->buf = malloc(handle->buf_size);
    if (!handle->buf)
    {
        printf("malloc failed\n");
        free(handle);
        return NULL;
    }

    memset(handle->buf, 0, handle->buf_size);

    handle->fd = tcp_create_client_connect(handle->port, handle->ip);
    if (0 >= handle->fd)
    {
        printf("tcp init faild\n");
        free(handle->buf);
        free(handle);

        return NULL;
    }

    if (-1 == pthread_create(&handle->t_id, NULL, tcp_rx_func, (void *)handle))
    {
        printf("tcp thread create failed.\n");
        close(handle->fd);
        free(handle->buf);
        free(handle);
        return NULL;
    }

    return handle;
}

int tcp_commu_send(mHandle _handle, void *buf, int len)
{
    if (!_handle)
    {
        printf("hadle null\n");
        return -1;
    }
    
    tcp_commu_t *handle = (tcp_commu_t *)_handle;

    if (len > handle->buf_size)
    {
        printf("msg len error\n");
        return -1;
    }
    
    handle->header_tx.size = len;
    handle->header_tx.index++;

    if(write(handle->fd, &handle->header_tx, sizeof(handle->header_tx)) != sizeof(handle->header_tx))
    {
        printf("tcp write error\n");
        return -1;
    }

    if(write(handle->fd, buf, len) != len)
    {
        printf("tcp write error\n");
        return -1;
    }
    
    return 0; 
}

int tcp_commu_del(mHandle _handle)
{
    if (!_handle)
    {
        printf("hadle null\n");
        return -1;
    }
    tcp_commu_t *handle = (tcp_commu_t *)_handle;

    pthread_kill(handle->t_id, 0);
    usleep(1000);
    close(handle->fd);
    free(handle->buf);
    free(handle);    

    return 0; 
}