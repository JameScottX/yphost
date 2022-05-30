#include <opencv2/opencv.hpp>
#include "slc.h"

using namespace cv;
using namespace std;

cv::Mat img_rev; 
bool rev_flag = false;
cv::Mat img_rev1; 
bool rev_flag1 = false;

int func_call(void *arg, char *buf, int len){
    // double *val = (double *)buf;
    //do something
    printf("func_call rev %d %d \n", buf[0], len);
    char *temp;
    temp = buf+48;
    if(buf[0] == 12){
        img_rev = cv::Mat(720/4, 1280/4, CV_8UC3, temp);
        rev_flag = true;
    }else if(buf[0] == 13){
        img_rev1 = cv::Mat(720/4, 1280/4, CV_8UC3, temp);
        rev_flag1 = true;
    }

    return 0;
}

// int func_call1(void *arg, char *buf, int len){
//     // double *val = (double *)buf;
//     //do something
//     // printf("func_call rev %f %d \n", val[0], len);
//     img_rev1 = cv::Mat(720/2, 1280/2, CV_8UC3, buf);
//     rev_flag1 = true;
//     return 0;
// }


int main(){

    mHandle mhandle = tcp_commu_init_client(15513, "192.168.1.20", 2048*2048*3, func_call, NULL, 0);
    // mHandle mhandle1 = tcp_commu_init_client(15514, "192.168.1.20", 2048*2048*3, func_call1, NULL, 0);
    
    while (1){
        if (rev_flag){
            imshow("读取视频", img_rev);
            rev_flag = false;
        }

        if (rev_flag1){
            imshow("读取视频1", img_rev1);
            rev_flag1 = false;
        }
        waitKey(1);
    }
    return 0;
}

