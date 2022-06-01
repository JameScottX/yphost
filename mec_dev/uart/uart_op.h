#ifndef _UART_OP_H_
#define _UART_OP_H_

#include "string.h"

#define HEAD0           0xff
#define HEAD1           0xe1
#define HEAD12           0xe2
#define HEAD13           0xe3
#define HEAD14           0xe4
#define TAIL            0xfe
#define FRAME_LENGTH    16
#define UART_FRAME_LENGTH    4

int uart_open_normal(char *devname, int bud, int (*usr_func)(float *, int, int));
int uart_close_normal(int &fd);
int uart_flush(int fd);
int uart_send(int fd, char *buf, int len);
int uart_recv(int fd, char *buf, int len);

void float2char(float val, unsigned char *bytes);
float char2float(unsigned char *bytes);

void uart_pack(int &fd, float *val, unsigned short size, int flag);
void uart_pack_encoder(int &fd, float *val, unsigned short size);
int uart_pack_decoder(int &fd, float *val);

#endif



