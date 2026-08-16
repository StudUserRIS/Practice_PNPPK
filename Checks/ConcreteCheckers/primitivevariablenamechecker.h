#ifndef PRIMITIVEVARIABLENAMECHECKER_H
#define PRIMITIVEVARIABLENAMECHECKER_H

#include <Checks/icheck.h>

class PrimitiveVariableNameChecker : public ICheck
{
public:
    PrimitiveVariableNameChecker() = default;
    QList<CheckResult> check(QString fileName) override;

private:
    void checkLocalVariables(const QByteArray& sourceCode, const QString& fileName, QList<CheckResult>& results);
    void checkClassFields(const QByteArray& sourceCode, const QString& fileName, QList<CheckResult>& results);
};

#endif // PRIMITIVEVARIABLENAMECHECKER_H
