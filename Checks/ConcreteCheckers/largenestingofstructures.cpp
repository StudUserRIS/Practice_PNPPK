#include "largenestingofstructures.h"

#include <Checks/checkhelper.h>
#include <QDebug>

constexpr int kMaxNestingCount = 3;

QList<CheckResult> LargeNestingOfStructures::check(QString fileName)
{
    QList<CheckResult> results = {};

    if (fileName.endsWith(".cpp"))
    {
        QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
        TooBigMethodChecker methodChecker;

        int currentLine = 1;
        start = 0;
        end = 0;
        braceLevel = 0;      // Вычитаем скобку метода
        falseBraceLevel = 0; // Скобки не относятся к операторам и методам
        allBraceLevel = 0;   // Все фигурные скобки

        for (int i = 0; i < sourceCode.size(); i++)
        {
            char current = sourceCode.at(i);
            char befor = (i - 1 >= 0) ? sourceCode.at(i - 1) : '\0';
            char befor2 = (i - 2 >= 0) ? sourceCode.at(i - 2) : '\0';
            char next = (i + 1 < sourceCode.size()) ? sourceCode.at(i + 1) : '\0';

            // Обработка перевода строки
            if (current == '\n')
            {
                currentLine++;
                if (methodChecker.inLineComment)
                    methodChecker.inLineComment = false;
                continue;
            }

            // Проверка на вхождение в специальные области -------------------------------------------
            if (methodChecker.checkSpesialSpace(current, next, befor, befor2))
            {
                i = i + methodChecker.plusI;
                continue;
            }

            // ---------------------------------------------------------------------------------------
            // Проверка фигурных скобок вне специальных областей
            if (!methodChecker.inString && !methodChecker.inChar && !methodChecker.inComment &&
                !methodChecker.inLineComment && methodChecker.inRoundBracket == 0)
            {
                findBrace(sourceCode, current, i, fileName, currentLine, results);
            }
        }
    }

    return results;
}

void LargeNestingOfStructures::findBrace(QByteArray sourceCode, char current, int index, QString fileName,
                                         int currentLine, QList<CheckResult>& results)
{
    bool blocHasKey = false;

    if (current == '{')
    {
        allBraceLevel++;
        end = index;
        blocHasKey = blocHasKeywords(sourceCode, start, end);

        start = index;
        if (allBraceLevel == 1)
            return;

        if (allBraceLevel != 1 && blocHasKey)
        {
            braceLevel++;
            if (braceLevel > kMaxNestingCount)
                results.append(
                    {QString("Большая вложенность конструкций: уровень %1").arg(braceLevel), fileName, {currentLine}});
            return;
        }

        if (!blocHasKey)
        {
            falseBraceLevel++;
            return;
        }
    }
    else if (current == '}')
    {
        allBraceLevel--;
        start = index;
        if (allBraceLevel != 0 && falseBraceLevel == 0)
            braceLevel--;
        if (falseBraceLevel > 0)
            falseBraceLevel--;
    }
}

bool LargeNestingOfStructures::blocHasKeywords(const QByteArray& content, int start, int end)
{
    if (start >= end || start < 0 || end >= content.size())
    {
        return false;
    }

    QByteArray bloc = content.mid(start, end - start + 1);
    for (const QByteArray& keyword : openKeywords)
    {
        if (bloc.contains(keyword + "(") || bloc.contains(keyword + " ") || bloc.contains(keyword + ";"))
        {
            return true;
        }
    }

    return false;
}
