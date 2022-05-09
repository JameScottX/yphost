#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hkimage.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    OpenCamera();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(img_update()));
    timer->start(50);
    ui->hk_img_l->setScaledContents(false);
    ui->hk_sa->viewport()->installEventFilter(this);
    ui->hk_img_l->installEventFilter(this);

    hk = new HKHandle();
    connect(hk, SIGNAL(img_emit(QImage)), this, SLOT(img_show(QImage)));
    hk->start();
}

MainWindow::~MainWindow()
{   
    hk->quit();
    hk->wait();

    delete ui;
    delete timer;
    delete hk;
}

void MainWindow::OpenCamera(){
    car_f.open(0);
}

cv::Mat MainWindow::getFrame_f(){

    cv::Mat imageout;

    if(!car_f_stop){
        car_f>>frame_f;
        imageout = frame_f;
        // GaussianBlur(frame_f, imageout, cv::Size(3, 3), 0, 0);
        return imageout;
    }
    return imageout;
}

void MainWindow::img_update(){

    // cv::Mat temp_img_f = getFrame_f();
    // cv::resize(temp_img_f, temp_img_f, Size(),hk_ratio,hk_ratio);//我长宽都变为原来的0.5倍

    // cv::Mat img_rev;
    // hk_get_img();
    // img_rev = cv::Mat(3072, 2048, CV_8UC3, stConvertParam.pDstBuffer );

    // cv::resize(img_rev, img_rev, Size(),hk_ratio,hk_ratio);//我长宽都变为原来的0.5倍

    // QImage temp = mat2QImage(img_rev);
    // mp = mp.fromImage(temp);
    // ui->hk_img_l->setPixmap(mp);
    // ui->hk_img_l->show();

}

void MainWindow::img_show(QImage img){
    
    mp = mp.fromImage(img);
    ui->hk_img_l->setPixmap(mp);
    ui->hk_img_l->show();
}

bool MainWindow::eventFilter(QObject *target, QEvent *event){

    if(target == ui->hk_sa->viewport() && event->type() == QEvent::Wheel){
        
        // event->ignore();
        return true;      //只针对scrollArea窗口禁用滚轮滚动功能，返回true表示过滤
        
    }else if(qobject_cast<QLabel*>(target) == ui->hk_img_l && event->type() == QEvent::MouseButtonPress){

        currentPt = ((QMouseEvent*)event)->pos();
        // printf("currentPt %d %d \n", currentPt.x(), currentPt.y());

        return true;
    }else if(qobject_cast<QLabel*>(target) == ui->hk_img_l && event->type() == QEvent::MouseMove){

        currentMt = ((QMouseEvent*)event)->pos();

        int dist_x = currentPt.x() - currentMt.x();
        int dist_y = currentPt.y() - currentMt.y();
        // printf("currentMt %d %d \n", currentMt.x(), currentMt.y());
        ui->hk_sa->verticalScrollBar()->setValue(ui->hk_sa->verticalScrollBar()->value() + dist_y);
        ui->hk_sa->horizontalScrollBar()->setValue(ui->hk_sa->horizontalScrollBar()->value() + dist_x);
        return true;

    }else if(qobject_cast<QLabel*>(target) == ui->hk_img_l && event->type() == QEvent::Wheel){

        int delta = ((QWheelEvent*)event)->delta();

        mutex.lock();
        hk->hk_ratio += delta*0.0006;
        if (hk->hk_ratio < 0.5){
            hk->hk_ratio = 0.5;
        }
        mutex.unlock();

        ui->hk_sa->verticalScrollBar()->setValue( currentMt.y());
        ui->hk_sa->horizontalScrollBar()->setValue( currentMt.x());
        // printf("currentMt %d %d \n", currentMt.x(), currentMt.y());
        return true;
    }

    return false;			
}


