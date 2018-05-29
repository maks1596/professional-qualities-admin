#pragma once

#include <QWidget>

namespace Ui {
class PassedTestsForm;
}

class PassedTest;
class PassedTestsModel;

class PassedTestsForm : public QWidget {
    Q_OBJECT

public:
    explicit PassedTestsForm(QWidget *parent = nullptr);
    ~PassedTestsForm();

    PassedTestsModel *getModel() const;
    void setModel(PassedTestsModel *model);

public slots:
    void startUpdating();
    void stopUpdating();

signals:
    void backButtonClicked();
    void passedTestSelected(int id);
    void passedTestSelected(const PassedTest &passedTest);
    void error(const QString &errorMessage);

private slots:
    void onPassedTestDoubleClicked(const QModelIndex &index);

private:
    PassedTestsModel *m_model;
    Ui::PassedTestsForm *ui;
};
