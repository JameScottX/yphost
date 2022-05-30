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

#define MSG_LENG                    96
#define FRAME_LENGTH                16

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
    float move_spd = 0.0;
    float light_on = 0.0;
    float lift = 0.0;
    float bogan_p = 0.0;
    float bogan_v = 0.0;

};

void car_img_slc_init();
void car_slc_send(float *val);
void float2char(float val, unsigned char *bytes);
float char2float(unsigned char *bytes);

#endif 


