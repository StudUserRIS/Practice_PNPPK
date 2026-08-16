#include "oldstyleconnectchecker.h"

#include <QDebug>
#include <QRegularExpression>

#include <Checks/checkhelper.h>

OldStyleConnectChecker::OldStyleConnectChecker() {}

QList<CheckResult> OldStyleConnectChecker::check(QString fileName)
{
    if (fileName.endsWith("h"))
        return {};

    _fileName = fileName;
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    return checkForQt4Connects(sourceCode);
}

QList<CheckResult> OldStyleConnectChecker::checkForQt4Connects(const QByteArray& code)
{
    // Регулярное выражение для поиска коннектов в стиле Qt4
    QRegularExpression regex("connect\\s*\\(\\s*([^,]+)\\s*,\\s*SIGNAL\\s*\\(([^)]+)\\)\\s*,\\s*([^,]+)\\s*,"
                             "\\s*SLOT\\s*\\(([^)]+)\\)\\s*\\)");

    // Поиск всех совпадений в коде
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(code);

    if (matchIterator.hasNext() == false)
        return {};

    QList<CheckResult> results;
    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        QByteArray codeBefore = code.left(match.capturedStart());
        int crCount = codeBefore.count("\r");
        int lfCount = codeBefore.count("\n");
        int linesCount = qMax(crCount, lfCount) + 2;
        results.append({QString("Коннект в стиле Qt4: %1").arg(match.capturedTexts().at(0)), _fileName, {linesCount}});
    }
    return results;
}
