#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(m_timer()));
    timer->start(1000);
    ui->hk_img_l->setScaledContents(false);
    ui->hk_sa->viewport()->installEventFilter(this);
    ui->hk_img_l->installEventFilter(this);

    hk = new HKHandle("MV-CS016-10GC");
    hk_up = new HKHandle("MV-CA060-10GC");

    connect(hk, SIGNAL(img_emit(QImage)), this, SLOT(hk_cam_f_show(QImage)));
    hk->start();
    connect(hk_up, SIGNAL(img_emit(QImage)), this, SLOT(hk_cam_u_show(QImage)));
    hk_up->start();

    connect(ui->sharpen_rb,SIGNAL(clicked(bool)),
    this,SLOT(state_change()));

    ui->car_f_img_l->setScaledContents(true);
    ui->car_h_img_l->setScaledContents(true);

    car = new CAR();
    connect(car, SIGNAL(car_img(QImage)), this, SLOT(car_img_show(QImage)));
    connect(car, SIGNAL(car_img1(QImage)), this, SLOT(car_img1_show(QImage)));
    connect(car, SIGNAL(car_uart(float*)), this, SLOT(cat_status_feedback(float*)));
    car->start();

    car_img_slc_init();

    connect(ui->up_down_pb, SIGNAL(released()), this, SLOT(car_command()));

    connect(ui->hk_cam_f_rb, SIGNAL(toggled(bool)), this, SLOT(hk_cam_f_rb_open()));
    connect(ui->hk_cam_u_rb, SIGNAL(toggled(bool)), this, SLOT(hk_cam_u_rb_open()));
    // 一开始打开前相机
    hk_cam_f_rb_open();
}

MainWindow::~MainWindow()
{   
    hk->quit();
    hk->wait(500);

    hk_up->quit();
    hk_up->wait(500);

    car->quit();
    car->wait();

    delete ui;
    delete timer;
    delete hk, hk_up;
    delete car;
}


void MainWindow::m_timer(){
    // 帧率显示
    mutex.lock();
    if(hk->open_status()){
        ui->framerate_l->setText(QString::number(hk->hkp.frame_counter));
        hk->hkp.frame_counter = 0;
    }
    if(hk_up->open_status()){
        ui->framerate_l->setText(QString::number(hk_up->hkp.frame_counter));
        hk_up->hkp.frame_counter = 0;
    }
    mutex.unlock();
    // printf(" hk->hkp.frame_counter %d \n", hk->hkp.frame_counter );
}

void MainWindow::hk_cam_f_rb_open(){
    if(ui->hk_cam_f_rb->isChecked()){
        hk->hk_find();
        hk->open_camera(hk->cam_id);
    }else{
        if(hk->open_status()){
            hk->close_camera(hk->cam_id);
        }
    }
}

void MainWindow::hk_cam_f_show(QImage img){
    mp = mp.fromImage(img);
    ui->hk_img_l->setPixmap(mp);
    ui->hk_img_l->show();
    hk->hkp.frame_counter ++;
}

void MainWindow::hk_cam_u_rb_open(){
    if(ui->hk_cam_u_rb->isChecked()){
        hk_up->hk_find();
        hk_up->open_camera(hk_up->cam_id);
    }else{
        if(hk_up->open_status()){
            hk_up->close_camera(hk_up->cam_id);
        }
    }
}

void MainWindow::hk_cam_u_show(QImage img){
    mp = mp.fromImage(img);
    ui->hk_img_l->setPixmap(mp);
    ui->hk_img_l->show();
    hk_up->hkp.frame_counter ++;
}

void MainWindow::car_img_show(QImage img){
    mp = mp.fromImage(img);
    ui->car_f_img_l->setPixmap(mp);
    ui->car_f_img_l->show();
}

void MainWindow::car_img1_show(QImage img){
    mp = mp.fromImage(img);
    ui->car_h_img_l->setPixmap(mp);
    ui->car_h_img_l->show();
}

void MainWindow::cat_status_feedback(float *uart_val){
    ui->car_speed_l->setText(QString::number(uart_val[0]));
}

void MainWindow::car_command(){
    // car->move_spd = 0;
    float val[FRAME_LENGTH] = {
        3.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
    };
    car_slc_send(val);
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
        }else if(hk->hk_ratio > 3){
            hk->hk_ratio = 3;
        }
        mutex.unlock();

        mutex.lock();
        hk_up->hk_ratio += delta*0.0006;
        if (hk_up->hk_ratio < 0.5){
            hk_up->hk_ratio = 0.5;
        }else if(hk_up->hk_ratio > 3){
            hk_up->hk_ratio = 3;
        }
        mutex.unlock();

        ui->hk_sa->verticalScrollBar()->setValue( currentMt.y());
        ui->hk_sa->horizontalScrollBar()->setValue( currentMt.x());
        // printf("currentMt %d %d \n", currentMt.x(), currentMt.y());
        return true;
    }

    return false;			
}

void MainWindow::closeEvent(QCloseEvent *event){

    timer->stop();

    mutex.lock();
    hk->isstop = true;
    mutex.unlock();

    mutex.lock();
    hk_up->isstop = true;
    mutex.unlock();

    car->mutex_car.lock();
    car->isstop = true;
    car->mutex_car.unlock();
}

void MainWindow::state_change(){

    mutex.lock();
    if(ui->sharpen_rb->isChecked())
        hk->hkp.issharpen = true;
    else
        hk->hkp.issharpen = false;
    mutex.unlock();

}

