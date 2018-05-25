#pragma once

#include <QWidget>

#include "Entities/User/User.h"

class CreateUserModel;
class UpdateUserDataModel;

namespace Ui {
class UserForm;
}

class UserForm : public QWidget {
Q_OBJECT

public:
    explicit UserForm(const User &user, QWidget *parent = nullptr);
    ~UserForm();

public:
	User getUser() const;
	void setUser(const User &user);

signals:
    void editingCanceled();

private slots:
    void onLoginChanged(const QString &login);
    void onPasswordChanged(const QString &pass);
    void onRepeatPasswordChanged(const QString &repPass);
    void onSaveUserBtnClicked();
	void onProfessionsGot(QStringList professions);

	void onError(const QString &error);

private:
    void hideLoginData();
	void initCreateModel();
	void initUpdateModel();
	void fillGenderRadioButtons();
	void fillProfessionsComboBox();
	void setGender(Gender gender);

    void saveUser();
    void updateUser();
    void putUser();

    User m_user;
	CreateUserModel *m_createModel;
	UpdateUserDataModel *m_updateModel;
    Ui::UserForm *ui;
};
