#pragma once

#include "Forms/TemplateUserForm/TemplateUserForm.h"

class User;

class EditUserView: public TemplateUserForm {
    Q_OBJECT

public:
    explicit EditUserView(const User &user, QWidget *parent = nullptr);
    virtual ~EditUserView() = default;

private:
};
