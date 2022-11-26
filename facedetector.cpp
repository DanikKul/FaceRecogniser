#include "facedetector.h"
#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>
#include "exceptions.h"

FaceDetector::FaceDetector(
        const StringConv& cascadePath,
        double scaleFactor,
        int    minNeighbours,
        double minSizeRatio,
        double maxSizeRatio) {

    try {
        if (!(cascade.load(cascadePath.c_str()))) throw ExceptionFileLoad();
    } catch (ExceptionFileLoad& exception) {
        exception.getError();
        exit(exception.getCode());
    } catch (...) {
        Exception exception;
        exception.getError();
        exit(exception.getCode());
    }

    this -> scaleFactor = scaleFactor;
    this -> minNeighbours = minNeighbours;
    this -> minSizeRatio = minSizeRatio;
    this -> maxSizeRatio = maxSizeRatio;
}

FaceDetector::~FaceDetector() = default;

// Принимает изображение (cv::Mat) и ссылку пустого вектора прямоугольников (std::vector<cv::Rect>)
// Записывает все найденные лица в вектор прямоугольников

void FaceDetector::findObjectsInImage(const cv::Mat& img, std::vector<cv::Rect>& res) {
    std::cout << "INFO: Нахождение и запись лиц с помощью сканирующего окна" << std::endl;
    cv::Mat tmp;
    int width  = img.size().width;
    int height = img.size().height;
    cv::Size minScaleSize = cv::Size((int)this -> minSizeRatio * width, (int)this -> minSizeRatio * height);
    cv::Size maxScaleSize = cv::Size((int)this -> maxSizeRatio * width, (int)this -> maxSizeRatio * height);

    try {
        if (img.channels() != 3) throw ExceptionWrongChannels();
        cv::cvtColor(img, tmp, cv::COLOR_BGR2GRAY);
    } catch (ExceptionWrongChannels& exception) {
        img.copyTo(tmp);
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    cv::equalizeHist(tmp, tmp);

    res.clear();

    try {
        if (this -> isEmpty()) throw ExceptionEmpty();
        this -> cascade.detectMultiScale(tmp,
                                         res,
                                         this -> scaleFactor,
                                         this -> minNeighbours,
                                         0,
                                         minScaleSize,
                                         maxScaleSize);
    } catch (ExceptionEmpty& exception) {
        exception.getError();
        std::cout << "ERROR: Каскад Хаара пустой!" << std::endl;
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

    std::cout << "SUCCESS: Запись лиц завершена!" << std::endl;
}

bool FaceDetector::isEmpty() {
    return this -> cascade.empty();
}

void FaceDetector::load(StringConv path) {
    try {
        if (!(this -> cascade.load(path.c_str()))) throw ExceptionFileLoad();
    } catch (ExceptionFileLoad& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }
}

void operator << (FaceDetector& detector, StringConv path) {
    detector.load(path);
}
