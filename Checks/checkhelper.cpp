#include "checkhelper.h"

#include <QFile>
#include <QRegularExpression>

QByteArray CheckHelper::getSourceCode(QString& fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray sourceCode = file.readAll();
    file.close();
    return sourceCode;
}

bool CheckHelper::checkCamelCase(const QString& text)
{
    QRegularExpression regex("^[a-z][a-z0-9]*([A-Z][a-z0-9]+)*$");
    return regex.match(text).hasMatch();
}

int CheckHelper::getLineNumberOfText(const QByteArray& sourceCode, const QString& text)
{
    int indexOfSlot = sourceCode.indexOf(text);
    QByteArray previousCode = sourceCode.left(indexOfSlot);
    int crCount = previousCode.count('\r');
    int lfCount = previousCode.count('\n');
    int linesCount = qMax(crCount, lfCount) + 1;
    return linesCount;
}

QList<int> CheckHelper::getLinesNumbersOfText(const QByteArray& sourceCode, const QString& text)
{
    QList<int> result;
    int indexOfText = sourceCode.indexOf(text);
    while (indexOfText >= 0)
    {
        QByteArray previousCode = sourceCode.left(indexOfText);
        int crCount = previousCode.count('\r');
        int lfCount = previousCode.count('\n');
        int linesCount = qMax(crCount, lfCount) + 1;
        result.append(linesCount);
        indexOfText = sourceCode.indexOf(text, indexOfText + 1);
    }
    return result;
}

QString CheckHelper::getFunctionNameByDefinition(QString definition)
{
    int indexOfSpace = definition.indexOf(' ');
    int indexOfBracet = definition.indexOf('(');
    int slotNameLength = indexOfBracet - indexOfSpace;
    QString slotName = definition.mid(indexOfSpace, slotNameLength);
    return slotName.trimmed();
}
