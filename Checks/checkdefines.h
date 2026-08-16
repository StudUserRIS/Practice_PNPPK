#ifndef CHECKDEFINES_H
#define CHECKDEFINES_H
#include <QMap>

enum class CheckType
{
    CodeInComments,                    //Сделано
    UserTypeWrongNaming,               //Не сделано
    ConstantsWrongNaming,              //Сделано
    MemcpyPotentionalError,            //???
    VeryPrimitiveVariableName,         //Сделано
    VeryPrimitiveMethodName,           //Сделано
    WrongSectionsOrder,                //Сделано
    IncludesInCenterOfFile,            //Сделано
    ConstexprForFundamentalTypes,      //Сделано
    SignalsSlotsWithPointerParameters, //Сделано
    MoreIncludesInHeader,              //Сделано
    SlotNaming,                        //Сделано
    SignalsNaming,                     //Сделано
    DifficultIfExpression,             //Сделано
    VeryBigClass,                      //Сделано
    VeryLongMethod,                    //Сделано
    OldStyleConnections,               //Сделано
    PublicState,                       //Сделано
    UninitializedPointer,              //
    UselessNullptrDelete,              //
    QWaitConditionUsage,               //
    QtConcurrentUsage,                 //
    DirectConnectionUsage,             //
    ThreadDependObjectPublicMethods    //
};

const QMap<CheckType, QString> kCheckList = {
    {CheckType::CodeInComments, "Закомментированный код"},
    {CheckType::UserTypeWrongNaming, "Именование пользовательских типов"},
    {CheckType::ConstantsWrongNaming, "Именование констант"},
    {CheckType::MemcpyPotentionalError, "Потенциальные ошибки при работе с memcpy"},
    {CheckType::VeryPrimitiveVariableName, "Слишком короткие имена переменных"},
    {CheckType::VeryPrimitiveMethodName, "Слишком короткие имена методов"},
    {CheckType::WrongSectionsOrder, "Неверный порядок секций класса"},
    {CheckType::IncludesInCenterOfFile, "Включения в центре файла"},
    {CheckType::ConstexprForFundamentalTypes, "Использование constexpr вместо const для фундаментальных типов"},
    {CheckType::SignalsSlotsWithPointerParameters, "Сигналы/слоты, передающие/принимающие указатели/ссылки"},
    {CheckType::MoreIncludesInHeader, "Черезмерное количество включений в заголовочном файле"},
    {CheckType::SlotNaming, "Именование слотов"},
    {CheckType::DifficultIfExpression, "Большая вложенность конструкций"},
    {CheckType::VeryBigClass, "Очень большой класс"},
    {CheckType::VeryLongMethod, "Очень длинный метод"},
    {CheckType::OldStyleConnections, "Старый стиль конектов"},
    {CheckType::SignalsNaming, "Именование сигналов"},
    {CheckType::PublicState, "Публичные поля класса"},
    {CheckType::UninitializedPointer, "Неинициализированный указатель"},
    {CheckType::UselessNullptrDelete, "Бесполезная проверка на nullptr перед delete"},
    {CheckType::QWaitConditionUsage, "Использование QWaitCondition"},
    {CheckType::QtConcurrentUsage, "Использование QtConcurrent"},
    {CheckType::DirectConnectionUsage, "Использование Qt::DirectConnection (или Qt::ConnectionType::DirectConnection)"},
    {CheckType::ThreadDependObjectPublicMethods, "Публичный метод у наследника ThreadDependObject"}
};
#endif // CHECKDEFINES_H
