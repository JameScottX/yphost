#include "cam.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
 

int func_call(void *arg, char *buf, int len){
    double *val = (double *)buf;
    printf("func_call rev %f %d \n", val[0], len);
    return 0;
}


int main()
{   

    mHandle mhandle = tcp_commu_init_server(11113, 10*60, 1024*1024*3, func_call,NULL, 0);
	//读取视频或摄像头
	VideoCapture capture(0);
    
	while (true)
	{
		Mat frame;
		capture >> frame;

        unsigned char *array = new unsigned char[frame.rows*frame.cols*frame.channels()];
        for (int i = 0; i < frame.rows; i++){
            unsigned char *data = frame.ptr<unsigned char>(i);
            for (int j = 0; j < frame.cols * 3; j++)
            {
                array[i * frame.cols * 3 + j] = data[j];
            }
        }

        tcp_commu_send(mhandle, array, frame.rows*frame.cols*frame.channels());
	    // cv::Mat Image(frame.rows, frame.cols, CV_8UC3, array);
        // printf("frame %d %d %d \n", frame.rows, frame.cols, frame.channels());
		// imshow("Camera Frame", Image);
		waitKey(10);

        delete array;
	}

    capture.release();
	return 0;
}

