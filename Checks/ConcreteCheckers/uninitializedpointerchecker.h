#ifndef UNINITIALIZEDPOINTERCHECKER_H
#define UNINITIALIZEDPOINTERCHECKER_H

#include "Checks/icheck.h"

class UninitializedPointerChecker : public ICheck
{
public:
    UninitializedPointerChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // UNINITIALIZEDPOINTERCHECKER_H
