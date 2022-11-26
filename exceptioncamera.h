#ifndef EXCEPTIONCAMERA_H
#define EXCEPTIONCAMERA_H
#include "exception.h"


class ExceptionCamera : public Exception{
public:

    ExceptionCamera();
    ExceptionCamera(int, char*);

};

#endif // EXCEPTIONCAMERA_H
