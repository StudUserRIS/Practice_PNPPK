#include "includesinheaderchecker.h"

#include <Checks/checkhelper.h>

constexpr int kHeaderFileMaxIncludeCount = 6;

QList<CheckResult> IncludesInHeaderChecker::check(QString fileName)
{
    if (fileName.endsWith(".h"))
    {
        QByteArray sourceCode = CheckHelper::getSourceCode(fileName);

        int includeCount = sourceCode.count("\n#include");

        if (includeCount > kHeaderFileMaxIncludeCount)
            return {{QString("Черезмерное количество включений в заголовочном файле: %1 включений").arg(includeCount),
                     fileName,
                     {0}}};
    }

    return {};
}
