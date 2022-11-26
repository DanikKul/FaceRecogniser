#include <string.h>
#include "drawer.h"

Drawer::Drawer(StringConv text, cv::Scalar textColor, cv::Scalar rectColor) {
    this -> text = text;
    this -> textColor = textColor;
    this -> rectColor = rectColor;
}

Drawer::Drawer(const Drawer& drawer) {
    this -> text = drawer.getText();
    this -> textColor = drawer.getTextColor();
    this -> rectColor = drawer.getRectColor();
}

cv::Scalar Drawer::getTextColor() const {
    return this -> textColor;
}

cv::Scalar Drawer::getRectColor() const {
    return this -> rectColor;
}

StringConv Drawer::getText() const {
    return this -> text;
}

void Drawer::setRectColor(cv::Scalar rectColor) {
    this -> rectColor = rectColor;
}

void Drawer::setTextColor(cv::Scalar textColor) {
    this -> textColor = textColor;
}

void Drawer::setText(StringConv text) {
    this -> text = text;
}
