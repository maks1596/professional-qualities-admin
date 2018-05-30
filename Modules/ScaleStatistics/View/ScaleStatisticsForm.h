#pragma once

#include <QWidget>

namespace Ui {
class ScaleStatisticsForm;
}

class ScaleStatisticsForm : public QWidget {
    Q_OBJECT

public:
    explicit ScaleStatisticsForm(QWidget *parent = nullptr);
    ~ScaleStatisticsForm();

signals:
    void backButtonClicked();

private:
    Ui::ScaleStatisticsForm *ui;
};
