#ifndef EXCEPTIONEMPTY_H
#define EXCEPTIONEMPTY_H
#include "exception.h"


class ExceptionEmpty : public Exception{
public:

    ExceptionEmpty();
    ExceptionEmpty(int, char*);

};

#endif // EXCEPTIONEMPTY_H
