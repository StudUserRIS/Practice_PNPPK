#ifndef TOOBIGMATHODCHECKER_H
#define TOOBIGMATHODCHECKER_H

#include "Checks/icheck.h"

class TooBigMethodChecker : public ICheck
{
public:
    TooBigMethodChecker() = default;

    struct MethodInfo
    {
        QString name;
        int lineCount;
        int lineStart;
    };

    QList<CheckResult> check(QString fileName);
    QList<TooBigMethodChecker::MethodInfo> findMethods(const QByteArray& code);
    bool checkSpesialSpace(char current, char next, char befor, char befor2);
    QString findName(QByteArray byteArray);
    QString checkingNameForTrue(int& i, QByteArray byteArray, bool& flag);

    bool inString = false;      // ("...")
    bool inChar = false;        // ('...')
    bool inComment = false;     // (/* ... */)
    bool inLineComment = false; // (//...)
    int inRoundBracket = 0;     // круглые скобки
    int plusI = 0;
};

#endif // TOOBIGMATHODCHECKER_H
