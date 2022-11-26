#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
#include <string>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include "algorithm.h"
#include "stringconv.h"

class FaceDetector : Algorithm {
    cv::CascadeClassifier cascade;
    double scaleFactor;
    int minNeighbours;
    double minSizeRatio;
    double maxSizeRatio;
public:
    FaceDetector(const StringConv&, double, int, double, double);
    virtual ~FaceDetector();
    void findObjectsInImage(const cv::Mat&, std::vector<cv::Rect>&);
    bool isEmpty() override;
    void load(StringConv) override;
    friend void operator << (FaceDetector&, StringConv);
};


#endif // FACEDETECTOR_H
