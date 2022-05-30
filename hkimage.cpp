#include "hkimage.h"

QMutex mutex;

HKHandle::HKHandle(std::string cam_name_, QObject *parent) : QThread(parent){
    isstop = false;
    this->cam_name = cam_name_;
}

HKHandle::~HKHandle(){

    if (pData_rgb)
    {
        free(pData_rgb);	
        pData_rgb = NULL;
    }
    hk_end();
}

void HKHandle::open_camera(unsigned char id){
    hk_find();
    hk_open(id);
    isstop = false;
    nRet = MV_OK;
    hk_ratio = 1;
    isopen = true;
}

void HKHandle::close_camera(unsigned char id){
    go_close  = true;
}

bool HKHandle::open_status(){
    return this->isopen;
}

void HKHandle::run(){

    bool __isstop = false;
    while(1){

        mutex.lock();
        __isstop = isstop;
        mutex.unlock();
        if(__isstop){
            if(isopen){
                hk_close();
                isopen = false;
            }
            return;
        }

        // 相机关闭
        if(go_close && isopen){
            hk_close();
            isopen = false;
            go_close = false;
        }
        // 相机没有打开线程在此等待
        while (!isopen){
            if(__isstop){
                return;
            }
        }

        cv::Mat img_rev;
        hk_get_img();
        if(stOutFrame.stFrameInfo.enPixelType == 0){
            printf("No image data!\n");
            continue;
        }
        if(pData_rgb == NULL)
            pData_rgb = (unsigned char*)malloc(stOutFrame.stFrameInfo.nWidth * stOutFrame.stFrameInfo.nHeight * 3);
        // printf("enPixelType %d \n", stOutFrame.stFrameInfo.enPixelType);

        if( stOutFrame.stFrameInfo.enPixelType == PixelType_Gvsp_YUV422_Packed){
            yuv422packed_to_rgb24(FMT_UYVY, stOutFrame.pBufAddr, pData_rgb, stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight);
        }else{
            yuv422packed_to_rgb24(FMT_YUYV, stOutFrame.pBufAddr, pData_rgb, stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight);
        }
        img_rev = cv::Mat(stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nWidth , CV_8UC3, pData_rgb);
        
        mutex.lock();
        if(hkp.issharpen == true){
            char arith[9] = {
            0, -1, 0, -1, 5, -1, 0, -1, 0};       //使用拉普拉斯算子
            img_rev = imgSharpen(img_rev, arith);
        }
        cv::resize(img_rev, img_rev, cv::Size(),hk_ratio,hk_ratio, cv::INTER_LINEAR);//我长宽都变为原来的0.5倍
        mutex.unlock();
        
        QImage temp = mat2QImage(img_rev);
        emit img_emit(temp);
        usleep(100);
    }
}


cv::Mat imgSharpen(const cv::Mat & img, char * arith)       //arith为3*3模板算子
{
    
    int rows = img.rows;        //原图的行
    int cols = img.cols * img.channels();   //原图的列
    int offsetx = img.channels();       //像素点的偏移量

    cv::Mat dst = cv::Mat::ones(img.rows-2, img.cols-2, img.type());

    for(int i = 1; i < rows - 1; i++)
    {
    
        const uchar* previous = img.ptr<uchar>(i - 1);
        const uchar* current = img.ptr<uchar>(i);
        const uchar* next = img.ptr<uchar>(i + 1);
        uchar * output = dst.ptr<uchar>(i-1);
        for(int j = offsetx ; j < cols - offsetx; j++)
        {
    
            output[j - offsetx] =
            cv::saturate_cast<uchar>( previous[j-offsetx]*arith[0] + previous[j]*arith[1] + previous[j+offsetx]*arith[2] +
                                  current[j-offsetx]*arith[3]  + current[j]*arith[4]  + current[j+offsetx]*arith[5]  +
                                  next[j-offsetx]*arith[6]     + next[j]*arith[7]     + next[j-offsetx]*arith[8] );
        }
    }
    return dst;
}

QImage mat2QImage(cv::Mat& mat){
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
#if 0
        qDebug() << "CV_8UC1";
#endif
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
#if 0
        qDebug() << "CV_8UC4";
#endif
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
#if 0
        qDebug() << "ERROR: Mat could not be converted to QImage.";
#endif
        QMessageBox::information(
            NULL,
            "Error",
            "Image Format Unknown!",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
        return QImage();
    }
}


bool HKHandle::PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo){
    if (NULL == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

        // ch:打印当前相机ip和用户自定义名字 | en:print current ip and user defined name
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chModelName);
        printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chModelName);
        printf("UserDefinedName: %s\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
    }
    else
    {
        printf("Not support.\n");
    }

    return true;
}

