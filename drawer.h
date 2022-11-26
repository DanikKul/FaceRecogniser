#ifndef DRAWER_H
#define DRAWER_H
#include <opencv2/imgproc.hpp>
#include <vector>
#include "stringconv.h"


class Drawer {

    StringConv text; // string
    cv::Scalar textColor;
    cv::Scalar rectColor;

public:

    Drawer(StringConv text, cv::Scalar textColor, cv::Scalar rectColor);
    Drawer(const Drawer&);
    virtual void drawFaces(cv::Mat&, std::vector<cv::Rect>&) = 0;
    virtual void setTextInImage(cv::Mat&, cv::Point) = 0;
    cv::Scalar getRectColor() const;
    cv::Scalar getTextColor() const;
    StringConv getText() const;
    void setRectColor(cv::Scalar);
    void setTextColor(cv::Scalar);
    void setText(StringConv);

};

#endif // DRAWER_H
