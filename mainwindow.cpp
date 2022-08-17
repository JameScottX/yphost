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

    hk = new HKHandle("MV-CS016-10GC", "/home/jame/ubuntu-data/yphost_image");
    hk_up = new HKHandle("MV-CA060-10GC", "/home/jame/ubuntu-data/yphost_image");

    connect(hk, SIGNAL(img_emit(QImage)), this, SLOT(hk_cam_f_show(QImage)));
    hk->start();
    connect(hk_up, SIGNAL(img_emit(QImage)), this, SLOT(hk_cam_u_show(QImage)));
    hk_up->start();

    connect(ui->sharpen_rb,SIGNAL(clicked(bool)),
        this,SLOT(state_change()));
    connect(ui->save_img_pb,SIGNAL(released()),
        this,SLOT(hk_cam_save()));

    ui->car_f_img_l->setScaledContents(true);
    ui->car_h_img_l->setScaledContents(true);

    car = new CAR();
    connect(car, SIGNAL(car_img(QImage)), this, SLOT(car_img_show(QImage)));
    connect(car, SIGNAL(car_img1(QImage)), this, SLOT(car_img1_show(QImage)));
    connect(car, SIGNAL(car_uart(float*)), this, SLOT(car_status_feedback(float*)));
    car->start();

    car_img_slc_init();

    // 所有按键都在一个槽函数中处理
    QList<QPushButton *> pblist = ui->tabWidget->findChildren<QPushButton *>();
    foreach(auto pb, pblist){
        if(pb->objectName() == QString("save_img_pb")) continue;
        connect(pb, SIGNAL(released()), this, SLOT(car_command()));
    }
    pblist = ui->tabWidget_2->findChildren<QPushButton *>();
    foreach(auto pb, pblist){
        if(pb->objectName() == QString("save_img_pb")) continue;
        connect(pb, SIGNAL(released()), this, SLOT(car_command()));
    }

    // 所有滑块在一个槽函数中处理
    QList<QSlider *> sllist = ui->tabWidget->findChildren<QSlider *>();
    foreach(auto sl, sllist){
        connect(sl, SIGNAL(valueChanged(int)), this, SLOT(car_command2(int)));
    }
    sllist = ui->tabWidget_2->findChildren<QSlider *>();
    foreach(auto sl, sllist){
        connect(sl, SIGNAL(valueChanged(int)), this, SLOT(car_command2(int)));
    }
    // 所有编辑数值在一个槽函数中处理
    QDoubleValidator* aDoubleValidator = new QDoubleValidator;
    QList<QLineEdit *>lelist = ui->tabWidget->findChildren<QLineEdit *>();
    foreach(auto le, lelist){
        aDoubleValidator->setRange(-1e15, 1e15, 5);
        le->setValidator(aDoubleValidator);
        connect(le, SIGNAL(editingFinished()), this, SLOT(car_command2(int)));
    }
    lelist = ui->tabWidget_2->findChildren<QLineEdit *>();
    foreach(auto le, lelist){
        aDoubleValidator->setRange(-1e15, 1e15, 5);
        le->setValidator(aDoubleValidator);
        connect(le, SIGNAL(editingFinished()), this, SLOT(car_command2(int)));
    }
    car_init();

    connect(ui->hk_cam_f_rb, SIGNAL(toggled(bool)), this, SLOT(hk_cam_f_rb_open()));
    connect(ui->hk_cam_u_rb, SIGNAL(toggled(bool)), this, SLOT(hk_cam_u_rb_open()));
    // 一开始打开前相机
    hk_cam_f_rb_open();
    // 初始化界面反馈
    float uart_val[16] = {0.0f};
    car_status_feedback(uart_val);

    delete aDoubleValidator;
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
        hk_now = hk;
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
        hk_now = hk_up;
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

void MainWindow::car_status_feedback(float *uart_val){

    ui->car_speed_l->setText(QString::number(uart_val[0]));
    ui->car_yaw_l->setText(QString::number(uart_val[1]));
    if(uart_val[2] == 0){
        ui->updown_l->setText("DOWN");
    }else{
        ui->updown_l->setText("UP");
    }
    // 拨杆
    ui->bogan_p_l->setText(QString::number(uart_val[4]));
    ui->bogan_v_l->setText(QString::number(uart_val[5]));
    ui->bogan_t_l->setText(QString::number(uart_val[6]));

    ui->laser0_l->setText(QString::number(uart_val[8]) + QString(" mm"));
    ui->laser1_l->setText(QString::number(uart_val[9]));
    ui->laser2_l->setText(QString::number(uart_val[10]));

    ui->ultrasound_f->setText(QString::number(uart_val[12]));
    ui->ultrasound_f_2->setText(QString::number(uart_val[13]));
    
}

