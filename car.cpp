#include "car.h"


mHandle mhandle;
// USB图像段
cv::Mat img_rev; 
bool rev_img_flag = false;
cv::Mat img_rev1; 
bool rev_img_flag1 = false;
// 串口数据段
float uart_val[FRAME_LENGTH] = {0.0f};
bool uart_rev_flag = false;

// tcp 回调
int func_call(void *arg, char *buf, int len){
    // double *val = (double *)buf;
    // printf("func_call rev %d %d \n", buf[0], len);
    char *temp;
    temp = buf+MSG_LENG;
    if(buf[MSG_LENG-1] == 12){
        img_rev = cv::Mat(720/4, 1280/4, CV_8UC3, temp);
        rev_img_flag = true;
    }else if(buf[MSG_LENG-1] == 13){
        img_rev1 = cv::Mat(720/4, 1280/4, CV_8UC3, temp);
        rev_img_flag1 = true;
    }

    // 车速 车姿态 升降状态 0.0
    // 拨杆角度　拨杆速度　拨杆扭矩 0.0
    // 激光数据0　激光数据1　激光数据2 0.0
    // 超声波前 超声波后 前碰撞状态 0.0

    // 串口段信息
    for(char i=0; i<FRAME_LENGTH; i++){
        uart_val[i] = char2float((unsigned char*)(buf+i*4));
    }
    uart_rev_flag = true;
    // printf(" uart_val[i] %f \n", uart_val[0]);

    return 0;
}


void car_img_slc_init(){
    // TCP 需要在主线程中打开
    mhandle = tcp_commu_init_client(15513, "192.168.1.22", 2048*2048*3, func_call, NULL, 0);
}

void car_slc_send(float *val){
    //  TCP发送
    unsigned char *array = new unsigned char[MSG_LENG];
    for(unsigned char i =0; i< FRAME_LENGTH; ++i){
        float2char(val[i], (array+i*4));
    }
    tcp_commu_send(mhandle, array, MSG_LENG);
    delete array;
}


CAR::CAR(QObject *parent): QThread(parent){
    isstop = false;
}

void CAR::run(){

    QImage temp;
    bool __isstop = false;
    while (1)
    {   
        mutex_car.lock();
        __isstop = isstop;
        mutex_car.unlock();
        if(__isstop){
            return;
        }

        if(rev_img_flag){
            temp = mat2QImage(img_rev);
            emit car_img(temp);
            rev_img_flag = false;
        }else if(rev_img_flag1){
            temp = mat2QImage(img_rev1);
            emit car_img1(temp);
            rev_img_flag1 = false;
        }

        if(uart_rev_flag){
            emit car_uart(uart_val);
            uart_rev_flag = false;
        }
        usleep(10000);
    }
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

