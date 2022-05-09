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
    
    cv::VideoCapture hk_img;
    cv::VideoCapture car_f;
    cv::VideoCapture car_h;
    cv::Mat frame_f,frame_h;
    bool car_f_stop = false;
    cv::Mat getFrame_f();
    void OpenCamera();

    QPoint currentPt;
    QPoint currentMt;
    
    HKHandle *hk;

private:
    Ui::MainWindow *ui;
protected:
    bool eventFilter(QObject *target, QEvent *event);

protected slots:
    void img_update();
    void img_show(QImage);

};

#endif // MAINWINDOW_H
