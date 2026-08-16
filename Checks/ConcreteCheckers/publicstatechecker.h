#ifndef PUBLICSTATECHECKER_H
#define PUBLICSTATECHECKER_H

#include <Checks/icheck.h>

class PublicStateChecker : public ICheck
{
public:
    PublicStateChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // PUBLICSTATECHECKER_H
