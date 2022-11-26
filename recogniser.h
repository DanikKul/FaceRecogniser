#ifndef RECOGNISER_H
#define RECOGNISER_H

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include "algorithm.h"
#include "stringconv.h"

class Recogniser : Algorithm {
    cv::Ptr<cv::face::LBPHFaceRecognizer> model;
    cv::CascadeClassifier classifier;
    bool existDir(StringConv name);
public:
    Recogniser();
    virtual ~Recogniser();
    int extractFaces(cv::Mat&, cv::Mat&);
    void getImages(StringConv);
    void train(const StringConv&);
    void recognize(cv::Mat&, const StringConv&);
    int extractRect(cv::Mat&, cv::Mat&, std::vector<cv::Rect>&);
    void writeModel(StringConv);
    bool isEmpty() override;
    void load(StringConv) override;
};

#endif // RECOGNISER_H
