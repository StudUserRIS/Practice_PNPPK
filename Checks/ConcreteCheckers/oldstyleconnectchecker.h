#ifndef OLDSTYLECONNECTCHECKER_H
#define OLDSTYLECONNECTCHECKER_H

#include "Checks/icheck.h"

class OldStyleConnectChecker : public ICheck
{
public:
    OldStyleConnectChecker();
    QList<CheckResult> check(QString fileName);

private:
    QString _fileName;
    QList<CheckResult> checkForQt4Connects(const QByteArray& code);
};

#endif // OLDSTYLECONNECTCHECKER_H
