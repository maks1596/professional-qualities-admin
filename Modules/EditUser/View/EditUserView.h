#pragma once

#include "Forms/TemplateUserForm/TemplateUserForm.h"

class QDate;

class EditUserDataForm;
class PersonalDataForm;
class User;

enum class Gender;
enum class UserRole;

class EditUserView: public TemplateUserForm {
    Q_OBJECT

public:
    explicit EditUserView(const User &user, QWidget *parent = nullptr);
    virtual ~EditUserView() = default;

    //  :: Accessors ::

    QString getLogin() const;
    QString getPassword() const;
    UserRole getRole() const;

    QString getName() const;
    Gender getGender() const;
    QDate getBirtdate() const;
    QString getProfession() const;
    int getExpertAssessment() const;

private:
    EditUserDataForm *getEditUserDataForm();
    EditUserDataForm *getEditUserDataForm() const;

    PersonalDataForm *getPersonalDataForm();
    PersonalDataForm *getPersonalDataForm() const;
};
