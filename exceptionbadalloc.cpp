#include "exceptionbadalloc.h"

ExceptionBadAlloc::ExceptionBadAlloc() {
    this -> code = 11;
    strcpy(this -> msg, "Bad Allocation Error");
}

ExceptionBadAlloc::ExceptionBadAlloc(int code, char* msg) : Exception(code, msg) {}

