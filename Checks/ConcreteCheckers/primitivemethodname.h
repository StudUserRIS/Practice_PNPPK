#ifndef PRIMITIVEMETHODNAME_H
#define PRIMITIVEMETHODNAME_H

#include "Checks/icheck.h"

class PrimitiveMethodName : public ICheck
{
public:
    PrimitiveMethodName() = default;
    QList<CheckResult> check(QString fileName);
};

#endif // PRIMITIVEMETHODNAME_H
