#ifndef CONSTEXPRFORFUNDAMENTALTYPESCHECKER_H
#define CONSTEXPRFORFUNDAMENTALTYPESCHECKER_H

#include <Checks/icheck.h>

class ConstexprForFundamentalTypesChecker : public ICheck
{
public:
    ConstexprForFundamentalTypesChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // CONSTEXPRFORFUNDAMENTALTYPESCHECKER_H
