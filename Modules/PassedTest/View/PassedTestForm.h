#pragma once

#include <QWidget>

namespace Ui {
class PassedTestForm;
}
class PassedTestModel;
class ScaleStatistics;

class PassedTestForm : public QWidget {
    Q_OBJECT

public:
    explicit PassedTestForm(QWidget *parent = nullptr);
    ~PassedTestForm();

    PassedTestModel *getModel() const;
    void setModel(PassedTestModel *model);

signals:
    void scaleSelected(int testId, const ScaleStatistics &scaleStatistics);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onScaleDoubleClicked(const QModelIndex &index);

private:
    void updatePassedTestName();
    void setPassedTestName(const QString &name);

    PassedTestModel *m_model;
    Ui::PassedTestForm *ui;
};
