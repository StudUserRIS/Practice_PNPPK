#ifndef PROFILEPARSER_H
#define PROFILEPARSER_H

#include <QStringList>

class ProFileParser
{
public:
    ProFileParser();
    static QStringList getProjectSourcesFiles(const QString& proFileName);

private:
    static QStringList parseSection(const QByteArray& sectionName, QByteArrayList& lines);
};

#endif // PROFILEPARSER_H
