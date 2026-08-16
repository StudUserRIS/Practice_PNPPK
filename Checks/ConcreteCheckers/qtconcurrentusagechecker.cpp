#include "qtconcurrentusagechecker.h"
#include <Checks/checkhelper.h>

QList<CheckResult> QtConcurrentUsageChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;
    
    if (sourceCode.contains("QtConcurrent"))
    {
        QList<int> lines = CheckHelper::getLinesNumbersOfText(sourceCode, "QtConcurrent");
        for (int line : lines)
        {
            results.append({"Обнаружено использование QtConcurrent", fileName, {line}});
        }
    }
    return results;
}
