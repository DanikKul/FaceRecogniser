#include "exception.h"
#include <iostream>

void Exception::getError() const {
    std::cerr << "Error code " << code << ". " << msg << std::endl;
}

int Exception::getCode() const {
    return this -> code;
}

Exception::Exception() {
    this -> code = 999;
    strcpy(this -> msg, "Unknown Error");
}

Exception::Exception(int code, char* msg) {
    this -> code = code;
    strcpy(this -> msg, msg);
}
