#ifndef SECTIONORDERCHECKER_H
#define SECTIONORDERCHECKER_H

#include <Checks/icheck.h>

class SectionOrderChecker : public ICheck
{
public:
    SectionOrderChecker() = default;
    QList<CheckResult> check(QString fileName);
};

#endif // SECTIONORDERCHECKER_H
