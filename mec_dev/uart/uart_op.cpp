#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <thread>
#include "uart_op.h"

unsigned char buffer[1024];
unsigned char buffer_rev[1024];
bool run = true;

// 串口线程
int uart_rev_handle(int fd, int (*usr_func)(float *, int, int)){

    float uart_val[UART_FRAME_LENGTH];
    printf("uart receiving.\n");
    while(run){
        int flag = uart_pack_decoder(fd, uart_val);
        if (flag == -1) continue;
        usr_func(uart_val, UART_FRAME_LENGTH, flag);
        usleep(100);
    }
    printf("uart thread exit.\n");
    return 0;
}

// 串口初始化 开启线程
int uart_open_normal(char *devname, int bud, int (*usr_func)(float *, int, int)){
    
    int fd = open(devname, O_RDWR | O_NOCTTY);
    if (fd < 0){
        printf("uart open failed.\n");
        return -1;
    }
    
    int speed = 0;
    struct termios oldtio = {0};
    struct termios newtio = {0};
    tcgetattr(fd, &oldtio);

    switch (bud)
    {
    case 2400:
        speed = B2400;
        break;
    case 4800:
        speed = B4800;
        break;
    case 9600:
        speed = B9600;
        break;
    case 115200:
        speed = B115200;
        break;
    case 460800:
        speed = B460800;
        break;
    default:
        speed = B9600;
        break;
    }

    newtio.c_cflag = speed | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = 0; // IGNPAR | ICRNL
    newtio.c_oflag = 0;
    newtio.c_lflag = 0; // ICANON
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 1;

    tcflush(fd, TCIOFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);

    std::thread uart_rev(uart_rev_handle, fd, usr_func);
    uart_rev.detach();

    // 注释掉 读等待
    // fcntl(fd, F_SETFL, O_NONBLOCK);
    fcntl(fd, F_SETFL, 0);
    return fd;
}

// 串口关闭
int uart_close_normal(int &fd){
    fcntl(fd, F_SETFL, O_NONBLOCK);
    tcflush(fd, TCIOFLUSH);
    sleep(1);
    run = false;
    return 0;
}

int uart_flush(int fd)
{
    return tcflush(fd, TCIOFLUSH);
}

int uart_send(int fd, char *buf, int len){
    return write(fd, buf, len);
}

int uart_recv(int fd, char *buf, int len){
    return read(fd, buf, len);
}

// 串口数据打包
void uart_pack(int &fd, float *val, unsigned short size, int flag){
    *buffer = HEAD0;
    *(buffer+1) = flag;
    for(unsigned short i =0; i <size; i++){
        float2char(val[i], (buffer + 2 + i *sizeof(float)) );
    }
    // memcpy(buffer + 2, bytes, size * sizeof(float));
    *(buffer+2+size * sizeof(float)) = TAIL;
    write(fd, buffer, 3+size * sizeof(float));
}


void uart_pack_encoder(int &fd, float *val, unsigned short size){
    unsigned char bytes[4];
    *buffer = HEAD0;
    *(buffer+1) = HEAD1;
    unsigned int j = 2;
    for(unsigned short i = 0; i< size; i++){
        float2char(val[i], bytes);
        memcpy(buffer + j, bytes, 4 * sizeof(char));
        j += 4;
    }
    *(buffer+j) = TAIL;
    j += 1;
    write(fd, buffer, j);
}

// 串口数据解码
int uart_pack_decoder(int &fd, float *val){

    int flag = -1;
    read(fd, buffer_rev, 2);
    if(buffer_rev[0] == HEAD0 && buffer_rev[1] == HEAD1){flag = HEAD1;
    }else if(buffer_rev[0] == HEAD0 && buffer_rev[1] == HEAD12){flag = HEAD12;
    }else if(buffer_rev[0] == HEAD0 && buffer_rev[1] == HEAD13){flag = HEAD13;
    }else if(buffer_rev[0] == HEAD0 && buffer_rev[1] == HEAD14){flag = HEAD14;
    }else{
        // printf("buffer_rev %x %x \n", buffer_rev[0], buffer_rev[1]);
        return -1;
    }

    for(unsigned char i =0; i < UART_FRAME_LENGTH; i++){
        read(fd, buffer_rev, 4);
        val[i] = char2float(buffer_rev);
        if(i == 0){
            // printf("buffer_rev %x %x %x %x\n", 
            //     buffer_rev[0], buffer_rev[1], buffer_rev[2], buffer_rev[3]);
            // float temp = char2float(buffer_rev);
            // printf("%f \n", temp);
            // unsigned char temp2[4];
            // memcpy(temp2, &temp,4);
            // printf("temp2 %x %x %x %x\n", 
            //     temp2[0], temp2[1], temp2[2], temp2[3]);
        }
    }
    
    read(fd, buffer_rev, 1);
    if(*(buffer_rev) == TAIL){
    }else return -1;
    
    usleep(2000);
    return flag;
}


void float2char(float val, unsigned char *bytes){
    unsigned char *p = (unsigned char *)&val;
    *bytes = *(p);
    *(bytes+1) = *(p + 1);
    *(bytes+2) = *(p + 2);
    *(bytes+3) = *(p + 3);
}

float char2float(unsigned char *bytes){
    float val = 0.0;
    unsigned char *p = (unsigned char *)&val;
    *(p) = *bytes;
    *(p + 1) = *(bytes+1);
    *(p + 2) = *(bytes+2);
    *(p + 3) = *(bytes+3);
    return val;
}




