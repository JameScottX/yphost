#ifndef HKIMG_H_
#define HKIMG_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "MvCameraControl.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <QThread>
#include <QImage>
#include <QMessageBox>
#include <QMutex>
#include "yuv2rgb.h"


extern QMutex mutex;
extern char hk_img_name[128];

struct HK_Param
{
    float frame_rate = 0.0f;
    unsigned int frame_counter = 0;
    bool issharpen = false;
    bool issave = false;
} ;

class HKHandle : public QThread
{
    Q_OBJECT

public:
    HKHandle(std::string cam_name_, std::string file_save_path_, QObject *parent = 0);
    ~HKHandle();
    bool isstop = false;
    bool isopen = false;
    bool go_close = false;
    float hk_ratio = 1;
    HK_Param hkp;
    unsigned char cam_id = 0;
    std::string cam_name;
    std::string file_save_path;

    void open_camera(unsigned char id);
    void close_camera(unsigned char id);
    bool open_status();

    void* handle = NULL;
    unsigned char *pData = NULL; 
    unsigned char *pData_rgb = NULL;     
    unsigned char *pDataForRGB = NULL;
    int nRet = MV_OK;
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    MV_FRAME_OUT_INFO_EX stImageInfo = {0};
    MV_CC_PIXEL_CONVERT_PARAM stConvertParam = {0};
    MV_FRAME_OUT stOutFrame = {0};

    bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo);
    void hk_find();
    void hk_open(unsigned char nIndex);
    void hk_get_img();
    void hk_close();
    void hk_end();

signals:  
    void img_emit(QImage);

protected:  
    void run();

};

QImage mat2QImage(cv::Mat& mat);
cv::Mat imgSharpen(const cv::Mat & img, char * arith);
char* get_sys_time(std::string &cam);

#endif 


