#ifndef DIRECTCONNECTIONUSAGECHECKER_H
#define DIRECTCONNECTIONUSAGECHECKER_H

#include "Checks/icheck.h"

class DirectConnectionUsageChecker : public ICheck
{
public:
    DirectConnectionUsageChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // DIRECTCONNECTIONUSAGECHECKER_H
