#pragma once

#include "Forms/EntitiesForm/EntitiesForm.h"

class User;
class UsersModel;

class UsersForm : public EntitiesForm {
Q_OBJECT

public:
    explicit UsersForm(QWidget *parent = nullptr);

public slots:
	virtual void update() override;

signals:
    void addUserButtonClicked();
    void createUserForm(const User &user);

protected slots:
	virtual void onAddBtnClicked() override;

protected:
	virtual void removeEntity(const int &id) override;
	virtual void editEntity(const int &id) override;

private slots:
	void updateUsersTable(const QList<User> &users);

private:
	UsersModel *m_model;
};
