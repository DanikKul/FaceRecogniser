#include <iostream>
#include "recogniserdrawer.h"

RecogniserDrawer::RecogniserDrawer(StringConv text, cv::Scalar textColor, cv::Scalar rectColor)
    :Drawer(text, textColor, rectColor){}

RecogniserDrawer::RecogniserDrawer(const RecogniserDrawer& rd) : Drawer(rd){}

void RecogniserDrawer::drawFaces(cv::Mat& img, std::vector<cv::Rect>& faces) {
    std::cout << "INFO: Отрисовка лиц на изображении" << std::endl;
    cv::rectangle(img, faces[0], this -> getRectColor(), 5);
    std::cout << "SUCCESS: Отрисовка лиц завершена!" << std::endl;
}

void RecogniserDrawer::setTextInImage(cv::Mat& img, cv::Point pt) {
    std::cout << "INFO: Отрисовка текста на изображении" << std::endl;
    cv::putText(img, this -> getText().cpp_str(), pt,
                cv::FONT_HERSHEY_DUPLEX, img.rows / 500, this -> getTextColor(), 3);
}
