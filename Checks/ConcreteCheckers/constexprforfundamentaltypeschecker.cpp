#include "constexprforfundamentaltypeschecker.h"
#include <Checks/checkhelper.h>
#include <QRegularExpression>

QList<CheckResult> ConstexprForFundamentalTypesChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;

    QString typesPattern = "\\b(bool|int|double|float|char|long|short|unsigned|signed|quint8|quint16|quint32|quint64|"
                           "qint8|qint16|qint32|qint64|qreal)\\b";
    QRegularExpression regex("const\\s+" + typesPattern + "\\s+(\\w+)\\s*=");

    QRegularExpressionMatchIterator matches = regex.globalMatch(sourceCode);
    while (matches.hasNext())
    {
        QRegularExpressionMatch match = matches.next();
        int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
        results.append(
            {QString("Используйте constexpr вместо const для фундаментального типа '%1'").arg(match.captured(1)),
             fileName,
             {line}});
    }

    return results;
}
