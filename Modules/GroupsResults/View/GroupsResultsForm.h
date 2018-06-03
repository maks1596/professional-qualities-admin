#pragma once

#include <QWidget>

namespace Ui {
class GroupsResultsForm;
}
class GroupsResultsModel;

class GroupsResultsForm : public QWidget {
    Q_OBJECT

public:
    explicit GroupsResultsForm(QWidget *parent = nullptr);
    ~GroupsResultsForm();

    GroupsResultsModel *getModel() const;
    void setModel(GroupsResultsModel *model);

private:
    GroupsResultsModel *m_model;
    Ui::GroupsResultsForm *ui;
};
