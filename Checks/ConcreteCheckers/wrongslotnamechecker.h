#ifndef WRONGSLOTNAMECHECKER_H
#define WRONGSLOTNAMECHECKER_H

#include "Checks/icheck.h"

class WrongSlotNameChecker : public ICheck
{
public:
    WrongSlotNameChecker() = default;
    QList<CheckResult> check(QString fileName);

private:
    QStringList findQtSlots(const QByteArray& code);
};

#endif // WRONGSLOTNAMECHECKER_H
