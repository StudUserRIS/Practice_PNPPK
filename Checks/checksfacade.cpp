#include "checksfacade.h"
#include "Checks/icheck.h"
#include "checkfactory.h"
#include <QDebug>

ChecksFacade::ChecksFacade(QObject* parent) : QObject{parent} {}

QList<CheckResult> ChecksFacade::runChecks(QList<CheckType> checks, QStringList fileNames)
{
    QList<ICheck*> checkersList;
    for (auto checkType : checks)
    {
        ICheck* checker = CheckFactory::createChecker(checkType);
        if (checker != nullptr)
        {
            checkersList.append(checker);
        }
    }

    QList<CheckResult> results;
    for (auto& fileName : fileNames)
    {
        for (auto checker : checkersList)
        {
            results.append(checker->check(fileName));
        }
    }

    // Очистка памяти от созданных чекеров
    for (auto checker : checkersList)
    {
        delete checker;
    }

    return results;
}

void ChecksFacade::onStartChecks(QList<CheckType> checks, QStringList fileNames)
{
    QList<CheckResult> results = runChecks(checks, fileNames);
    for (auto& result : results) qDebug() << result.fileName << result.lines << result.readableInfo;
    emit showResults(results);
}
