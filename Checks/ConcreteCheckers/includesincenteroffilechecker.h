#ifndef INCLUDESINCENTEROFFILECHECKER_H
#define INCLUDESINCENTEROFFILECHECKER_H

#include "Checks/icheck.h"

class IncludesInCenterOfFileChecker : public ICheck
{
public:
    IncludesInCenterOfFileChecker() = default;
    QList<CheckResult> check(QString fileName);
};

#endif // INCLUDESINCENTEROFFILECHECKER_H
