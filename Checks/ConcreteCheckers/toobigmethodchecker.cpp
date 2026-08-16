#include "toobigmethodchecker.h"

#include <QDebug>

#include <Checks/checkhelper.h>

constexpr int kMethodMaxLineCount = 100;

QList<CheckResult> TooBigMethodChecker::check(QString fileName)
{
    QList<CheckResult> results;
    QByteArray sourceCode = CheckHelper::getSourceCode(fileName);

    auto methods = findMethods(sourceCode);

    if (fileName.endsWith("cpp") && !methods.isEmpty())
    {
        foreach (const MethodInfo& method, methods)
        {
            if (method.lineCount > kMethodMaxLineCount)
            {
                results.append(
                    {QString("Слишком длинный метод: метод %1, %2 строк").arg(method.name).arg(method.lineCount),
                     fileName,
                     {method.lineStart}});
            }
        }
    }

    return results;
}

QList<TooBigMethodChecker::MethodInfo> TooBigMethodChecker::findMethods(const QByteArray& code)
{
    QList<MethodInfo> methods;
    int braceLevel = 0;
    int currentLine = 1;
    int methodLine = 0;
    int lineStart = 0;
    int startPosName = 0;
    int endPosName = 0;
    bool inMathod = false;
    QString methodName = "no name";

    for (int i = 0; i < code.size(); i++)
    {
        char current = code.at(i);
        char befor = (i - 1 >= 0) ? code.at(i - 1) : '\0';
        char befor2 = (i - 2 >= 0) ? code.at(i - 2) : '\0';
        char next = (i + 1 < code.size()) ? code.at(i + 1) : '\0';

        // Обработка перевода строки
        if (current == '\n')
        {
            currentLine++;
            if (inLineComment)
                inLineComment = false;
            if (inMathod)
                methodLine++;
            continue;
        }

        // Проверка на вхождение в специальные области -------------------------------------------
        if (checkSpesialSpace(current, next, befor, befor2))
        {
            i = i + plusI;
            continue;
        }

        // ---------------------------------------------------------------------------------------
        // Проверка фигурных скобок вне специальных областей
        if (!inString && !inChar && !inComment && !inLineComment && current == '{')
        {
            braceLevel++;
            if (braceLevel == 1)
            {
                inMathod = true;
                endPosName = i;
                lineStart = currentLine;
            }
        }
        else if (!inString && !inChar && !inComment && !inLineComment && current == '}')
        {
            braceLevel--;

            if (braceLevel == 0)
            {
                inMathod = false;
                // Поиск имени
                startPosName = (endPosName - 200 >= 0) ? endPosName - 200 : 0;
                endPosName = (endPosName - 200 >= 0) ? 200 : endPosName;
                methodName = findName(code.mid(startPosName, endPosName));
                if (methodName == "not method")
                    continue; // Если не встречено скобок с аргументами

                methods.append({methodName, methodLine, lineStart});

                methodLine = 0;
            }
        }
    }

    return methods;
}

// Проверка на вхождение в специальные области (кавычки, комментарии)
bool TooBigMethodChecker::checkSpesialSpace(char current, char next, char befor, char befor2)
{
    if (!inComment && !inLineComment && current == '\"' && !inChar && !inString)
    { // Встретили открывающую "
        inString = true;
        plusI = 0;
        return true;
    }
    else if (!inComment && !inLineComment && current == '\"' && !inChar && inString && befor != '\\')
    { // Встретили обычную закрывающую "
        inString = false;
        plusI = 0;
        return true;
    }
    else if (!inComment && !inLineComment && current == '\"' && !inChar && inString && befor == '\\' && befor2 == '\\')
    { // Встретили ' //" '
        inString = false;
        plusI = 0;
        return true;
    }
    else if (!inComment && !inLineComment && current == '\'' && !inString && !inChar)
    { // Встретили открывающую '
        inChar = true;
        plusI = 0;
        return true;
    }
    else if (!inComment && !inLineComment && current == '\'' && !inString && inChar && befor != '\\')
    { // Встртили обычную закрывающую '
        inChar = false;
        plusI = 0;
        return true;
    }
    else if (!inComment && !inLineComment && current == '\'' && !inString && inChar && befor == '\\' && befor2 == '\\')
    { // Встртили ' //' '
        inChar = false;
        plusI = 0;
        return true;
    }
    else if (!inString && !inChar && !inComment && !inLineComment && current == '/' && next == '*')
    { // Встретили начало многострочного комментария
        inComment = true;
        plusI = 1;
        return true;
    }
    else if (!inString && !inChar && inComment && current == '*' && next == '/')
    { // Встретили конец многострочного комментария */
        inComment = false;
        plusI = 1;
        return true;
    }
    else if (!inString && !inChar && !inComment && !inLineComment && current == '/' && next == '/')
    { // Встретили начало однострочного комментария
        inLineComment = true;
        plusI = 1;
        return true;
    }
    else if (!inString && !inChar && !inComment && !inLineComment && current == '(')
    { // Встретили Открывающую закрывающую скобку
        inRoundBracket++;
        plusI = 0;
        return true;
    }
    else if (!inString && !inChar && !inComment && !inLineComment && current == ')')
    { // Встретили Открывающую закрывающую скобку
        inRoundBracket--;
        plusI = 0;
        return true;
    }
    else
    {
        return false;
    }
}

QString TooBigMethodChecker::findName(QByteArray byteArray)
{
    QString methodName = "name not found__";
    QByteArray nameByteArray = {};
    bool flag = false; // Флаг, разрешающий взятие имени

    int level = -1; // Счётчик обычных скобок

    for (int i = byteArray.size() - 1; i >= 0; i--)
    {
        char currentByte = byteArray.at(i);

        if (isspace(currentByte))
            continue; // Пропускаем пробелы и переносы строк

        if (currentByte == ')')
        {
            if (level == -1)
                level++;
            level++;
        }
        else if (currentByte == '(')
        {
            level--;
            if (level == 0)
            {
                flag = true;
                continue;
            }
        }

        // Проверяем истинность нахождения имени
        if (level == 0 && flag)
        {

            methodName = checkingNameForTrue(i, byteArray, flag);
            return methodName;
        }
    }

    if (level == -1)
        return "not method";

    return methodName;
}

QString TooBigMethodChecker::checkingNameForTrue(int& i, QByteArray byteArray, bool& flag)
{
    int startPos = 0;
    int endPos = i + 1;
    QString methodName = "name not found";

    for (int j = i; j >= 0; j--)
    {
        char current = byteArray.at(j);
        char befor = (j - 1 >= 0) ? byteArray.at(j - 1) : '\0';

        if (isspace(current))
        {
            startPos = j + 1;
            flag = false;
            continue;
        }
        else if ((current == ':' && befor != ':') || current == ',')
        {
            flag = false;
            i = j;
            j = -1;
        }
        else if ((current != ':' || current != ',') && !flag)
        {
            startPos = j + 1;
            methodName = QString::fromUtf8(byteArray.mid(startPos, endPos - startPos));
        }
        else if (current == ':' && befor == ':')
        {
            startPos = j + 1;
            methodName = QString::fromUtf8(byteArray.mid(startPos, endPos - startPos));
            return methodName;
        }
        else if (flag)
        {
            continue;
        }
        else
        { //Если найденное имя оказалось не именем, продолжаем перебор
            startPos = j + 1;
            methodName = QString::fromUtf8(byteArray.mid(startPos, endPos - startPos));
            return methodName;
        }
    }

    return methodName;
}
