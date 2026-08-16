#include "checkfactory.h"
#include "Checks/ConcreteCheckers/codeincommentschecker.h"
#include "Checks/ConcreteCheckers/constantsnameschecker.h"
#include "Checks/ConcreteCheckers/constexprforfundamentaltypeschecker.h"
#include "Checks/ConcreteCheckers/includesincenteroffilechecker.h"
#include "Checks/ConcreteCheckers/includesinheaderchecker.h"
#include "Checks/ConcreteCheckers/largenestingofstructures.h"
#include "Checks/ConcreteCheckers/oldstyleconnectchecker.h"
#include "Checks/ConcreteCheckers/primitivemethodname.h"
#include "Checks/ConcreteCheckers/primitivevariablenamechecker.h"
#include "Checks/ConcreteCheckers/publicstatechecker.h"
#include "Checks/ConcreteCheckers/sectionorderchecker.h"
#include "Checks/ConcreteCheckers/signalsslotswithpointerparameterschecker.h"
#include "Checks/ConcreteCheckers/toobigclasschecker.h"
#include "Checks/ConcreteCheckers/toobigmethodchecker.h"
#include "Checks/ConcreteCheckers/wrongsignalsnameschecker.h"
#include "Checks/ConcreteCheckers/wrongslotnamechecker.h"

CheckFactory::CheckFactory() {}

ICheck* CheckFactory::createChecker(CheckType type)
{
    switch (type)
    {
        case CheckType::CodeInComments:
            return new CodeInCommentsChecker();
        case CheckType::VeryBigClass:
            return new TooBigClassChecker();
        case CheckType::OldStyleConnections:
            return new OldStyleConnectChecker();
        case CheckType::SlotNaming:
            return new WrongSlotNameChecker();
        case CheckType::SignalsNaming:
            return new WrongSignalsNamesChecker();
        case CheckType::WrongSectionsOrder:
            return new SectionOrderChecker();
        case CheckType::ConstantsWrongNaming:
            return new ConstantsNamesChecker();
        case CheckType::VeryPrimitiveMethodName:
            return new PrimitiveMethodName();
        case CheckType::VeryLongMethod:
            return new TooBigMethodChecker();
        case CheckType::IncludesInCenterOfFile:
            return new IncludesInCenterOfFileChecker();
        case CheckType::MoreIncludesInHeader:
            return new IncludesInHeaderChecker();
        case CheckType::DifficultIfExpression:
            return new LargeNestingOfStructures();
        case CheckType::ConstexprForFundamentalTypes:
            return new ConstexprForFundamentalTypesChecker();
        case CheckType::PublicState:
            return new PublicStateChecker();
        case CheckType::SignalsSlotsWithPointerParameters:
            return new SignalsSlotsWithPointerParametersChecker();
        case CheckType::VeryPrimitiveVariableName:
            return new PrimitiveVariableNameChecker();
        case CheckType::UserTypeWrongNaming:
        case CheckType::MemcpyPotentionalError:
            return nullptr;
    }
    return nullptr;
}
