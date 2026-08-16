#ifndef TOOBIGCLASSCHECKER_H
#define TOOBIGCLASSCHECKER_H

#include "Checks/icheck.h"

class TooBigClassChecker : public ICheck
{
public:
    TooBigClassChecker() = default;
    QList<CheckResult> check(QString fileName);
};

#endif // TOOBIGCLASSCHECKER_H
