#include "exceptionempty.h"

ExceptionEmpty::ExceptionEmpty() {
    this -> code = 10;
    strcpy(this -> msg, "Empty Error");
}

ExceptionEmpty::ExceptionEmpty(int code, char* msg) : Exception(code, msg) {}
