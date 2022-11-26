#ifndef EXCEPTIONBADALLOC_H
#define EXCEPTIONBADALLOC_H
#include "exception.h"


class ExceptionBadAlloc : public Exception{
public:

    ExceptionBadAlloc();
    ExceptionBadAlloc(int, char*);

};

#endif // EXCEPTIONBADALLOC_H
