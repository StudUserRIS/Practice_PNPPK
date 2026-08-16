#ifndef USELESSNULLPTRDELETECHECKER_H
#define USELESSNULLPTRDELETECHECKER_H

#include "Checks/icheck.h"

class UselessNullptrDeleteChecker : public ICheck
{
public:
    UselessNullptrDeleteChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // USELESSNULLPTRDELETECHECKER_H
