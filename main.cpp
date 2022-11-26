#include "mainwindow.h"
#include <QApplication>
#include "opencv2/opencv.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Face Scanner");
    w.setWindowState(Qt::WindowFullScreen);
    w.show();
    return a.exec();
}
