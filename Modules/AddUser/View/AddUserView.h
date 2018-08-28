#pragma once

#include <QWidget>

#include "Entities/User/User.h"

class QAbstractItemModel;

class CreateUserModel;
class UpdateUserDataModel;

namespace Ui {
class AddUserView;
}

enum class UserRole;
enum class PasswordsHintStatus;

class AddUserView : public QWidget {
Q_OBJECT

public:
    explicit AddUserView(const User &user, QWidget *parent = nullptr);
    ~AddUserView();

	User getUser() const;
	void setUser(const User &user);

    QString getLogin() const;
    QString getPassword() const;
    QString getRepeatPassword() const;
    UserRole getRole() const;

    void setPasswordsHintStatus(PasswordsHintStatus status);

    void setMaximumBirtdate(const QDate &maxDate);
    void setMinimumBirtdate(const QDate &minDate);

    void setMaximumExpertAssessment(int maxAssessment);
    void setMinimumExpertAssessment(int minAssessment);

    QAbstractItemModel *getProfessionsModel() const;
    void setProfessionsModel(QAbstractItemModel *model);

    void setUserExcludedFromAsstimationMessageVisibility(bool visible);

    void setSaveButtonEnabled(bool enabled);
    void setSaveButtonToolTip(const QString &toolTip);

    void showErrorMessage(const QString &message);

signals:
    void loginChanged(const QString &login);
    void passwordChanged(const QString &password);
    void repeatPasswordChanged(const QString &repeatPassword);

    void expertAssessmentChanged(int assessment);

    void saveUserButtonClicked();
    void editingCanceled();

private:
    void hideLoginData();
	void initCreateModel();
    void initUpdateModel();
	void setGender(Gender gender);

    void saveUser();
    void updateUser();
    void putUser();

    User m_user;
	CreateUserModel *m_createModel;
	UpdateUserDataModel *m_updateModel;
    Ui::AddUserView *ui;
};
