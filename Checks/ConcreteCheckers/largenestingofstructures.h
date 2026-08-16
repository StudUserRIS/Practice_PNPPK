#ifndef LARGENESTINGOFSTRUCTURES_H
#define LARGENESTINGOFSTRUCTURES_H

#include "Checks/ConcreteCheckers/toobigmethodchecker.h"
#include <Checks/icheck.h>

class LargeNestingOfStructures : public ICheck
{
public:
    LargeNestingOfStructures() = default;
    QList<CheckResult> check(QString fileName);

private:
    void findBrace(QByteArray sourceCode, char current, int index, QString fileName, int currentLine,
                   QList<CheckResult>& results);
    bool blocHasKeywords(const QByteArray& content, int start, int end);

    int start = 0;
    int end = 0;
    int braceLevel = 0;      // Вычитаем скобку метода
    int falseBraceLevel = 0; // Скобки не относятся к операторам и методам
    int allBraceLevel = 0;   // Все фигурные скобки
    const QList<QByteArray> openKeywords = {"if", "else if", "else", "for",   "while",
                                            "do", "switch",  "try",  "catch", "finally"};
};

#endif // LARGENESTINGOFSTRUCTURES_H
