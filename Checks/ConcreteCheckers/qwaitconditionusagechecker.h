#ifndef QWAITCONDITIONUSAGECHECKER_H
#define QWAITCONDITIONUSAGECHECKER_H

#include "Checks/icheck.h"

class QWaitConditionUsageChecker : public ICheck
{
public:
    QWaitConditionUsageChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // QWAITCONDITIONUSAGECHECKER_H
