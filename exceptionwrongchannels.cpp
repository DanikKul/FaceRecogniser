#include "exceptionwrongchannels.h"

ExceptionWrongChannels::ExceptionWrongChannels() {
    this -> code = 6;
    strcpy(this -> msg, "File Error");
}

ExceptionWrongChannels::ExceptionWrongChannels(int code, char* msg) : Exception(code, msg) {}
