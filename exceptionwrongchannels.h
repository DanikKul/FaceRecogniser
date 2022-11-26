#ifndef EXCEPTIONWRONGCHANNELS_H
#define EXCEPTIONWRONGCHANNELS_H
#include "exception.h"


class ExceptionWrongChannels : public Exception{
public:

    ExceptionWrongChannels();
    ExceptionWrongChannels(int, char*);

};

#endif // EXCEPTIONWRONGCHANNELS_H
