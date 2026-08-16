#ifndef ICHECK_H
#define ICHECK_H

#include <QList>
#include <QString>

struct CheckResult
{
    QString readableInfo;
    QString fileName;
    QList<int> lines;
};

class ICheck
{
public:
    ICheck();
    virtual ~ICheck() = default;
    virtual QList<CheckResult> check(QString fileName) = 0;
};

#endif // ICHECK_H
