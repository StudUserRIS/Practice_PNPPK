#include "Checks/checkdefines.h"
#include "Checks/checksfacade.h"
#include "Checks/icheck.h"
#include "mainwindow.h"
#include "profileparser.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

void runCliMode(const QString& proFilePath)
{
    QFileInfo proFileInfo(proFilePath);
    if (!proFileInfo.exists())
    {
        qCritical() << "Error: .pro file does not exist:" << proFilePath;
        return;
    }

    QStringList files = ProFileParser::getProjectSourcesFiles(proFilePath);
    if (files.isEmpty())
    {
        qWarning() << "No source files found in .pro file.";
        return;
    }

    // Собираем все доступные типы проверок из kCheckList
    QList<CheckType> checks = kCheckList.keys();

    // Удаляем MemcpyPotentionalError, если он есть в списке, так как он не требуется
    checks.removeAll(CheckType::MemcpyPotentionalError);

    ChecksFacade facade;
    // Выполняем проверки синхронно
    QList<CheckResult> allResults = facade.runChecks(checks, files);

    // Путь к отчету в той же директории, что и .pro файл
    QString reportPath = proFileInfo.absolutePath() + "/codeCheckResults.txt";
    QFile reportFile(reportPath);

    if (reportFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&reportFile);
        // Устанавливаем кодировку UTF-8 для корректного отображения кириллицы
        out.setCodec("UTF-8");

        out << "CodeChecker Results for project: " << proFileInfo.fileName() << "\n";
        out << "Total issues found: " << allResults.size() << "\n";
        out << "--------------------------------------------------\n\n";

        for (int i = 0; i < allResults.size(); ++i)
        {
            const CheckResult& result = allResults.at(i);

            // Формируем строку с номерами строк
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
        qInfo() << "Report successfully generated:" << reportPath;
    }
    else
    {
        qCritical() << "Failed to open report file for writing:" << reportPath;
    }
}

int main(int argc, char* argv[])
{
    // Регистрация типов для мета-системы Qt
    qRegisterMetaType<CheckType>("CheckType");
    qRegisterMetaType<QList<CheckType>>("QList<CheckType>");
    qRegisterMetaType<QList<CheckResult>>("QList<CheckResult>");

    if (argc > 1)
    {
        // Если передан аргумент, работаем в консольном режиме
        QCoreApplication a(argc, argv);
        runCliMode(QString::fromLocal8Bit(argv[1]));
        return 0;
    }
    else
    {
        // Иначе запускаем графический интерфейс
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}