void MainWindow::car_command(){

    QObject *object = QObject::sender();
    QPushButton *pb = qobject_cast<QPushButton *>(object);
    // 默认取消软急停
    car->emgc = 0.0;
    if(pb->objectName() == QString("up_down_pb")){ 
        // 升降
        // pb->setText(QString(""));
        if((int)(car->lift) == 0) car->lift = 1;
        else car->lift = 0;
        // printf("up_down_pb\n");
    }else if(pb->objectName() == QString("supp_pb")){
        // 前支撑
        if((int)(car->supp) == 0) car->supp = 1;
        else car->supp = 0;
        // printf("supp_pb\n");
    }else if(pb->objectName() == QString("emgc_pb")){
        // 软急停
        car->emgc = 120.0;
        car->move_spd = 0.0;
        car->dir_spd = 0.0;
        car->bogan_v = 0.0;
        car->supp = 0.0;
        car->lift = 0.0; 
        car->light_on=0.0;car->light_on2=0.0;car->light_on3=0.0;
        // printf("emgc_pb\n");
    }
    
    float val_send[FRAME_LENGTH] = {
        car->move_spd, car->dir_spd, car->dir, car->emgc,
        car->bogan_p, car->bogan_v, car->supp, 0.0, 
        car->lift, car->light_on, car->light_on2, car->light_on3, 
        0.0, 0.0, 0.0, 0.0
    };
    car_slc_send(val_send);
}

void MainWindow::car_command2(int val){

    QObject *object = QObject::sender();
    QSlider *sl = qobject_cast<QSlider *>(object);

    // 默认取消软急停
    car->emgc = 0.0;
    if(sl->objectName() == QString("hS_0")){ 
        // 前灯
        car->light_on = data_map(val, 0, 10000, car->light_on_rge);
        ui->lE_0->setText(QString::number(car->light_on));
        // printf("light_on %f\n", car->light_on);
    }else if(sl->objectName() == QString("hS_1")){
        // 上灯
        car->light_on2 = data_map(val, 0, 10000, car->light_on_rge);
        ui->lE_1->setText(QString::number(car->light_on2));
        // printf("light_on2 %f\n", car->light_on2);
    }else if(sl->objectName() == QString("hS_2")){
        // 视野灯
        car->light_on3 = data_map(val, 0, 10000, car->light_on_rge);
        ui->lE_2->setText(QString::number(car->light_on3));
        // printf("light_on3 %f\n", car->light_on3);
    }else if(sl->objectName() == QString("hS_3")){
        // 拨杆速度
        car->bogan_v = data_map(val, 5000, 10000, car->bogan_v_rge);
        ui->lE_3->setText(QString::number(car->bogan_v));
        // printf("bogan_v %f\n", car->bogan_v);
    }else if(sl->objectName() == QString("hS_4")){
        // 前进速度
        car->move_spd = data_map(val, 5000, 10000, car->move_spd_rge);
        ui->lE_4->setText(QString::number(car->move_spd));
        // printf("move_spd %f\n", car->move_spd);
    }else if(sl->objectName() == QString("hS_5")){
        // 角速度
        car->dir_spd = data_map(val, 5000, 10000, car->dir_spd_rge);
        ui->lE_5->setText(QString::number(car->dir_spd));
        // printf("dir_spd %f\n", car->dir_spd);
    }else if(sl->objectName() == QString("hS_6")){
        // 前进角度
        car->dir = data_map(val, 5000, 10000, car->dir_rge);
        ui->lE_6->setText(QString::number(car->dir));
        // printf("dir %f\n", car->dir);
    }

    float val_send[FRAME_LENGTH] = {
        car->move_spd, car->dir_spd, car->dir, car->emgc,
        car->bogan_p, car->bogan_v, car->supp, 0.0, 
        car->lift, car->light_on, car->light_on2, car->light_on3, 
        0.0, 0.0, 0.0, 0.0
    };
    car_slc_send(val_send);
}

