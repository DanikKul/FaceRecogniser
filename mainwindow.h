#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include "recogniser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QImage imdisplay;

    cv::Mat img;

    cv::Mat cached_img;

    Recogniser recogniser;

    bool isTrained;

    bool isRecording;

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void setImage(cv::Mat);

    void saveToFile();

    void loadFromFile();

public slots:
    void displayImage(cv::Mat);

    QPixmap convertImage(cv::Mat);

private slots:
    void on_getAllFaces_clicked();

    void on_loadButton_clicked();

    void on_exportButton_clicked();

    void on_train_clicked();

    void on_recognize_clicked();

    void on_addDataset_clicked();

    void on_exitButton_clicked();

    void on_instructionButton_clicked();

    void on_makePhoto_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
