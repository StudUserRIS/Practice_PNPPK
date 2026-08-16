#include "uninitializedpointerchecker.h"
#include <Checks/checkhelper.h>
#include <QRegularExpression>

QList<CheckResult> UninitializedPointerChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;
    
    // Ищем указатели, заканчивающиеся точкой с запятой (без инициализации)
    QRegularExpression regex("\\b[A-Za-z_][A-Za-z0-9_:]*(?:\\s*<[^>]*>)?\\s*\\*\\s*[A-Za-z_][A-Za-z0-9_]*\\s*;");
    QRegularExpressionMatchIterator matches = regex.globalMatch(sourceCode);
    
    while (matches.hasNext())
    {
        QRegularExpressionMatch match = matches.next();
        int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
        results.append({QString("Объявление неинициализированного указателя: '%1'").arg(match.captured().trimmed()), 
                        fileName, {line}});
    }
    return results;
}
