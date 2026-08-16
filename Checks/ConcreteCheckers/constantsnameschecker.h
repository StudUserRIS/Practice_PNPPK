#ifndef CONSTANTSNAMESCHECKER_H
#define CONSTANTSNAMESCHECKER_H

#include <Checks/icheck.h>

class ConstantsNamesChecker : public ICheck
{
public:
    ConstantsNamesChecker() = default;
    QList<CheckResult> check(QString fileName);

private:
    QList<QPair<QString, QString>> findConstants(const QByteArray& code);
};

#endif // CONSTANTSNAMESCHECKER_H
