#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "facedetector.h"
#include "defines.h"
#include "recogniser.h"
#include <QInputDialog>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "detectordrawer.h"
#include "exceptions.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    std::cout << "INFO: Создание основного окна" << std::endl;
    ui->setupUi(this);
    ui->display_image->setText("Подождите прогрузки программы...");
    this->isTrained = false;
    this->isRecording = false;
    std::cout << "INFO: Инициализация камеры" << std::endl;
    cv::VideoCapture(0);
    std::cout << "SUCCESS: Инициализация камеры завершена" << std::endl;
    std::cout << "SUCCESS: Создано основное окно!" << std::endl;
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::displayImage(cv::Mat img) {
    std::cout << "INFO: Вывод изображения" << std::endl;
    this->img = img;
    QPixmap pixmap = convertImage(img);
    ui->display_image->setWindowFlag(Qt::Window, false);
    ui->display_image->setPixmap(pixmap.scaled(ui->display_image->width() - 40,
                                               ui->display_image->height() - 40,
                                               Qt::KeepAspectRatio));
    std::cout << "SUCCESS: Вывод изображения прошел успешно!" << std::endl;
}


QPixmap MainWindow::convertImage(cv::Mat img) {
    std::cout << "INFO: Конвертирование изображения" << std::endl;
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(imdisplay);
    std::cout << "SUCCESS: Конвертирование изображения завершено" << std::endl;
    return pixmap;
}


void MainWindow::on_getAllFaces_clicked() {
    std::cout << "INFO: Процесс нахождения лиц на фотографии" << std::endl;

    try {
        if (this->img.empty()) throw ExceptionEmpty();
        this->cached_img.copyTo(this->img);
    } catch (ExceptionEmpty& exception) {
        exception.getError();
        ui->display_image->setText("Сначала загрузите изображение!");
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        ui->display_image->setText("Сначала загрузите изображение!");
        return;
    }

    FaceDetector fd(FD_FACE_CASCADE_PATH, FD_SCALE_FACTOR, FD_MIN_NEIGHBOURS, FD_MIN_SIZE_RATIO, FD_MAX_SIZE_RATIO);
    std::vector<cv::Rect> faces;
    fd.findObjectsInImage(this->img, faces);

    try {
        if (this -> img.channels() != 3) throw ExceptionWrongChannels();
        cvtColor(this->img, this->img, cv::COLOR_BGR2RGB);
    } catch (ExceptionWrongChannels& exception) {
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

    DetectorDrawer dd("", cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 0));
    dd.drawFaces(img, faces);
    displayImage(img);
    std::cout << "SUCCESS: Процесс нахождения лиц на фотографии завершен" << std::endl;
}


void MainWindow::setImage(cv::Mat img) {
    std::cout << "INFO: Установка нового изображения" << std::endl;
    this -> img = img;
    displayImage(img);
    std::cout << "INFO: Установка нового изображения завершена!" << std::endl;
}


void MainWindow::saveToFile() {
    std::cout << "INFO: Сохранение изображения в файл" << std::endl;

    try {
        if (this->img.empty()) throw ExceptionEmpty();
    } catch (ExceptionEmpty& exception) {
        ui->display_image->setText("Сначала загрузите изображение!");
        return;
    } catch (...) {
        ui->display_image->setText("Сначала загрузите изображение!");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Сохранить изображение"), "",
         tr("JPG-Image (*.jpg);;JPEG-Image (*.jpeg);;PNG-Image (*.png)"));

    try {

        if (fileName.isEmpty()) throw ExceptionEmpty();
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly)) throw ExceptionFileLoad();

        if (img.channels() != 3) throw ExceptionWrongChannels();

        cvtColor(img, img, cv::COLOR_RGB2BGR);

        if (!(imwrite(file.fileName().toStdString(), this->img))) throw ExceptionFileWrite();

    } catch (ExceptionEmpty& exception) {
        exception.getError();
        return;
    } catch (ExceptionFileLoad& exception) {
        exception.getError();
        QFile file(fileName);
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    } catch (ExceptionWrongChannels& exception) {
        exception.getError();
        return;
    } catch (ExceptionFileWrite& exception) {
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

    std::cout << "SUCCESS: Изображение сохранено!" << std::endl;
}