void MainWindow::car_command3(){

    QObject *object = QObject::sender();
    QLineEdit *le = qobject_cast<QLineEdit *>(object);

    // // 默认取消软急停
    // car->emgc = 0.0;
    // if(le->objectName() == QString("lE_0")){ 
    //     // 前灯
    //     car->light_on = data_map(val, 0, 10000, car->light_on_rge);
    //     printf("light_on %f\n", car->light_on);
    // }else if(le->objectName() == QString("lE_1")){
    //     // 上灯
    //     car->light_on2 = data_map(val, 0, 10000, car->light_on_rge);
    //     printf("light_on2 %f\n", car->light_on2);
    // }else if(le->objectName() == QString("lE_2")){
    //     // 视野灯
    //     car->light_on3 = data_map(val, 0, 10000, car->light_on_rge);
    //     printf("light_on3 %f\n", car->light_on3);
    // }else if(le->objectName() == QString("lE_3")){
    //     // 拨杆速度
    //     car->bogan_v = data_map(val, 5000, 10000, car->bogan_v_rge);
    //     printf("bogan_v %f\n", car->bogan_v);
    // }else if(le->objectName() == QString("lE_4")){
    //     // 前进速度
    //     car->move_spd = data_map(val, 5000, 10000, car->move_spd_rge);
    //     printf("move_spd %f\n", car->move_spd);
    // }else if(le->objectName() == QString("lE_5")){
    //     // 角速度
    //     car->dir_spd = data_map(val, 5000, 10000, car->dir_spd_rge);
    //     printf("dir_spd %f\n", car->dir_spd);
    // }else if(le->objectName() == QString("lE_6")){
    //     // 前进角度
    //     car->dir = data_map(val, 5000, 10000, car->dir_rge);
    //     printf("dir %f\n", car->dir);
    // }

    // float val_send[FRAME_LENGTH] = {
    //     car->move_spd, car->dir_spd, car->dir, car->emgc,
    //     car->bogan_p, car->bogan_v, car->supp, 0.0, 
    //     car->lift, car->light_on, car->light_on2, car->light_on3, 
    //     0.0, 0.0, 0.0, 0.0
    // };
    // car_slc_send(val_send);
    
}

void MainWindow::car_init(){

    ui->lE_0->setText(QString::number(0));
    ui->hS_0->setValue(data_mapback(ui->lE_0->text().toFloat(),
             car->light_on_rge, 0, 10000));
    
    ui->lE_1->setText(QString::number(0));
    ui->hS_1->setValue(data_mapback(ui->lE_1->text().toFloat(),
             car->light_on_rge, 0, 10000));
    
    ui->lE_2->setText(QString::number(0));
    ui->hS_2->setValue(data_mapback(ui->lE_2->text().toFloat(),
             car->light_on_rge, 0, 10000));
    
    ui->lE_3->setText(QString::number(0));
    ui->hS_3->setValue(data_mapback(ui->lE_3->text().toFloat(), 
            car->bogan_v_rge, 5000, 10000));
    
    ui->lE_4->setText(QString::number(0));
    ui->hS_4->setValue(data_mapback(ui->lE_4->text().toFloat(), 
            car->move_spd_rge, 5000, 10000));

    ui->lE_5->setText(QString::number(0));
    ui->hS_5->setValue(data_mapback(ui->lE_5->text().toFloat(), 
            car->dir_spd_rge, 5000, 10000));

    ui->lE_6->setText(QString::number(0));
    ui->hS_6->setValue(data_mapback(ui->lE_6->text().toFloat(), 
            car->dir_rge, 5000, 10000));

}

void MainWindow::keyPressEvent(QKeyEvent *ev){

    if(ev->key() == Qt::Key_W ){
        car->move_spd += 100;
    }else if(ev->key() == Qt::Key_S){
        car->move_spd -= 100;
    }else if(ev->key() == Qt::Key_A){
        car->dir_spd += 60;
    }else if(ev->key() == Qt::Key_D){
        car->dir_spd -= 60;
    }else if(ev->key() == Qt::Key_G && ev->modifiers() == Qt::ControlModifier){
        car->bogan_v +=10;
    }else if(ev->key() == Qt::Key_H && ev->modifiers() == Qt::ControlModifier){
        car->bogan_v -=10;
    }else if(ev->key() == Qt::Key_V && ev->modifiers() == Qt::ControlModifier){
        car->lift = 0;
    }else if(ev->key() == Qt::Key_B && ev->modifiers() == Qt::ControlModifier){
        car->lift = 1;
    }else if(ev->key() == Qt::Key_N && ev->modifiers() == Qt::ControlModifier){
        car->light_on = 0;
    }else if(ev->key() == Qt::Key_M && ev->modifiers() == Qt::ControlModifier){
        car->light_on = 1;
    }else if(ev->key() == Qt::Key_K && ev->modifiers() == Qt::ControlModifier){
        car->supp = 0;
    }else if(ev->key() == Qt::Key_L && ev->modifiers() == Qt::ControlModifier){
        car->supp = 1;
    }
    
    float val[FRAME_LENGTH] = {
        car->move_spd, car->dir_spd, car->dir, car->emgc,
        car->bogan_p, car->bogan_v, car->supp, 0.0, 
        car->lift, car->light_on, car->light_on2, car->light_on3, 
        0.0, 0.0, 0.0, 0.0
    };
    car_slc_send(val);
    return;
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
        hk_now->hkp.issharpen = true;
    else
        hk_now->hkp.issharpen = false;
    mutex.unlock();

}

void MainWindow::hk_cam_save(){

    mutex.lock();
    hk_now->hkp.issave = true;
    mutex.unlock();
    
}





