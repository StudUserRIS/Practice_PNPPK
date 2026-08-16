#include "profileparser.h"

#include <QFile>
#include <QFileInfo>

ProFileParser::ProFileParser() {}

QStringList ProFileParser::getProjectSourcesFiles(const QString& proFileName)
{
    QFile file(proFileName);
    file.open(QIODevice::ReadOnly);

    QByteArray data = file.readAll();
    QByteArrayList lines = data.split('\n');
    for (auto& line : lines) line = line.simplified();
    QStringList fileNames = parseSection("SOURCES", lines);
    fileNames.append(parseSection("HEADERS", lines));

    QFileInfo info(proFileName);
    QString path = info.path() + "/";

    for (auto& fileName : fileNames) fileName.prepend(path);
    return fileNames;
}

QStringList ProFileParser::parseSection(const QByteArray& sectionName, QByteArrayList& lines)
{
    int sectionStartIndex = 0;

    for (int i = 0; i < lines.count(); i++)
    {
        if (lines.at(i).contains(sectionName))
            sectionStartIndex = i;
    }

    QStringList fileNames;
    for (int i = sectionStartIndex; i < lines.count(); i++)
    {

        if (i != sectionStartIndex && lines.at(i - 1).contains('\\') == false)
            break;
        if (lines.at(i).contains(sectionName))
        {
            QString fileName = lines.at(i).mid(lines.at(i).indexOf("+=") + 2,
                                               lines.at(i).indexOf("\\") - lines.at(i).indexOf("+=") - 2);
            fileName = fileName.simplified();
            if (fileName.isEmpty() == false)
                fileNames.append(fileName);
        }
        else
        {
            QString fileName = lines.at(i);
            fileName.remove("\\");
            fileName = fileName.simplified();
            fileNames.append(fileName);
        }
    }
    return fileNames;
}
