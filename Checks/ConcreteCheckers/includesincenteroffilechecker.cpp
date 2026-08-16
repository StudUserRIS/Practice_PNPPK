#include "includesincenteroffilechecker.h"

#include <Checks/checkhelper.h>
#include <QDebug>

QList<CheckResult> IncludesInCenterOfFileChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);

    QList<CheckResult> results = {};
    bool flag = true;
    int currentLine = 1;
    int foundPos = -1;
    int posInAllFile = 0;
    QByteArray fragmentCode;

    for (int i = 0; i < sourceCode.size(); i++)
    {
        char befor = (i - 1 > 0) ? sourceCode.at(i - 1) : '\0';
        char current = sourceCode.at(i);
        char next = (i + 1 < sourceCode.size()) ? sourceCode.at(i + 1) : '\0';
        char next2 = (i + 2 < sourceCode.size()) ? sourceCode.at(i + 2) : '\0';

        if (current == '\n')
        {
            currentLine++;
            if (!isspace(next) && next != '#' && flag)
            {
                flag = false;
                foundPos = i;
                posInAllFile = i;
            }
        }

        if (isspace(current))
            continue;

        if (!flag && current == '#' && next == 'i' && next2 == 'n' && befor == '\n')
        {

            fragmentCode = sourceCode.mid(0, i);
            results.append({QString("Включение в середине файла"), fileName, {currentLine}});
        }
    }
    return results;
}
