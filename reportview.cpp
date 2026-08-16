#include "reportview.h"
#include "qmessagebox.h"
#include "ui_reportview.h"

ReportView::ReportView(QWidget* parent) : QWidget(parent), ui(new Ui::ReportView)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 400);
    resize(1600, 500);
}

ReportView::~ReportView() { delete ui; }

void ReportView::onShowErrors(QList<CheckResult> errors)
{
    if (errors.isEmpty())
    {
        QMessageBox::information(this, "Поздравляю!", "Ошибки не найдены");
        return;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(errors.count());
    int row = 0;
    for (const auto& error : errors)
    {
        QString lines;
        for (int lineNumber : error.lines) lines.append(QString::number(lineNumber) + ", ");
        lines.chop(2);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(lines));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(error.fileName));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(error.readableInfo));
        row++;
    }
    show();
}
