#include "wrongslotnamechecker.h"

#include <QDebug>
#include <QRegularExpression>
#include <QtGlobal>

#include <Checks/checkhelper.h>

QList<CheckResult> WrongSlotNameChecker::check(QString fileName)
{
    if (fileName.endsWith("cpp"))
        return {};

    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    auto slotsDefinitions = findQtSlots(sourceCode);

    QList<CheckResult> results;
    for (auto slotDefinition : slotsDefinitions)
    {
        QString slotName = CheckHelper::getFunctionNameByDefinition(slotDefinition);
        if (CheckHelper::checkCamelCase(slotName) == false)
        {
            if (slotDefinition.startsWith("on") == false)
                results.append(
                    {QString("Имя слота начинается не с \"on\" и оформлено не по camelCase: %1").arg(slotDefinition),
                     fileName, CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
            else
                results.append({QString("Имя слота оформлено не по camelCase: %1").arg(slotDefinition), fileName,
                                CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
        }
        else if (slotName.startsWith("on") == false)
            results.append({QString("Имя слота начинается не с \"on\": %1").arg(slotDefinition), fileName,
                            CheckHelper::getLinesNumbersOfText(sourceCode, slotDefinition)});
    }
    return results;
}

QStringList WrongSlotNameChecker::findQtSlots(const QByteArray& code)
{
    // Регулярное выражение для поиска классических слотов (slots)
    QRegularExpression classicSlotsRegex("(public|private|protected)\\s+slots\\s*:\\s*(.*?)(?=\\bpublic\\b|"
                                         "\\bprivate\\b|\\bprotected\\b|\\bQ_OBJECT\\b|\\bsignals\\b|$)",
                                         QRegularExpression::DotMatchesEverythingOption);

    // Регулярное выражение для поиска слотов с использованием Q_SLOTS
    QRegularExpression qSlotsRegex(
        "Q_SLOTS\\s*:\\s*(.*?)(?=\\bpublic\\b|\\bprivate\\b|\\bprotected\\b|\\bQ_OBJECT\\b|$)",
        QRegularExpression::DotMatchesEverythingOption);

    // Регулярное выражение для поиска слотов с аннотацией Q_SLOT
    QRegularExpression qSlotAnnotationRegex("Q_SLOT\\s+([^;]+);");

    // Регулярное выражение для поиска слотов с аннотацией Q_INVOKABLE
    QRegularExpression qInvokableRegex("Q_INVOKABLE\\s+([^;]+);");

    // Функция для обработки найденных слотов
    QStringList slotsDefinitions;
    auto processSlots = [&](const QString& slotSection) {
        QStringList slotsText = slotSection.split(';', Qt::SkipEmptyParts);
        for (const QString& slot : slotsText)
        {
            QString trimmedSlot = slot.trimmed();
            if (!trimmedSlot.isEmpty())
                slotsDefinitions.append(trimmedSlot);
        }
    };

    // Поиск классических слотов
    QRegularExpressionMatchIterator classicSlotsIterator = classicSlotsRegex.globalMatch(code);
    if (classicSlotsIterator.hasNext())
    {
        while (classicSlotsIterator.hasNext())
        {
            QRegularExpressionMatch match = classicSlotsIterator.next();
            processSlots(match.captured(2).trimmed());
        }
    }

    // Поиск слотов с использованием Q_SLOTS
    QRegularExpressionMatchIterator qSlotsIterator = qSlotsRegex.globalMatch(code);
    if (qSlotsIterator.hasNext())
    {
        while (qSlotsIterator.hasNext())
        {
            QRegularExpressionMatch match = qSlotsIterator.next();
            processSlots(match.captured(1).trimmed());
        }
    }

    // Поиск слотов с аннотацией Q_SLOT
    QRegularExpressionMatchIterator qSlotAnnotationIterator = qSlotAnnotationRegex.globalMatch(code);
    if (qSlotAnnotationIterator.hasNext())
    {
        while (qSlotAnnotationIterator.hasNext())
        {
            QRegularExpressionMatch match = qSlotAnnotationIterator.next();
            slotsDefinitions.append(match.captured(1).trimmed());
        }
    }

    // Поиск слотов с аннотацией Q_INVOKABLE
    QRegularExpressionMatchIterator qInvokableIterator = qInvokableRegex.globalMatch(code);
    if (qInvokableIterator.hasNext())
    {
        while (qInvokableIterator.hasNext())
        {
            QRegularExpressionMatch match = qInvokableIterator.next();
            slotsDefinitions.append(match.captured(1).trimmed());
        }
    }

    return slotsDefinitions;
}
