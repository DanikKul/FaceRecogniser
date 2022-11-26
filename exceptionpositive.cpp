#include "exceptionpositive.h"

ExceptionPositive::ExceptionPositive() {
    this -> code = 7;
    strcpy(this -> msg, "File Error");
}

ExceptionPositive::ExceptionPositive(int code, char* msg) : Exception(code, msg) {}
