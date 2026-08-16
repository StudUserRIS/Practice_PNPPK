#ifndef REPORTVIEW_H
#define REPORTVIEW_H

#include "Checks/icheck.h"
#include <QWidget>

namespace Ui
{
class ReportView;
}

class ReportView : public QWidget
{
    Q_OBJECT

public:
    explicit ReportView(QWidget* parent = nullptr);
    ~ReportView();

public slots:
    void onShowErrors(QList<CheckResult> errors);

private:
    Ui::ReportView* ui;
};

#endif // REPORTVIEW_H
