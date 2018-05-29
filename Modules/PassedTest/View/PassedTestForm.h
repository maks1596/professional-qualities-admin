#pragma once

#include <QWidget>

namespace Ui {
class PassedTestForm;
}

class PassedTestForm : public QWidget {
    Q_OBJECT

public:
    explicit PassedTestForm(QWidget *parent = nullptr);
    ~PassedTestForm();

signals:
    void backButtonClicked();

private:
    Ui::PassedTestForm *ui;
};
