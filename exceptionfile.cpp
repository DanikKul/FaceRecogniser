#include "exceptionfile.h"

ExceptionFile::ExceptionFile() {
    this -> code = 2;
    strcpy(this -> msg, "File Error");
}

ExceptionFile::ExceptionFile(int code, char* msg) : Exception(code, msg) {}
