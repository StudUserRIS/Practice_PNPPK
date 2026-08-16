#include "signalsslotswithpointerparameterschecker.h"
#include <Checks/checkhelper.h>
#include <QRegularExpression>

QList<CheckResult> SignalsSlotsWithPointerParametersChecker::check(QString fileName)
{
    if (!fileName.endsWith(".h"))
        return {};

    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;

    QByteArrayList sections;
    sections << "signals:"
             << "public slots:"
             << "protected slots:"
             << "private slots:"
             << "slots:";

    foreach (const QByteArray& section, sections)
    {
        int pos = sourceCode.indexOf(section);
        while (pos != -1)
        {
            int nextSectionPos = sourceCode.indexOf("public:", pos + section.length());
            if (nextSectionPos == -1)
                nextSectionPos = sourceCode.indexOf("protected:", pos + section.length());
            if (nextSectionPos == -1)
                nextSectionPos = sourceCode.indexOf("private:", pos + section.length());
            if (nextSectionPos == -1)
                nextSectionPos = sourceCode.indexOf("signals:", pos + section.length());
            if (nextSectionPos == -1)
                nextSectionPos = sourceCode.indexOf("slots:", pos + section.length());
            if (nextSectionPos == -1)
                nextSectionPos = sourceCode.indexOf("};", pos + section.length());
            if (nextSectionPos == -1)
                nextSectionPos = sourceCode.size();

            QByteArray content = sourceCode.mid(pos, nextSectionPos - pos);

            QRegularExpression sigRegex("\\w+\\s+(\\w+)\\s*\\(([^\\)]*)\\)");
            QRegularExpressionMatchIterator matches = sigRegex.globalMatch(content);
            while (matches.hasNext())
            {
                QRegularExpressionMatch match = matches.next();
                QString params = match.captured(2);
                if (params.contains("*") || params.contains("&"))
                {
                    int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
                    results.append(
                        {QString("Сигнал/слот '%1' содержит указатели или ссылки в параметрах").arg(match.captured(1)),
                         fileName,
                         {line}});
                }
            }
            pos = sourceCode.indexOf(section, nextSectionPos);
        }
    }

    return results;
}
