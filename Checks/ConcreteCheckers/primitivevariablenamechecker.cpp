#include "primitivevariablenamechecker.h"
#include <Checks/checkhelper.h>
#include <QRegularExpression>

QList<CheckResult> PrimitiveVariableNameChecker::check(QString fileName)
{
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;

    if (fileName.endsWith(".cpp"))
    {
        checkLocalVariables(sourceCode, fileName, results);
    }
    else if (fileName.endsWith(".h"))
    {
        checkClassFields(sourceCode, fileName, results);
    }

    return results;
}

void PrimitiveVariableNameChecker::checkLocalVariables(const QByteArray& sourceCode, const QString& fileName,
                                                       QList<CheckResult>& results)
{
    QRegularExpression varRegex("\\b([A-Za-z_][A-Za-z0-9_:]*(?:\\s*<[^>]*>)?)\\s+(?:\\*\\s*|&\\s*)?([A-Za-z_][A-Za-z0-9_]*)\\s*[;=]");
    QRegularExpressionMatchIterator matches = varRegex.globalMatch(sourceCode);
    while (matches.hasNext())
    {
        QRegularExpressionMatch match = matches.next();
        QString varName = match.captured(2);

        // Исключения для стандартных переменных и счетчиков
        if (varName == "ui" || varName == "i" || varName == "j" || varName == "k")
        {
            continue;
        }

        if (varName.length() < 4)
        {
            int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
            results.append({QString("Слишком короткое имя локальной переменной: '%1' (минимум 4)").arg(varName),
                            fileName,
                            {line}});
        }
    }

    QRegularExpression ptrRegex("\\b\\w+\\s*\\*\\s*(\\w+)\\s*[;=]");
    QRegularExpressionMatchIterator ptrMatches = ptrRegex.globalMatch(sourceCode);
    while (ptrMatches.hasNext())
    {
        QRegularExpressionMatch match = ptrMatches.next();
        QString varName = match.captured(1);
        if (!varName.startsWith("p"))
        {
            int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
            results.append(
                {QString("Имя указателя '%1' должно начинаться с префикса 'p'").arg(varName), fileName, {line}});
        }
    }
}

void PrimitiveVariableNameChecker::checkClassFields(const QByteArray& sourceCode, const QString& fileName,
                                                    QList<CheckResult>& results)
{
    QByteArrayList sections;
    sections << "private:"
             << "protected:";
    foreach (const QByteArray& section, sections)
    {
        int pos = sourceCode.indexOf(section);
        if (pos == -1)
            continue;

        int nextSectionPos = sourceCode.indexOf("public:", pos + section.length());
        if (nextSectionPos == -1)
            nextSectionPos = sourceCode.indexOf("signals:", pos + section.length());
        if (nextSectionPos == -1)
            nextSectionPos = sourceCode.indexOf("};", pos + section.length());
        if (nextSectionPos == -1)
            nextSectionPos = sourceCode.size();

        QByteArray content = sourceCode.mid(pos, nextSectionPos - pos);
        QRegularExpression fieldRegex("\\b(\\w+(?:\\s*\\*|\\s+))(\\w+)\\s*;");
        QRegularExpressionMatchIterator matches = fieldRegex.globalMatch(content);
        while (matches.hasNext())
        {
            QRegularExpressionMatch match = matches.next();
            QString typePart = match.captured(1);
            QString varName = match.captured(2);

            // Исключение для переменной ui (игнорируем все проверки префиксов и длины)
            if (varName == "ui")
            {
                continue;
            }

            if (varName.length() < 6)
            {
                int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
                results.append(
                    {QString("Слишком короткое имя поля класса: '%1' (минимум 6)").arg(varName), fileName, {line}});
            }

            if (!varName.startsWith("_"))
            {
                int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
                results.append(
                    {QString("Имя поля класса '%1' должно начинаться с '_'").arg(varName), fileName, {line}});
            }

            if (typePart.contains("*") && !varName.startsWith("_p"))
            {
                int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
                results.append(
                    {QString("Имя поля-указателя '%1' должно начинаться с '_p'").arg(varName), fileName, {line}});
            }
        }
    }
}
