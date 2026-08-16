#include "publicstatechecker.h"
#include <Checks/checkhelper.h>
#include <QRegularExpression>

QList<CheckResult> PublicStateChecker::check(QString fileName)
{
    if (!fileName.endsWith(".h"))
        return {};

    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;

    int publicPos = sourceCode.indexOf("public:");
    while (publicPos != -1)
    {
        int nextSectionPos = sourceCode.indexOf("protected:", publicPos + 7);
        if (nextSectionPos == -1)
            nextSectionPos = sourceCode.indexOf("private:", publicPos + 7);
        if (nextSectionPos == -1)
            nextSectionPos = sourceCode.indexOf("signals:", publicPos + 7);
        if (nextSectionPos == -1)
            nextSectionPos = sourceCode.indexOf("slots:", publicPos + 7);
        if (nextSectionPos == -1)
            nextSectionPos = sourceCode.size();

        QByteArray publicSection = sourceCode.mid(publicPos, nextSectionPos - publicPos);

        QRegularExpression varRegex("\\b(\\w+)\\s+(\\w+)\\s*;");
        QRegularExpressionMatchIterator matches = varRegex.globalMatch(publicSection);
        while (matches.hasNext())
        {
            QRegularExpressionMatch match = matches.next();
            QString varName = match.captured(2);
            if (!match.captured().contains("(") && !match.captured().contains(")"))
            {
                int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
                results.append({QString("Публичное поле класса: %1. Все поля должны быть приватными.").arg(varName),
                                fileName,
                                {line}});
            }
        }

        publicPos = sourceCode.indexOf("public:", nextSectionPos);
    }

    return results;
}
