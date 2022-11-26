#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "stringconv.h"


class Algorithm
{
public:
    Algorithm();
    virtual bool isEmpty() = 0;
    virtual void load(StringConv) = 0;
};

#endif // ALGORITHM_H
