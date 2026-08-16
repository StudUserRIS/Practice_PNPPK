#include "directconnectionusagechecker.h"
#include <Checks/checkhelper.h>

QList<CheckResult> DirectConnectionUsageChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;
    
    QStringList targets = {"Qt::DirectConnection", "Qt::ConnectionType::DirectConnection"};
    
    for (const QString& target : targets)
    {
        if (sourceCode.contains(target.toUtf8()))
        {
            QList<int> lines = CheckHelper::getLinesNumbersOfText(sourceCode, target);
            for (int line : lines)
            {
                results.append({QString("Обнаружено использование %1").arg(target), fileName, {line}});
            }
        }
    }
    return results;
}
