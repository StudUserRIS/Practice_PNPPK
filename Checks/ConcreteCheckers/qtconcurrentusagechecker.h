#ifndef QTCONCURRENTUSAGECHECKER_H
#define QTCONCURRENTUSAGECHECKER_H

#include "Checks/icheck.h"

class QtConcurrentUsageChecker : public ICheck
{
public:
    QtConcurrentUsageChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // QTCONCURRENTUSAGECHECKER_H
