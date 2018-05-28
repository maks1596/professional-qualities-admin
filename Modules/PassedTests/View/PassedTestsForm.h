#pragma once

#include <QWidget>

namespace Ui {
class PassedTestsForm;
}

class PassedTestsModel;

class PassedTestsForm : public QWidget {
    Q_OBJECT

public:
    explicit PassedTestsForm(QWidget *parent = nullptr);
    ~PassedTestsForm();

    PassedTestsModel *getModel() const;
    void setModel(PassedTestsModel *model);

signals:
    void backButtonClicked();
    void passedTestSelected(int id);

private slots:
    void onPassedTestDoubleClicked(const QModelIndex &index);

private:
    PassedTestsModel *m_model;
    Ui::PassedTestsForm *ui;
};
