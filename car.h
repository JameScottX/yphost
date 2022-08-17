#pragma once
#ifndef CAR_H_
#define CAR_H_

#include "slc.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QThread>
#include <QImage>
#include <QMessageBox>
#include <QMutex>

#include "hkimage.h"

#define MSG_LENG                    96          // tcp 车载信息字节数
#define FRAME_LENGTH                16          // tcp 一帧float数量

extern QMutex mutex_car;

class CAR : public QThread
{
    Q_OBJECT
public:
    bool isstop = false;
    CAR(QObject *parent = 0);
    ~CAR(){};
    QMutex mutex_car;
    
signals:  
    void car_img(QImage);
    void car_img1(QImage);
    void car_uart(float *uart_val);

protected:  
    void run();

public:
    float move_spd = 0.0;       // 前进速度
    float dir_spd = 0.0;        // 角速度
    float dir = 0.0;            // 角度
    float emgc= 0.0;            // 软件急停
    float lift = 0.0;           // 抬起主相机
    float light_on = 0.0;       // 前灯
    float light_on2 = 0.0;      // 上灯
    float light_on3 = 0.0;      // 视野灯
    float bogan_p = 0.0;        // 拨杆位置
    float bogan_v = 0.0;        // 拨杆速度
    float supp = 0.0;           // 前支撑

    float move_spd_rge[2] = {-4000.0, 4000.0}; 
    float dir_spd_rge[2] = {-2000.0, 2000.0};
    float dir_rge[2] = {-3.1415, 3.1415};
    float bogan_v_rge[2] ={-720.0, 720.0};
    float light_on_rge[2]= {0, 50.0};

};

void car_img_slc_init();
void car_slc_send(float *val);
void float2char(float val, unsigned char *bytes);
float char2float(unsigned char *bytes);
float data_map(int val, int bias, int val_max, float *rge);
int data_mapback(float val, float *rge, int bias, int val_max);

#endif 


