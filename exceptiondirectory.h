#ifndef EXCEPTIONDIRECTORY_H
#define EXCEPTIONDIRECTORY_H
#include "exception.h"


class ExceptionDirectory : public Exception{
public:

    ExceptionDirectory();
    ExceptionDirectory(int, char*);

};

#endif // EXCEPTIONDIRECTORY_H
