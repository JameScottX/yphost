#include <opencv2/opencv.hpp>
#include <iostream>
#include "stdio.h"

using namespace cv;
using namespace std;
 
int main(int argc, char **argv)
{   
    if (argc<2) exit(0);
    int id = atoi(argv[1]);
	int img_cout = 0;
	char img_name[64];
	//读取视频或摄像头
	VideoCapture capture(id);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,1280);//可以
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);
    // capture.set(CV_CAP_PROP_FRAME_WIDTH,1920);//可以
    // capture.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
	
	while (true)
	{
		Mat frame;
		capture >> frame;
		imshow("读取视频", frame);
		int c =waitKey(20);	
		if (c == 115){

			sprintf(img_name, "img%d.jpg", img_cout);
			cv::imwrite(img_name, frame);
        	printf("frame size %d %d\n", frame.cols, frame.rows);

			printf("%s saved.\n", img_name);
			++img_cout;
		}
	}
	return 0;

}




