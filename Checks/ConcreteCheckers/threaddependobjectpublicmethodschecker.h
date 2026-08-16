#ifndef THREADDEPENDOBJECTPUBLICMETHODSCHECKER_H
#define THREADDEPENDOBJECTPUBLICMETHODSCHECKER_H

#include "Checks/icheck.h"

class ThreadDependObjectPublicMethodsChecker : public ICheck
{
public:
    ThreadDependObjectPublicMethodsChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // THREADDEPENDOBJECTPUBLICMETHODSCHECKER_H
