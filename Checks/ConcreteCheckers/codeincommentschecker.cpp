#include "codeincommentschecker.h"
#include "Checks/keywords.h"

#include <Checks/checkhelper.h>
#include <QByteArray>
#include <QDebug>
#include <QList>
#include <QRegularExpression>
#include <QSet>

QList<CheckResult> CodeInCommentsChecker::check(QString fileName)
{
    _sourceCode = CheckHelper::getSourceCode(fileName);
    QByteArrayList commentedCodeFragments = findCommentedCode();

    QList<CheckResult> result;
    for (int i = 0; i < commentedCodeFragments.size(); ++i)
    {
        const QByteArray& codeFragment = commentedCodeFragments.at(i);
        result.append({QString("Закомментированный код : %1").arg(QString(codeFragment)), fileName,
                       CheckHelper::getLinesNumbersOfText(_sourceCode, codeFragment)});
    }

    return result;
}

QByteArrayList CodeInCommentsChecker::findCommentedCode()
{
    QByteArrayList commentedCodeBlocks;

    // Регулярные выражения без использования raw strings (R"(...)") для совместимости
    QRegularExpression singleLineCommentPattern("\\/\\/.*");
    QRegularExpression multiLineCommentPattern("\\/\\*[\\s\\S]*?\\*\\/");

    // Поиск однострочных комментариев
    QRegularExpressionMatchIterator singleLineMatches = singleLineCommentPattern.globalMatch(_sourceCode);
    while (singleLineMatches.hasNext())
    {
        QRegularExpressionMatch match = singleLineMatches.next();
        QByteArray comment = match.captured().toUtf8();
        if (containsCode(comment))
        {
            commentedCodeBlocks.append(comment);
        }
    }

    // Поиск многострочных комментариев
    QRegularExpressionMatchIterator multiLineMatches = multiLineCommentPattern.globalMatch(_sourceCode);
    while (multiLineMatches.hasNext())
    {
        QRegularExpressionMatch match = multiLineMatches.next();
        QByteArray comment = match.captured().toUtf8();
        if (containsCode(comment))
        {
            commentedCodeBlocks.append(comment);
        }
    }

    return commentedCodeBlocks;
}

bool CodeInCommentsChecker::containsCode(const QByteArray& comment)
{
    QByteArray cleanedComment = comment.trimmed();
    if (cleanedComment.startsWith("//"))
        cleanedComment = cleanedComment.mid(2).trimmed();
    else if (cleanedComment.startsWith("/*"))
        cleanedComment = cleanedComment.mid(2, cleanedComment.length() - 4).trimmed();

    // Разделяем комментарий на слова
    QList<QByteArray> words = cleanedComment.split(' ');
    QSet<QByteArray> keywords = kKeywords;

    for (int i = 0; i < words.size(); ++i)
    {
        const QByteArray& word = words.at(i);
        foreach (const QByteArray& keyword, keywords)
        {
            if (word.contains(keyword))
                return true; // Найдено ключевое слово
        }
    }

    return false; // Код не обнаружен
}
