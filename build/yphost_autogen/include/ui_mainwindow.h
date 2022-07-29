/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *hk_sa;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QLabel *hk_img_l;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *car_f_img_l;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *car_h_img_l;
    QTextBrowser *debug_tb;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QRadioButton *hk_cam_f_rb;
    QRadioButton *hk_cam_u_rb;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QLabel *framerate_l;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QRadioButton *sharpen_rb;
    QPushButton *save_img_pb;
    QPushButton *up_down_pb;
    QPushButton *light_pb;
    QPushButton *bogan_pb;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QLabel *car_speed_l;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QLabel *car_yaw_l;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_7;
    QLabel *updown_l;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_9;
    QLabel *bogan_p_l;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_10;
    QLabel *bogan_v_l;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_11;
    QLabel *bogan_t_l;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QLabel *laser0_l;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_12;
    QLabel *laser1_l;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_13;
    QLabel *laser2_l;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_14;
    QLabel *ultrasound_f;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_15;
    QLabel *ultrasound_f_2;
    QSpacerItem *verticalSpacer_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(986, 818);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_8 = new QVBoxLayout(centralWidget);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font;
        font.setPointSize(20);
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        horizontalLayout_2 = new QHBoxLayout(tab_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        hk_sa = new QScrollArea(tab_3);
        hk_sa->setObjectName(QStringLiteral("hk_sa"));
        hk_sa->setMinimumSize(QSize(715, 522));
        hk_sa->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 736, 640));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        hk_img_l = new QLabel(scrollAreaWidgetContents);
        hk_img_l->setObjectName(QStringLiteral("hk_img_l"));
        hk_img_l->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(hk_img_l);

        hk_sa->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(hk_sa);

        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_3 = new QVBoxLayout(tab_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        scrollArea_2 = new QScrollArea(tab_4);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 736, 283));
        horizontalLayout_3 = new QHBoxLayout(scrollAreaWidgetContents_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        car_f_img_l = new QLabel(scrollAreaWidgetContents_2);
        car_f_img_l->setObjectName(QStringLiteral("car_f_img_l"));
        car_f_img_l->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(car_f_img_l);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_3->addWidget(scrollArea_2);

        scrollArea_3 = new QScrollArea(tab_4);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 736, 283));
        horizontalLayout_4 = new QHBoxLayout(scrollAreaWidgetContents_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        car_h_img_l = new QLabel(scrollAreaWidgetContents_3);
        car_h_img_l->setObjectName(QStringLiteral("car_h_img_l"));
        car_h_img_l->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(car_h_img_l);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_3->addWidget(scrollArea_3);

        debug_tb = new QTextBrowser(tab_4);
        debug_tb->setObjectName(QStringLiteral("debug_tb"));
        debug_tb->setMaximumSize(QSize(16777215, 60));

        verticalLayout_3->addWidget(debug_tb);

        tabWidget_2->addTab(tab_4, QString());

        horizontalLayout_5->addWidget(tabWidget_2);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(200, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        hk_cam_f_rb = new QRadioButton(tab);
        hk_cam_f_rb->setObjectName(QStringLiteral("hk_cam_f_rb"));
        hk_cam_f_rb->setChecked(true);

        verticalLayout_2->addWidget(hk_cam_f_rb);

        hk_cam_u_rb = new QRadioButton(tab);
        hk_cam_u_rb->setObjectName(QStringLiteral("hk_cam_u_rb"));
        hk_cam_u_rb->setChecked(false);

        verticalLayout_2->addWidget(hk_cam_u_rb);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_6->addWidget(label);

        framerate_l = new QLabel(tab);
        framerate_l->setObjectName(QStringLiteral("framerate_l"));
        framerate_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_6->addWidget(framerate_l);


        verticalLayout->addLayout(horizontalLayout_6);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_7->addWidget(label_3);

        sharpen_rb = new QRadioButton(groupBox);
        sharpen_rb->setObjectName(QStringLiteral("sharpen_rb"));

        horizontalLayout_7->addWidget(sharpen_rb);


        verticalLayout_6->addLayout(horizontalLayout_7);


        verticalLayout->addWidget(groupBox);

        save_img_pb = new QPushButton(tab);
        save_img_pb->setObjectName(QStringLiteral("save_img_pb"));

        verticalLayout->addWidget(save_img_pb);

        up_down_pb = new QPushButton(tab);
        up_down_pb->setObjectName(QStringLiteral("up_down_pb"));
        up_down_pb->setMinimumSize(QSize(40, 40));

        verticalLayout->addWidget(up_down_pb);

        light_pb = new QPushButton(tab);
        light_pb->setObjectName(QStringLiteral("light_pb"));
        light_pb->setMinimumSize(QSize(40, 40));

        verticalLayout->addWidget(light_pb);

        bogan_pb = new QPushButton(tab);
        bogan_pb->setObjectName(QStringLiteral("bogan_pb"));
        bogan_pb->setMinimumSize(QSize(40, 40));

        verticalLayout->addWidget(bogan_pb);

        verticalSpacer = new QSpacerItem(20, 459, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_8->addWidget(label_2);

        car_speed_l = new QLabel(tab_2);
        car_speed_l->setObjectName(QStringLiteral("car_speed_l"));
        car_speed_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(car_speed_l);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);

        car_yaw_l = new QLabel(tab_2);
        car_yaw_l->setObjectName(QStringLiteral("car_yaw_l"));
        car_yaw_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_9->addWidget(car_yaw_l);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_12->addWidget(label_7);

        updown_l = new QLabel(tab_2);
        updown_l->setObjectName(QStringLiteral("updown_l"));
        updown_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_12->addWidget(updown_l);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_14->addWidget(label_9);

        bogan_p_l = new QLabel(tab_2);
        bogan_p_l->setObjectName(QStringLiteral("bogan_p_l"));
        bogan_p_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_14->addWidget(bogan_p_l);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_15->addWidget(label_10);

        bogan_v_l = new QLabel(tab_2);
        bogan_v_l->setObjectName(QStringLiteral("bogan_v_l"));
        bogan_v_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_15->addWidget(bogan_v_l);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_16->addWidget(label_11);

        bogan_t_l = new QLabel(tab_2);
        bogan_t_l->setObjectName(QStringLiteral("bogan_t_l"));
        bogan_t_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_16->addWidget(bogan_t_l);


        verticalLayout_4->addLayout(horizontalLayout_16);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_10->addWidget(label_5);

        laser0_l = new QLabel(tab_2);
        laser0_l->setObjectName(QStringLiteral("laser0_l"));
        laser0_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_10->addWidget(laser0_l);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_17->addWidget(label_12);

        laser1_l = new QLabel(tab_2);
        laser1_l->setObjectName(QStringLiteral("laser1_l"));
        laser1_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_17->addWidget(laser1_l);


        verticalLayout_4->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_18->addWidget(label_13);

        laser2_l = new QLabel(tab_2);
        laser2_l->setObjectName(QStringLiteral("laser2_l"));
        laser2_l->setMinimumSize(QSize(50, 0));

        horizontalLayout_18->addWidget(laser2_l);


        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_19->addWidget(label_14);

        ultrasound_f = new QLabel(tab_2);
        ultrasound_f->setObjectName(QStringLiteral("ultrasound_f"));
        ultrasound_f->setMinimumSize(QSize(50, 0));

        horizontalLayout_19->addWidget(ultrasound_f);


        verticalLayout_4->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_20->addWidget(label_15);

        ultrasound_f_2 = new QLabel(tab_2);
        ultrasound_f_2->setObjectName(QStringLiteral("ultrasound_f_2"));
        ultrasound_f_2->setMinimumSize(QSize(50, 0));

        horizontalLayout_20->addWidget(ultrasound_f_2);


        verticalLayout_4->addLayout(horizontalLayout_20);

        verticalSpacer_3 = new QSpacerItem(20, 439, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout_5->addWidget(tabWidget);


        verticalLayout_8->addLayout(horizontalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 986, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\350\210\252\345\217\221\345\217\266\347\211\207\346\243\200\346\265\213\350\243\205\347\275\256\347\263\273\347\273\237", Q_NULLPTR));
        hk_img_l->setText(QApplication::translate("MainWindow", "No Image", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("MainWindow", "\344\270\273\350\247\206\351\207\216", Q_NULLPTR));
        car_f_img_l->setText(QApplication::translate("MainWindow", "No Image", Q_NULLPTR));
        car_h_img_l->setText(QApplication::translate("MainWindow", "No Image", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "\350\275\246\350\275\275\350\247\206\351\207\216", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\344\270\273\347\233\270\346\234\272", Q_NULLPTR));
        hk_cam_f_rb->setText(QApplication::translate("MainWindow", "\345\211\215\346\213\215\346\221\204\345\203\217\346\234\272", Q_NULLPTR));
        hk_cam_u_rb->setText(QApplication::translate("MainWindow", "\344\270\212\346\213\215\346\221\204\345\203\217\346\234\272", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\270\247\347\216\207\357\274\232", Q_NULLPTR));
        framerate_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("MainWindow", "\351\224\220\345\214\226\357\274\232", Q_NULLPTR));
        sharpen_rb->setText(QString());
        save_img_pb->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", Q_NULLPTR));
        up_down_pb->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\345\215\207\351\231\215\346\235\206", Q_NULLPTR));
        light_pb->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\345\205\211\346\272\220", Q_NULLPTR));
        bogan_pb->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\346\213\250\346\235\206", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\344\270\273\347\233\270\346\234\272\345\217\202\346\225\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\351\200\237\345\272\246\357\274\232", Q_NULLPTR));
        car_speed_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\247\277\346\200\201\357\274\232", Q_NULLPTR));
        car_yaw_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\345\215\207\351\231\215\346\235\206\357\274\232", Q_NULLPTR));
        updown_l->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "\346\213\250\346\235\206\350\247\222\345\272\246\357\274\232", Q_NULLPTR));
        bogan_p_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\346\213\250\346\235\206\351\200\237\345\272\246\357\274\232", Q_NULLPTR));
        bogan_v_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "\346\213\250\346\235\206\346\211\255\347\237\251\357\274\232", Q_NULLPTR));
        bogan_t_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\277\200\345\205\211\346\225\260\346\215\2560\357\274\232", Q_NULLPTR));
        laser0_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "\346\277\200\345\205\211\346\225\260\346\215\2561\357\274\232", Q_NULLPTR));
        laser1_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\346\277\200\345\205\211\346\225\260\346\215\2562\357\274\232", Q_NULLPTR));
        laser2_l->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "\350\266\205\345\243\260\346\225\260\346\215\256(\345\211\215)\357\274\232", Q_NULLPTR));
        ultrasound_f->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "\350\266\205\345\243\260\346\225\260\346\215\256(\345\220\216)\357\274\232", Q_NULLPTR));
        ultrasound_f_2->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\350\275\246\347\212\266\346\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
