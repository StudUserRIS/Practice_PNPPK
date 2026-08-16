#include "uselessnullptrdeletechecker.h"
#include <Checks/checkhelper.h>
#include <QRegularExpression>

QList<CheckResult> UselessNullptrDeleteChecker::check(QString fileName)
{
    if (!fileName.endsWith(".cpp"))
    {
        return {};
    }
    
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;
    
    // Find if(ptr) delete ptr; or if(ptr != nullptr) delete ptr;
    QRegularExpression regex("if\\s*\\(\\s*([A-Za-z0-9_]+)\\s*(?:!=\\s*(?:nullptr|NULL|0))?\\s*\\)\\s*\\{?\\s*delete\\s*(?:\\[\\s*\\])?\\s+\\1\\s*;");
    QRegularExpressionMatchIterator matches = regex.globalMatch(sourceCode);
    
    while (matches.hasNext())
    {
        QRegularExpressionMatch match = matches.next();
        int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
        results.append({QString("Бесполезная проверка указателя перед delete: '%1'").arg(match.captured(1)), 
                        fileName, {line}});
    }
    return results;
}
