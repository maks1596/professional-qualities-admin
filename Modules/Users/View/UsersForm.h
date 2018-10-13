#pragma once

#include "Forms/EntitiesForm/EntitiesForm.h"

class User;

class UsersForm : public EntitiesForm {
    Q_OBJECT

public:
    explicit UsersForm(QWidget *parent = nullptr);

    void showRemoveUserDialog(uint userIndex);
    void showEditUserView(const User &user);
    void showAddUserView();

signals:
    void removeUserClicked(uint userIndex);

protected:
    QString getTitle() const override;
    QString getAddButtonIconName() const override;
    QString getAddButtonToolTip() const override;
};
