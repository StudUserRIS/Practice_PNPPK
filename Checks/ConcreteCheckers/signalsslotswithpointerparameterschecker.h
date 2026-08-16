#ifndef SIGNALSSLOTSWITHPOINTERPARAMETERSCHECKER_H
#define SIGNALSSLOTSWITHPOINTERPARAMETERSCHECKER_H

#include <Checks/icheck.h>

class SignalsSlotsWithPointerParametersChecker : public ICheck
{
public:
    SignalsSlotsWithPointerParametersChecker() = default;
    QList<CheckResult> check(QString fileName) override;
};

#endif // SIGNALSSLOTSWITHPOINTERPARAMETERSCHECKER_H
