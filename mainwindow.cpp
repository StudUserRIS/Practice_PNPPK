#include "mainwindow.h"
#include "profileparser.h"
#include "reportview.h"
#include "ui_mainwindow.h"

#include "Checks/checksfacade.h"
#include <QCheckBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QMetaMethod>
#include <QTextStream>
#include <QThread>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupOptions();
    _pChecker = new ChecksFacade();
    QThread* pThread = new QThread();
    _pChecker->moveToThread(pThread);
    pThread->start();

    connect(ui->pushButtonStartChecks, &QPushButton::clicked, this, &MainWindow::onStartChecks);
    connect(this, &MainWindow::startChecks, _pChecker, &ChecksFacade::onStartChecks);
    connect(ui->pushButtonChooseProFile, &QPushButton::clicked, this, &MainWindow::onChooseProFile);

    // Подключаем сигнал результатов к нашему слоту сохранения в файл
    _pReportView = new ReportView();
    connect(_pChecker, SIGNAL(showResults(QList<CheckResult>)), _pReportView, SLOT(onShowErrors(QList<CheckResult>)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onStartChecks()
{
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Внимание!", "Не выбран *.pro файл");
        return;
    }
    QList<CheckType> checks;
    for (int i = 0; i < ui->verticalLayout->count(); i++)
    {
        QCheckBox* checkBox = dynamic_cast<QCheckBox*>(ui->verticalLayout->itemAt(i)->widget());
        if (checkBox && checkBox->isChecked())
            checks.append(kCheckList.key(checkBox->text()));
    }

    emit startChecks(checks, ProFileParser::getProjectSourcesFiles(ui->lineEdit->text()));
}

void MainWindow::onChooseProFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите *.pro файл проекта", "", "*.pro");
    if (fileName.isEmpty())
        return;
    ui->lineEdit->setText(fileName);
}

void MainWindow::onSaveResultsToFile(QList<CheckResult> results)
{
    QString proPath = ui->lineEdit->text();
    if (proPath.isEmpty())
        return;

    QFileInfo proFileInfo(proPath);
    QString reportPath = proFileInfo.absolutePath() + "/codeCheckResults.txt";
    QFile reportFile(reportPath);

    if (reportFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&reportFile);
        out.setCodec("UTF-8");

        out << "CodeChecker Results for project: " << proFileInfo.fileName() << "\n";
        out << "Total issues found: " << results.size() << "\n";
        out << "--------------------------------------------------\n\n";

        for (int i = 0; i < results.size(); ++i)
        {
            const CheckResult& result = results.at(i);

            QString linesStr;
            if (result.lines.isEmpty())
            {
                linesStr = "N/A";
            }
            else
            {
                for (int j = 0; j < result.lines.size(); ++j)
                {
                    if (j > 0)
                        linesStr += ", ";
                    linesStr += QString::number(result.lines.at(j));
                }
            }

            out << "[" << QFileInfo(result.fileName).fileName() << ":" << linesStr << "] " << result.readableInfo
                << "\n";
        }

        reportFile.close();
        qDebug() << "GUI Report generated:" << reportPath;
    }
}

void MainWindow::setupOptions()
{
    foreach (const QString& string, kCheckList)
        ui->verticalLayout->addWidget(new QCheckBox(string, this));
    for (int i = 0; i < ui->verticalLayout->count(); i++)
    {
        QCheckBox* checkBox = dynamic_cast<QCheckBox*>(ui->verticalLayout->itemAt(i)->widget());
        if (checkBox)
            checkBox->setChecked(true);
    }
}
