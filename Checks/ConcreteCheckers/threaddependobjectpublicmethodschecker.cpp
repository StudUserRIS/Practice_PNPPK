#include "threaddependobjectpublicmethodschecker.h"
#include <Checks/checkhelper.h>
#include <QRegularExpression>

QList<CheckResult> ThreadDependObjectPublicMethodsChecker::check(QString fileName)
{
    if (!fileName.endsWith(".h")) 
    {
        return {};
    }
    
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);
    QList<CheckResult> results;
    
    // Check if the class inherits from ThreadDependObject
    if (!sourceCode.contains("public ThreadDependObject")) 
    {
        return results;
    }

    int publicPos = sourceCode.indexOf("public:");
    while (publicPos != -1)
    {
        int nextSectionPos = sourceCode.indexOf("protected:", publicPos + 7);
        if (nextSectionPos == -1)
        {
            nextSectionPos = sourceCode.indexOf("private:", publicPos + 7);
        }
        if (nextSectionPos == -1)
        {
            nextSectionPos = sourceCode.indexOf("signals:", publicPos + 7);
        }
        if (nextSectionPos == -1)
        {
            nextSectionPos = sourceCode.indexOf("slots:", publicPos + 7);
        }
        if (nextSectionPos == -1)
        {
            nextSectionPos = sourceCode.size();
        }

        QByteArray publicSection = sourceCode.mid(publicPos, nextSectionPos - publicPos);
        
        // Find any method signature that is not a constructor/destructor (presence of return type)
        QRegularExpression methodRegex("\\b([A-Za-z_][A-Za-z0-9_:]*)\\s+([A-Za-z_][A-Za-z0-9_]*)\\s*\\(");
        QRegularExpressionMatchIterator matches = methodRegex.globalMatch(publicSection);
        
        while (matches.hasNext())
        {
            QRegularExpressionMatch match = matches.next();
            QString methodName = match.captured(2);
            
            // If it is not a macro or a reserved word
            if (methodName != "override" && methodName != "final") 
            {
                int line = CheckHelper::getLineNumberOfText(sourceCode, match.captured());
                results.append({QString("Публичный метод '%1' в наследнике ThreadDependObject").arg(methodName), 
                                fileName, {line}});
            }
        }
        
        publicPos = sourceCode.indexOf("public:", nextSectionPos);
    }
    return results;
}
