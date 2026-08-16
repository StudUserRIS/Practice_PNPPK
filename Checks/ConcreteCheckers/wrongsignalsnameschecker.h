#ifndef WRONGSIGNALSNAMESCHECKER_H
#define WRONGSIGNALSNAMESCHECKER_H

#include "Checks/icheck.h"

class WrongSignalsNamesChecker : public ICheck
{
public:
    WrongSignalsNamesChecker() = default;
    QList<CheckResult> check(QString fileName);

private:
    QStringList findQtSignals(const QByteArray& code);
};

#endif // WRONGSIGNALSNAMESCHECKER_H
