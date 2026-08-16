#ifndef CHECKSFACADE_H
#define CHECKSFACADE_H

#include "Checks/checkdefines.h"
#include "Checks/icheck.h"
#include <QObject>

class ChecksFacade : public QObject
{
    Q_OBJECT
public:
    explicit ChecksFacade(QObject* parent = nullptr);

    QList<CheckResult> runChecks(QList<CheckType> checks, QStringList fileNames);

public slots:
    void onStartChecks(QList<CheckType> checks, QStringList fileNames);

signals:
    void showResults(QList<CheckResult> errors);
};

#endif // CHECKSFACADE_H
