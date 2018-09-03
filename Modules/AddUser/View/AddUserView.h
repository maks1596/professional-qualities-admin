#pragma once

#include "Forms/TemplateUserForm/TemplateUserForm.h"

class QAbstractItemModel;

enum class Gender;
enum class PasswordsHintStatus;
enum class UserRole;

class UserDataForm;
class PersonalDataForm;

class AddUserView: public TemplateUserForm {
Q_OBJECT

public:
    explicit AddUserView(QWidget *parent = nullptr);
    virtual ~AddUserView() = default;

    QString getLogin() const;
    QString getPassword() const;
    QString getRepeatPassword() const;
    UserRole getRole() const;

    QString getName() const;
    Gender getGender() const;
    QDate getBirthdate() const;
    QString getProfession() const;
    int getExpertAssessment() const;

    void setPasswordsHintStatus(PasswordsHintStatus status);

    void setMaximumBirtdate(const QDate &maxDate);
    void setMinimumBirtdate(const QDate &minDate);

    void setMaximumExpertAssessment(int maxAssessment);
    void setMinimumExpertAssessment(int minAssessment);

    QAbstractItemModel *getProfessionsModel() const;
    void setProfessionsModel(QAbstractItemModel *model);

    void setUserExcludedFromAsstimationMessageVisibility(bool visible);

signals:
    void loginChanged(const QString &login);
    void passwordChanged(const QString &password);
    void repeatPasswordChanged(const QString &repeatPassword);

    void expertAssessmentChanged(int assessment);

private:
    void setGender(Gender gender);

    void initUserDataForm();
    void initPersonalDataForm();

    UserDataForm *getUserDataForm() const;
    PersonalDataForm *getPersonalDataForm() const;
};
