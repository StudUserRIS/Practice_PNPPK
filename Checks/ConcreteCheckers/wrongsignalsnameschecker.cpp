#include "wrongsignalsnameschecker.h"
#include <Checks/checkhelper.h>
#include <QDebug>
#include <QRegularExpression>

QList<CheckResult> WrongSignalsNamesChecker::check(QString fileName)
{
    if (fileName.endsWith("cpp"))
        return {};

    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    auto signalsDefinitions = findQtSignals(sourceCode);

    QList<CheckResult> results;
    for (auto slotDefinition : signalsDefinitions)
    {
        QString slotName = CheckHelper::getFunctionNameByDefinition(slotDefinition);
        if (CheckHelper::checkCamelCase(slotName) == false)
        {
            if (slotDefinition.startsWith("signal"))
                results.append({QString("Имя сигнала начинается не с \"signal\" и оформлено не по camelCase: %1")
                                    .arg(slotDefinition),
                                fileName, CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
            else if (slotDefinition.startsWith("on"))
                results.append(
                    {QString("Имя сигнала начинается не с \"on\" и оформлено не по camelCase: %1").arg(slotDefinition),
                     fileName, CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
            else
                results.append({QString("Имя сигнала оформлено не по camelCase: %1").arg(slotDefinition), fileName,
                                CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
        }
        else if (slotName.startsWith("signal"))
            results.append({QString("Имя сигнала начинается с \"signal\": %1").arg(slotDefinition), fileName,
                            CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
        else if (slotName.startsWith("on"))
            results.append({QString("Имя сигнала начинается с \"on\": %1").arg(slotDefinition), fileName,
                            CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
    }
    return results;
}

QStringList WrongSignalsNamesChecker::findQtSignals(const QByteArray& code)
{
    // Регулярное выражение для поиска объявлений сигналов
    QRegularExpression signalRegex(
        "(?:signals|Q_SIGNALS)\\s*:\\s*(.*?)(?=\\bpublic\\b|\\bprivate\\b|\\bprotected\\b|\\bQ_OBJECT\\b|\\};|$)",
        QRegularExpression::DotMatchesEverythingOption);

    // Регулярное выражение для поиска отдельных сигналов
    QRegularExpression singleSignalRegex("\\bvoid\\s+\\w+\\s*\\([^)]*\\)\\s*;");
    QStringList resultSignalsDefinitions;
    // Поиск секций сигналов
    QRegularExpressionMatchIterator sectionIterator = signalRegex.globalMatch(code);
    if (sectionIterator.hasNext())
    {
        while (sectionIterator.hasNext())
        {
            QRegularExpressionMatch sectionMatch = sectionIterator.next();
            QString signalSection = sectionMatch.captured(1).trimmed();

            // Поиск отдельных сигналов в секции
            QRegularExpressionMatchIterator signalIterator = singleSignalRegex.globalMatch(signalSection);
            while (signalIterator.hasNext())
            {
                QRegularExpressionMatch signalMatch = signalIterator.next();
                resultSignalsDefinitions << signalMatch.captured(0).trimmed();
            }
        }
    }
    return resultSignalsDefinitions;
}
