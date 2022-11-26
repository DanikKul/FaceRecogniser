#include "exceptionfilewrite.h"

ExceptionFileWrite::ExceptionFileWrite() {
    this -> code = 4;
    strcpy(this -> msg, "File write Error");
}

ExceptionFileWrite::ExceptionFileWrite(int code, char* msg) : ExceptionFile(code, msg) {}
