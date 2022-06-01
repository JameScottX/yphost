#include "uart_op.h"
#include <iostream>

char name[50] = "/dev/ttyUSB0";

int rev_msg(float *val){
    printf(" %f \n", val[0]);
    return 0;
}

int main(){

    int fd = uart_open_normal(name , 115200, rev_msg);

    // char bytes[4];
    // float2char(-2.0, bytes);
    // float val_get = char2float(bytes);
    // printf(" %f \n", val_get);

    // float val[8] = {1,2,3,4,5,6,7,8};
    // float val2[8] = {1,1,1,1,1,1,1,1};
    // int fD_ = 1;
    // uart_pack_encoder(fD_, val ,8);
    // int sta = uart_pack_decoder(fD_, buffer, val2);
    // if(sta == 1){
    //     printf(" %f \n", val2[3]);
    // }

    if(fd == -1){
        printf("uart open failed!\n");
        return 0;
    }else{
        printf("uart open successed!\n");
    }

    while (1){

    }
    return 0;
}








