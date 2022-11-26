#include <iostream>
#include "detectordrawer.h"

DetectorDrawer::DetectorDrawer(StringConv text, cv::Scalar textColor, cv::Scalar rectColor)
    : Drawer(text, textColor, rectColor){}

DetectorDrawer::DetectorDrawer(const DetectorDrawer& dd) : Drawer(dd){}

void DetectorDrawer::drawFaces(cv::Mat& img, std::vector<cv::Rect>& faces) {
    std::cout << "INFO: Отрисовка лиц на изображении" << std::endl;
    for (auto face : faces) {
        cv::Rect rect;
        rect.x = face.x - 10;
        rect.y = face.y - 10;
        rect.width = face.width + 20;
        rect.height = face.height + 20;
        cv::rectangle(img, rect, getRectColor(), (int)face.width / 50);
    }
    std::cout << "SUCCESS: Отрисовка лиц завершена!" << std::endl;
}

void DetectorDrawer::setTextInImage(cv::Mat& img, cv::Point pt) {
    std::cout << "INFO: Отрисовка текста на изображении" << std::endl;
    cv::putText(img, this -> getText().cpp_str(), pt,
                cv::FONT_HERSHEY_DUPLEX, img.rows / 500, this -> getTextColor(), 5);
}