void HKHandle::hk_find(){
    do{
        memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
        // 枚举设备
        // enum device
        nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
        if (MV_OK != nRet)
        {
            printf("MV_CC_EnumDevices fail! nRet [%x]\n", nRet);
            break;
        }
        if (stDeviceList.nDeviceNum > 0)
        {
            for (int i = 0; i < stDeviceList.nDeviceNum; i++)
            {
                printf("[device %d]:\n", i);
                MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
                if (NULL == pDeviceInfo)
                {
                    break;
                }

                PrintDeviceInfo(pDeviceInfo);       
                std::string temp = (char*)pDeviceInfo->SpecialInfo.stGigEInfo.chModelName;
                if(temp == this->cam_name){
                    this->cam_id = i;
                    printf("Use Devices id: %d  %s\n",this->cam_id ,pDeviceInfo->SpecialInfo.stGigEInfo.chModelName);
                }     
            }  
        }else{
            printf("Find No Devices!\n");
            break;
        }
    }while (0);
}

void HKHandle::hk_open(unsigned char nIndex){

    do{
        if (nIndex >= stDeviceList.nDeviceNum){
            printf("Intput error!\n");
            break;
        }

        // 选择设备并创建句柄
        // select device and create handle
        nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[nIndex]);
        if (MV_OK != nRet)
        {
            printf("MV_CC_CreateHandle fail! nRet [%x]\n", nRet);
            break;
        }

        // 打开设备
        // open device
        nRet = MV_CC_OpenDevice(handle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_OpenDevice fail! nRet [%x]\n", nRet);
            break;
        }
        
        // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
        if (stDeviceList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
        {
            int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
            if (nPacketSize > 0)
            {
                nRet = MV_CC_SetIntValue(handle,"GevSCPSPacketSize",nPacketSize);
                if(nRet != MV_OK)
                {
                    printf("Warning: Set Packet Size fail nRet [0x%x]!\n", nRet);
                }
            }
            else
            {
                printf("Warning: Get Packet Size fail nRet [0x%x]!\n", nPacketSize);
            }
        }
        
        nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
        if (MV_OK != nRet){
            printf("MV_CC_SetTriggerMode fail! nRet [%x]\n", nRet);
            break;
        }

        // ch:获取数据包大小 | en:Get payload size
        MVCC_INTVALUE stParam;
        memset(&stParam, 0, sizeof(MVCC_INTVALUE));
        nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
        if (MV_OK != nRet)
        {
            printf("Get PayloadSize fail! nRet [0x%x]\n", nRet);
            break;
        }

        // 开始取流
        // start grab image
        nRet = MV_CC_StartGrabbing(handle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_StartGrabbing fail! nRet [%x]\n", nRet);
            break;
        }
        
    }while (0);

    memset(&stOutFrame, 0, sizeof(MV_FRAME_OUT));
}

void HKHandle::hk_get_img(){

    do{

    nRet = MV_CC_GetImageBuffer(handle, &stOutFrame, 1000);
    if (nRet == MV_OK)
    {
        // printf("Get One Frame: Width[%d], Height[%d], nFrameNum[%d]\n",
        //     stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nFrameNum);
    }
    else
    {
        printf("No data[0x%x]\n", nRet);
    }
    // printf(" stOutFrame.stFrameInfo %d \n", stOutFrame.stFrameInfo.enPixelType);

    if(NULL != stOutFrame.pBufAddr)
    {
        nRet = MV_CC_FreeImageBuffer(handle, &stOutFrame);
        if(nRet != MV_OK)
        {
            printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
        }
    }

    }while (0);
}

void HKHandle::hk_close(){

    do{
        // 停止取流
        // end grab image
        nRet = MV_CC_StopGrabbing(handle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_StopGrabbing fail! nRet [%x]\n", nRet);
            break;
        }

        // ch:关闭设备 | Close device
        nRet = MV_CC_CloseDevice(handle);
        if (MV_OK != nRet)
        {
            printf("ClosDevice fail! nRet [0x%x]\n", nRet);
            break;
        }
    }while (0);
    
}

void HKHandle::hk_end(){


    hk_close();

    if (nRet != MV_OK)
    {
        if (handle != NULL)
        {
            MV_CC_DestroyHandle(handle);
            handle = NULL;
        }
    }
    
    if (pData)
    {
        free(pData);	
        pData = NULL;
    }
    if (pDataForRGB)
    {
        free(pDataForRGB);
        pDataForRGB = NULL;
    }
}


