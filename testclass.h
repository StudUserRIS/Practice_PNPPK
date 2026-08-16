#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>

class TestClass : public QObject
{
    Q_OBJECT
public:
    TestClass() = delete;

signals:
    void onInTyPasdf();

private:
    void startTest();
};

#endif // TESTCLASS_H
