#ifndef EXCEPTIONINPUT_H
#define EXCEPTIONINPUT_H
#include "exception.h"


class ExceptionInput : public Exception {
public:

    ExceptionInput();
    ExceptionInput(int, char*);

};

#endif // EXCEPTIONINPUT_H
