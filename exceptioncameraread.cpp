#include "exceptioncameraread.h"

ExceptionCameraRead::ExceptionCameraRead() {
    this -> code = 15;
    strcpy(this -> msg, "Camera Error");
}

ExceptionCameraRead::ExceptionCameraRead(int code, char* msg) : ExceptionCamera(code, msg) {}
