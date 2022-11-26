#include "exceptionfileload.h"

ExceptionFileLoad::ExceptionFileLoad() {
    this -> code = 3;
    strcpy(this -> msg, "File load Error");
}

ExceptionFileLoad::ExceptionFileLoad(int code, char* msg) : ExceptionFile(code, msg) {}
