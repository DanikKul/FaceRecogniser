#include "exceptionemptymodel.h"

ExceptionEmptyModel::ExceptionEmptyModel() {
    this -> code = 12;
    strcpy(this -> msg, "Empty Model Error");
}

ExceptionEmptyModel::ExceptionEmptyModel(int code, char* msg) : ExceptionEmpty(code, msg) {}
