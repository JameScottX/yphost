#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss("/home/jame/Desktop/yphost/examples/Dark Orange (FreeCAD)/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    qss.close();

    MainWindow w;
    w.show();

    return a.exec();
}




