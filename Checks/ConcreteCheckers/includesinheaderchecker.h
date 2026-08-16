#ifndef INCLUDESINHEADERCHECKER_H
#define INCLUDESINHEADERCHECKER_H

#include <Checks/icheck.h>

class IncludesInHeaderChecker : public ICheck
{
public:
    IncludesInHeaderChecker() = default;
    QList<CheckResult> check(QString fileName);
};

#endif // INCLUDESINHEADERCHECKER_H
