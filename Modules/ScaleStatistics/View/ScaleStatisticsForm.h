#pragma once

#include <QWidget>

namespace Ui {
class ScaleStatisticsForm;
}
class ScaleStatisticsModel;

class ScaleStatisticsForm : public QWidget {
    Q_OBJECT

public:
    explicit ScaleStatisticsForm(QWidget *parent = nullptr);
    ~ScaleStatisticsForm();

    ScaleStatisticsModel *getModel() const;
    void setModel(ScaleStatisticsModel *model);

signals:
    void backButtonClicked();

private:
    void updateGroupsResultsTabs();

    ScaleStatisticsModel *m_model;
    Ui::ScaleStatisticsForm *ui;
};
