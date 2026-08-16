#include "toobigclasschecker.h"

#include <Checks/checkhelper.h>

constexpr int kSourceCodeFileMaxLineCount = 1000;
constexpr int kHeaderFileMaxLineCount = 300;

QList<CheckResult> TooBigClassChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    int lfCount = sourceCode.count('\n');
    int crCount = sourceCode.count('\r');
    int linesCount = qMax(lfCount, crCount);
    if (fileName.endsWith("h") && linesCount > kHeaderFileMaxLineCount)
        return {{QString("Слишком большой файл. Количество строк: %1").arg(linesCount), fileName, {0}}};
    else if (fileName.endsWith("cpp") && linesCount > kSourceCodeFileMaxLineCount)
        return {{QString("Слишком большой файл. Количество строк: %1").arg(linesCount), fileName, {0}}};
    return {};
}
