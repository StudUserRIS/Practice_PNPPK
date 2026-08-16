QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Checks/ConcreteCheckers/codeincommentschecker.cpp \
    Checks/ConcreteCheckers/constantsnameschecker.cpp \
    Checks/ConcreteCheckers/includesincenteroffilechecker.cpp \
    Checks/ConcreteCheckers/includesinheaderchecker.cpp \
    Checks/ConcreteCheckers/largenestingofstructures.cpp \
    Checks/ConcreteCheckers/oldstyleconnectchecker.cpp \
    Checks/ConcreteCheckers/primitivemethodname.cpp \
    Checks/ConcreteCheckers/sectionorderchecker.cpp \
    Checks/ConcreteCheckers/toobigclasschecker.cpp \
    Checks/ConcreteCheckers/toobigmethodchecker.cpp \
    Checks/ConcreteCheckers/wrongsignalsnameschecker.cpp \
    Checks/ConcreteCheckers/wrongslotnamechecker.cpp \
    Checks/ConcreteCheckers/constexprforfundamentaltypeschecker.cpp \
    Checks/ConcreteCheckers/publicstatechecker.cpp \
    Checks/ConcreteCheckers/signalsslotswithpointerparameterschecker.cpp \
    Checks/ConcreteCheckers/primitivevariablenamechecker.cpp \
    Checks/ConcreteCheckers/uninitializedpointerchecker.cpp \
    Checks/ConcreteCheckers/uselessnullptrdeletechecker.cpp \
    Checks/ConcreteCheckers/qwaitconditionusagechecker.cpp \
    Checks/ConcreteCheckers/qtconcurrentusagechecker.cpp \
    Checks/ConcreteCheckers/directconnectionusagechecker.cpp \
    Checks/ConcreteCheckers/threaddependobjectpublicmethodschecker.cpp \
    Checks/checkfactory.cpp \
    Checks/checkhelper.cpp \
    Checks/checksfacade.cpp \
    Checks/icheck.cpp \
    main.cpp \
    mainwindow.cpp \
    profileparser.cpp \
    reportview.cpp \
    testclass.cpp

HEADERS += \
    Checks/ConcreteCheckers/codeincommentschecker.h \
    Checks/ConcreteCheckers/constantsnameschecker.h \
    Checks/ConcreteCheckers/includesincenteroffilechecker.h \
    Checks/ConcreteCheckers/includesinheaderchecker.h \
    Checks/ConcreteCheckers/largenestingofstructures.h \
    Checks/ConcreteCheckers/oldstyleconnectchecker.h \
    Checks/ConcreteCheckers/primitivemethodname.h \
    Checks/ConcreteCheckers/sectionorderchecker.h \
    Checks/ConcreteCheckers/toobigclasschecker.h \
    Checks/ConcreteCheckers/toobigmethodchecker.h \
    Checks/ConcreteCheckers/wrongsignalsnameschecker.h \
    Checks/ConcreteCheckers/wrongslotnamechecker.h \
    Checks/ConcreteCheckers/constexprforfundamentaltypeschecker.h \
    Checks/ConcreteCheckers/publicstatechecker.h \
    Checks/ConcreteCheckers/signalsslotswithpointerparameterschecker.h \
    Checks/ConcreteCheckers/primitivevariablenamechecker.h \
    Checks/ConcreteCheckers/uninitializedpointerchecker.h \
    Checks/ConcreteCheckers/uselessnullptrdeletechecker.h \
    Checks/ConcreteCheckers/qwaitconditionusagechecker.h \
    Checks/ConcreteCheckers/qtconcurrentusagechecker.h \
    Checks/ConcreteCheckers/directconnectionusagechecker.h \
    Checks/ConcreteCheckers/threaddependobjectpublicmethodschecker.h \
    Checks/checkdefines.h \
    Checks/checkfactory.h \
    Checks/checkhelper.h \
    Checks/checksfacade.h \
    Checks/icheck.h \
    Checks/keywords.h \
    mainwindow.h \
    profileparser.h \
    reportview.h \
    testclass.h

FORMS += \
    mainwindow.ui \
    reportview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
