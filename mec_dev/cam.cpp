#include "cam.h"
#include <opencv2/opencv.hpp>
#include <arpa/inet.h>
#include "signal.h"
#include "unistd.h"

#include "uart_op.h"

using namespace cv;
using namespace std;
 
#define MSG_LENG 96

const float ratio_ = 0.25;
mHandle mhandle = NULL;
bool tcp_connect_flag = false;

char name[50] = "/dev/ttyUSB0";
float uart_val[FRAME_LENGTH] = {0.0f};
static int fd;

int func_call(void *arg, char *buf, int len){
    // uart 发送
    float *val = (float *)buf;
    // printf("uart send %f %d \n", val[0], len);
    uart_pack(fd, val, UART_FRAME_LENGTH, HEAD1);
    uart_pack(fd, (val+4), UART_FRAME_LENGTH, HEAD12);
    uart_pack(fd, (val+8), UART_FRAME_LENGTH, HEAD13);
    uart_pack(fd, (val+12), UART_FRAME_LENGTH, HEAD14);
    return 0;
}

int connect_call_func(int client_fd, void *arg){
    uint32_t ip;
    uint16_t port;
    tcp_get_peer_info(client_fd, &ip, &port);
    struct in_addr in;
    in.s_addr = ip;
    printf("client %s port %d connect \n", inet_ntoa(in), port);
    mhandle = tcp_commu_apply(client_fd, 1024*1024*4, 
                                func_call, NULL, 0);
    if(mhandle == NULL){
        printf("tcp_commu_apply failed.\n");
    }
    tcp_connect_flag = true;
    return 0;
}

// 串口读取回调函数, 单帧长度为 FRAME_LENGTH
int uart_rev_msg(float *val, int size, int flag){

    if(flag == HEAD1){
        memcpy(uart_val, val, sizeof(float)*UART_FRAME_LENGTH);
        printf("HEAD1 uart receive from car %f %f %f %f\n", uart_val[0], uart_val[1],
                        uart_val[2], uart_val[3]);
    }else if(flag == HEAD12){
        memcpy(uart_val + 4, val, sizeof(float)*UART_FRAME_LENGTH);
        // printf("HEAD12 uart receive from car %f %f %f %f\n", uart_val[4], uart_val[5],
        //                 uart_val[6], uart_val[7]);
    }else if(flag == HEAD13){
        memcpy(uart_val + 8, val, sizeof(float)*UART_FRAME_LENGTH);
    }else if(flag == HEAD14){
        memcpy(uart_val + 12, val, sizeof(float)*UART_FRAME_LENGTH);
    }

    // printf("uart receive from car %f %f %f %f\n", val[0], val[1],
    //                     val[2], val[3]);
    return 0;
}

void sig_handler(int sig){
    printf("****sig_handler-SIGPIPE****\n");
    tcp_connect_flag = false;
}

void uart_handler(int sig){
    uart_close_normal(fd);
    printf("****uart exit****\n");
    printf("****process exit****\n");
    exit(0);
}

void uart_init(){
    fd = uart_open_normal(name , 115200, uart_rev_msg);
}

int main()
{   
    unsigned char bytes[4];
    uart_init();

    signal(SIGPIPE, sig_handler);
    signal(SIGINT, uart_handler); 
    // mHandle mhandle = tcp_commu_init_server(15513, 10*60, 1024*1024*3, func_call,NULL, 0);
    tcp_commu_listen_task_init(15513, connect_call_func, NULL);
    
    //读取视频或摄像头
	VideoCapture capture(0);
    VideoCapture capture1(2);
    sleep(1);

    unsigned char *array = NULL;

	while (true)
	{
        if(!mhandle){
            usleep(1000);
            continue;
        }
        if(!tcp_connect_flag){
            usleep(20000);
            continue;
        }

		Mat frame;
		capture >> frame;
	    cv::resize(frame, frame, cv::Size(), ratio_, ratio_, cv::INTER_LINEAR);
        // 消息长度为 96 个字节， 最后一个表示图像ID
        if (array == NULL)
            array = new unsigned char[frame.rows*frame.cols*frame.channels() + MSG_LENG];
        array[MSG_LENG-1] = 12;
        for (int i = 0; i < frame.rows; i++){
            unsigned char *data = frame.ptr<unsigned char>(i);
            for (int j = 0; j < frame.cols * 3; j++)
            {
                array[i * frame.cols * 3 + j + MSG_LENG] = data[j];
            }
        }
        // 串口帧复制到tcp发送段
        for(char i=0; i<FRAME_LENGTH; i++){
            float2char(uart_val[i], bytes);
            memcpy(array + i*4, bytes, 4*sizeof(unsigned char));
        }

        tcp_commu_send(mhandle, array, frame.rows*frame.cols*frame.channels() + MSG_LENG);
        waitKey(5);

        Mat frame1;
        capture1 >> frame1;
	    cv::resize(frame1, frame1, cv::Size(), ratio_, ratio_, cv::INTER_LINEAR);
        array[MSG_LENG-1] = 13;
        for (int i = 0; i < frame1.rows; i++){
            unsigned char *data = frame1.ptr<unsigned char>(i);
            for (int j = 0; j < frame1.cols * 3; j++)
            {
                array[i * frame1.cols * 3 + j + MSG_LENG] = data[j];
            }
        }
        
        // 串口帧复制到tcp发送段
        for(char i=0; i<FRAME_LENGTH; i++){
            float2char(uart_val[i], bytes);
            memcpy(array + i*4, bytes, 4*sizeof(unsigned char));
        }

        tcp_commu_send(mhandle, array, frame1.rows*frame1.cols*frame1.channels() + MSG_LENG);
        // cv::Mat Image(frame.rows, frame.cols, CV_8UC3, array);
        // printf("frame %d %d %d \n", frame.rows, frame.cols, frame.channels());
		// imshow("Camera Frame", Image);
		waitKey(5);
	}

    delete array;
    capture.release();
    capture1.release();
	return 0;
}



