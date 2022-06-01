#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>
#include <QThread>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>

#include "hkimage.h"
#include "car.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer *timer;
    QPixmap mp;
    
    QPoint currentPt;
    QPoint currentMt;
    
    HKHandle *hk;
    HKHandle *hk_up;
    CAR *car;
    
private:
    Ui::MainWindow *ui;

protected:
    bool eventFilter(QObject *target, QEvent *event);
    void closeEvent(QCloseEvent *event);
    
protected slots:
    void m_timer();
    void hk_cam_f_show(QImage);
    void hk_cam_f_rb_open();
    void hk_cam_u_show(QImage);
    void hk_cam_u_rb_open();

    void state_change();

    void car_img_show(QImage);
    void car_img1_show(QImage);
    void car_status_feedback(float *uart_val);

    void car_command();

};

#endif // MAINWINDOW_H
