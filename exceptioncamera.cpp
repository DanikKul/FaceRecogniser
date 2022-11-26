#include "exceptioncamera.h"

ExceptionCamera::ExceptionCamera() {
    this -> code = 15;
    strcpy(this -> msg, "Camera Error");
}

ExceptionCamera::ExceptionCamera(int code, char* msg) : Exception(code, msg) {}

