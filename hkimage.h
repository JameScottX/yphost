#ifndef HKIMG_H_
#define HKIMG_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "MvCameraControl.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <QThread>
#include <QImage>
#include <QMessageBox>

#include <QMutex>

extern MV_CC_PIXEL_CONVERT_PARAM stConvertParam;
extern QMutex mutex;

class HKHandle : public QThread
{
    Q_OBJECT

public:
    HKHandle(QObject *parent = 0);
    ~HKHandle();
    bool isstop = false;
    float hk_ratio = 1;

signals:  
    void img_emit(QImage);

protected:  
    void run();

};

QImage mat2QImage(cv::Mat& mat);

bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo);
void hk_find();
void hk_open(unsigned char nIndex);
void hk_get_img();
void hk_end();


#endif 


