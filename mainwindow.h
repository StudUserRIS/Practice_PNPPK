#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Checks/checkdefines.h>
#include <Checks/icheck.h>
#include <QMainWindow>
class ReportView;
QT_BEGIN_NAMESPACE

class ChecksFacade;

namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

signals:
    void startChecks(QList<CheckType> checks, QStringList fileNames);

private slots:
    void onStartChecks();
    void onChooseProFile();
    void onSaveResultsToFile(QList<CheckResult> results);

private:
    Ui::MainWindow* ui;
    ChecksFacade* _pChecker = nullptr;
    ReportView* _pReportView = nullptr;

    void setupOptions();
};
#endif // MAINWINDOW_H
