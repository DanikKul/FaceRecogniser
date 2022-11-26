#ifndef EXCEPTIONFILE_H
#define EXCEPTIONFILE_H
#include "exception.h"


class ExceptionFile : public Exception{
public:

    ExceptionFile();
    ExceptionFile(int, char*);

};

#endif // EXCEPTIONFILE_H
