#include "exceptioninput.h"

ExceptionInput::ExceptionInput() {
    this -> code = 5;
    strcpy(this -> msg, "File Error");
}

ExceptionInput::ExceptionInput(int code, char* msg) : Exception(code, msg) {}
