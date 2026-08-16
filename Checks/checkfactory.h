#ifndef CHECKFACTORY_H
#define CHECKFACTORY_H

#include "checkdefines.h"
#include "icheck.h"

class CheckFactory
{
public:
    CheckFactory();
    static ICheck* createChecker(CheckType type);
};

#endif // CHECKFACTORY_H
