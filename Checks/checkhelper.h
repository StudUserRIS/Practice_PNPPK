#ifndef CHECKHELPER_H
#define CHECKHELPER_H

#include <QList>

class CheckHelper
{
public:
    CheckHelper() = delete;
    static QByteArray getSourceCode(QString& fileName);
    static bool checkCamelCase(const QString& text);
    static int getLineNumberOfText(const QByteArray& sourceCode, const QString& text);
    static QList<int> getLinesNumbersOfText(const QByteArray& sourceCode, const QString& text);
    static QString getFunctionNameByDefinition(QString definition);
};

#endif // CHECKHELPER_H
