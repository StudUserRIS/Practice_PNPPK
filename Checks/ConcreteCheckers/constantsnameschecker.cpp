#include "constantsnameschecker.h"

#include <Checks/checkhelper.h>
#include <QDebug>
#include <QRegularExpression>

QList<CheckResult> ConstantsNamesChecker::check(QString fileName)
{
    auto sourceCode = CheckHelper::getSourceCode(fileName);
    auto constants = findConstants(sourceCode);
    QList<CheckResult> results;
    for (const auto& constant : constants)
    {
        if (CheckHelper::checkCamelCase(constant.first) == false)
        {
            if (constant.first.startsWith("k") == false)
                results.append({QString("Имя константы начинается не с \'k\' и оформлено не по camelCase: %1")
                                    .arg(constant.second),
                                fileName, CheckHelper::getLinesNumbersOfText(sourceCode, constant.second)});
            else
                results.append({QString("Имя константы оформлено не по camelCase: %1").arg(constant.second), fileName,
                                CheckHelper::getLinesNumbersOfText(sourceCode, constant.second)});
        }
        else if (constant.first.startsWith("k") == false)
            results.append({QString("Имя константы начинается не с \'k\': %1").arg(constant.second), fileName,
                            CheckHelper::getLinesNumbersOfText(sourceCode, constant.second)});
    }
    return results;
}

QList<QPair<QString, QString>> ConstantsNamesChecker::findConstants(const QByteArray& code)
{
    // Регулярное выражение для поиска объявлений констант
    QRegularExpression constRegex("\\b(?:const|constexpr)\\s+(?:\\w+\\s+)*(\\w+)\\s*(?:=\\s*[^;]+)?\\s*;");

    QList<QPair<QString, QString>> constantsList;

    // Поиск всех совпадений в коде
    QRegularExpressionMatchIterator matchIterator = constRegex.globalMatch(code);

    if (matchIterator.hasNext())
    {
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            QString constantDefinition = match.captured(0).trimmed();
            QString constantName = match.captured(1).trimmed();
            constantsList.append({constantName, constantDefinition});
        }
    }
    return constantsList;
}
