#pragma once

#include "Forms/TemplateUserForm/TemplateUserForm.h"

class EditUserDataForm;
class PersonalDataForm;
class User;

class EditUserView: public TemplateUserForm {
    Q_OBJECT

public:
    explicit EditUserView(const User &user, QWidget *parent = nullptr);
    virtual ~EditUserView() = default;

private:
    EditUserDataForm *getEditUserDataForm();
    EditUserDataForm *getEditUserDataForm() const;

    PersonalDataForm *getPersonalDataForm();
    PersonalDataForm *getPersonalDataForm() const;
};
