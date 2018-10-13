#pragma once

#include "Forms/EntitiesForm/EntitiesForm.h"

class UsersForm : public EntitiesForm {
    Q_OBJECT

public:
    explicit UsersForm(QWidget *parent = nullptr);

    void showRemoveUserDialog(uint userIndex);

signals:
    void removeUser(uint userIndex);

protected:
    QString getTitle() const override;
    QString getAddButtonIconName() const override;
    QString getAddButtonToolTip() const override;
};
