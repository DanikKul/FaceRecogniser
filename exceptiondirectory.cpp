#include "exceptiondirectory.h"

ExceptionDirectory::ExceptionDirectory() {
    this -> code = 11;
    strcpy(this -> msg, "Bad Allocation Error");
}

ExceptionDirectory::ExceptionDirectory(int code, char* msg) : Exception(code, msg) {}