void MainWindow::loadFromFile() {
    std::cout << "INFO: Загрузка изображения" << std::endl;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Открыть изображение"), "",
        tr("Изображение (*.jpg; *.jpeg; *.png)"));
    try {
        if (fileName.isEmpty()) throw ExceptionEmpty();

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) throw ExceptionFileLoad();

        cv::Mat img = cv::imread(file.fileName().toStdString());
        this->img = img;
        img.copyTo(this->cached_img);

        if (img.channels() != 3) throw ExceptionWrongChannels();

        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        displayImage(img);

    } catch (ExceptionEmpty& exception) {
        exception.getError();
        return;
    } catch (ExceptionFileLoad& exception) {
        exception.getError();
        QFile file(fileName);
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    } catch (ExceptionWrongChannels& exception) {
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

    std::cout << "SUCCESS: Изображение загружено!" << std::endl;
}


void MainWindow::on_loadButton_clicked() {
    loadFromFile();
}


void MainWindow::on_exportButton_clicked() {
    saveToFile();
}


void MainWindow::on_train_clicked() {
    this->ui->display_image->setText("Пожалуйста, подождите...");
    this->isTrained = true;
    this->recogniser.train(DATASET_PATH);
    this->ui->display_image->setText("Готово!");
}


void MainWindow::on_recognize_clicked() {
    std::cout << "INFO: Процесс распознавания лиц начался" << std::endl;

    try {

        if (!this->isTrained) throw ExceptionEmptyModel();
        if (this->img.empty()) throw ExceptionEmpty();

        this->cached_img.copyTo(this->img);
        recogniser.recognize(this->img, DATASET_PATH);

        if (this->img.channels() != 3) throw ExceptionWrongChannels();

        cvtColor(this->img, this->img, cv::COLOR_BGR2RGB);
        displayImage(img);

    } catch (ExceptionEmptyModel& exception) {
        exception.getError();
        this->ui->display_image->setText("Сначала обучите модель!");
        return;
    } catch (ExceptionEmpty& exception) {
        exception.getError();
        this->ui->display_image->setText("Сначала загрузите изображение!");
        return;
    } catch (ExceptionWrongChannels& exception) {
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

    std::cout << "SUCCESS: Процесс распознавания лиц завершен!" << std::endl;
}


void MainWindow::on_addDataset_clicked() {
    bool isOk;
    std::cout << "INFO: Вызов окна ввода!" << std::endl;
    QString text = QInputDialog::getText(this, tr("Введите имя человека"), tr("Введите имя человека латиницей"), QLineEdit::Normal, "", &isOk);

    if (!isOk) return;

    try {
        if (text.isEmpty()) throw ExceptionEmpty();
        std::string std_string = text.toStdString();
        recogniser.getImages(std_string.c_str());
    } catch (ExceptionEmpty& exception) {
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    std::cout << "SUCCESS: Закрытие окна ввода!" << std::endl;
}


void MainWindow::on_exitButton_clicked() {
    exit(0);
}


void MainWindow::on_instructionButton_clicked() {
    std::cout << "INFO: Вызов справки!" << std::endl;
    this->ui->display_image->setText(TEXT_INFO);
}


void MainWindow::on_makePhoto_clicked() {
    std::cout << "INFO: Вызов камеры" << std::endl;
    cv::VideoCapture capture;
    try {
        capture.open(0);
        if (!capture.isOpened()) throw ExceptionCamera();
    } catch (ExceptionCamera& exception) {
        exception.getError();
        this->ui->display_image->setText("Ошибка с открытием камеры!");
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        this->ui->display_image->setText("Ошибка с открытием камеры!");
        return;
    }
    if (this -> isRecording == true) {
        this -> isRecording = false;
        return;
    } else {
        this -> isRecording = true;
    }
    cv::Mat img;
    while (isRecording) {

        capture.read(img);

        try {
            if (img.channels() != 3) throw ExceptionWrongChannels();
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        } catch (ExceptionWrongChannels& exception) {
            exception.getError();
            continue;
        } catch (...) {
            Exception exception;
            exception.getError();
        }

        displayImage(img);
        QApplication::processEvents();
    }
    cv::Mat buff;
    img.copyTo(buff);
    buff.copyTo(this->img);

    try {
        cv::cvtColor(buff, buff, cv::COLOR_BGR2RGB);
    } catch (ExceptionWrongChannels& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    buff.copyTo(this->cached_img);
    displayImage(img);
}

