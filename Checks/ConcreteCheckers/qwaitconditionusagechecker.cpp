#include "qwaitconditionusagechecker.h"
#include <Checks/checkhelper.h>

QList<CheckResult> QWaitConditionUsageChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;
    
    if (sourceCode.contains("QWaitCondition"))
    {
        QList<int> lines = CheckHelper::getLinesNumbersOfText(sourceCode, "QWaitCondition");
        for (int line : lines)
        {
            results.append({"Обнаружено использование QWaitCondition", fileName, {line}});
        }
    }
    return results;
}
