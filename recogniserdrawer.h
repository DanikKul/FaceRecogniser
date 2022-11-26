#ifndef RECOGNISERDRAWER_H
#define RECOGNISERDRAWER_H
#include <string>
#include <opencv2/imgproc.hpp>
#include "drawer.h"


class RecogniserDrawer : public Drawer {
public:

    RecogniserDrawer(StringConv text, cv::Scalar textColor, cv::Scalar rectColor);
    RecogniserDrawer(const RecogniserDrawer&);
    void drawFaces(cv::Mat&, std::vector<cv::Rect>&) override;
    void setTextInImage(cv::Mat&, cv::Point) override;

};

#endif // RECOGNISERDRAWER_H
