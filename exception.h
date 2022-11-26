#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>


class Exception {

protected:

    int code;
    char msg[80];

public:

    Exception();
    Exception(int, char*);

    void getError() const;
    int getCode() const;

};

#endif // EXCEPTION_H
