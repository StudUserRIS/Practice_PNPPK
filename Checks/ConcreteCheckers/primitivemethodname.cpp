#include "primitivemethodname.h"

#include "Checks/checkhelper.h"
#include "toobigmethodchecker.h"

constexpr int kMethodLengthName = 4;

QList<CheckResult> PrimitiveMethodName::check(QString fileName)
{
    QList<CheckResult> results;
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);

    TooBigMethodChecker methodChecker;

    auto methods = methodChecker.findMethods(sourceCode);

    if (fileName.endsWith("cpp") && !methods.isEmpty())
    {
        foreach (const TooBigMethodChecker::MethodInfo& method, methods)
        {
            if (method.name.size() < kMethodLengthName)
            {
                results.append({QString("Слишком короткое имя метода: метод %1, %2 символов")
                                    .arg(method.name)
                                    .arg(method.name.size()),
                                fileName,
                                {method.lineStart}});
            }
        }
    }
    return results;
}
