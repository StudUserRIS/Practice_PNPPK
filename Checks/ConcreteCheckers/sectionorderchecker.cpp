#include "sectionorderchecker.h"
#include <Checks/checkhelper.h>

const QByteArrayList kSectionsOrder = {
    "public:", "public slots:", "signals:", "protected:", "protected slots:", "private slots:", "private:"};

QList<CheckResult> SectionOrderChecker::check(QString fileName)
{
    if (!fileName.endsWith(".h"))
        return {};

    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;

    // 1. Проверка на множественное объявление
    for (const auto& sectionName : kSectionsOrder)
    {
        if (sourceCode.count(sectionName) > 1)
            results.append({QString("Множественное объявление секции класса: %1").arg(QString(sectionName)), fileName,
                            CheckHelper::getLinesNumbersOfText(sourceCode, sectionName)});
    }

    // 2. Проверка последовательности секций
    QList<QPair<QString, int>> foundSections;
    for (const auto& sectionName : kSectionsOrder)
    {
        int index = sourceCode.indexOf(sectionName);
        if (index >= 0)
            foundSections.append({sectionName, index});
    }

    // Сортируем найденные секции по их позиции в файле (используем qSort для совместимости)
    // Ошибка на swapItemsAt - законсервировал - можно доработать
    //for (int i = 0; i < foundSections.size(); ++i) {
    // for (int j = i + 1; j < foundSections.size(); ++j) {
    //if (foundSections[i].second > foundSections[j].second) {
    // foundSections.swapItemsAt(i, j);
    //}
    //}
    //}

    // Проверяем, что порядок соответствует kSectionsOrder
    int lastOrderIndex = -1;
    for (int i = 0; i < foundSections.size(); ++i)
    {
        const QPair<QString, int>& found = foundSections.at(i);
        int currentOrderIndex = kSectionsOrder.indexOf(found.first.toUtf8());
        if (currentOrderIndex < lastOrderIndex)
        {
            int line = CheckHelper::getLineNumberOfText(sourceCode, found.first);
            results.append(
                {QString("Неверный порядок секций: %1 находится после более приватной или специфичной секции")
                     .arg(found.first),
                 fileName,
                 {line}});
        }
        lastOrderIndex = currentOrderIndex;
    }

    return results;
}
