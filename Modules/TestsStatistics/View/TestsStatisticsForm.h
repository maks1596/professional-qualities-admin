#pragma once

#include <QWidget>

namespace Ui {
class TestsStatisticsForm;
}

class TestsStatisticsForm : public QWidget {
    Q_OBJECT

public:
    explicit TestsStatisticsForm(QWidget *parent = nullptr);
    ~TestsStatisticsForm();

signals:
    void backButtonClicked();

private:
    Ui::TestsStatisticsForm *ui;
};
