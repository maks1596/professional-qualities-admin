#pragma once

#include <QWidget>

namespace Ui {
class TestsStatisticsForm;
}

class PassedTestsForm : public QWidget {
    Q_OBJECT

public:
    explicit PassedTestsForm(QWidget *parent = nullptr);
    ~PassedTestsForm();

signals:
    void backButtonClicked();

private:
    Ui::TestsStatisticsForm *ui;
};
