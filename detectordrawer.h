#ifndef DETECTORDRAWER_H
#define DETECTORDRAWER_H
#include <opencv2/imgproc.hpp>
#include "drawer.h"


class DetectorDrawer : public Drawer{
public:

    DetectorDrawer(StringConv text, cv::Scalar textColor, cv::Scalar rectColor);
    DetectorDrawer(const DetectorDrawer&);
    void drawFaces(cv::Mat&, std::vector<cv::Rect>&) override;
    void setTextInImage(cv::Mat&, cv::Point) override;

};

#endif // DETECTORDRAWER_H
