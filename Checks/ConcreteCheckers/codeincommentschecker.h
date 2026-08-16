#ifndef CODEINCOMMENTSCHECKER_H
#define CODEINCOMMENTSCHECKER_H

#include "Checks/icheck.h"
#include <QByteArrayList>

class CodeInCommentsChecker : public ICheck
{
public:
    CodeInCommentsChecker() = default;
    virtual ~CodeInCommentsChecker() override = default;
    QList<CheckResult> check(QString fileName) override;

private:
    QByteArray _sourceCode;
    bool containsCode(const QByteArray& comment);
    QByteArrayList findCommentedCode();
};

#endif // CODEINCOMMENTSCHECKER_H
