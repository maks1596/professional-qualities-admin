#pragma once

#include <QWidget>

namespace Ui {
class PassedTestStatisticsForm;
}

class PassedTestStatisticsForm : public QWidget {
    Q_OBJECT

public:
    explicit PassedTestStatisticsForm(QWidget *parent = nullptr);
    ~PassedTestStatisticsForm();

private:
    Ui::PassedTestStatisticsForm *ui;
};
