#include "UserDataForm.h"
#include "ui_UserDataForm.h"

#include "Entities/UserRole/UserRole.h"
#include "Entities/UserRole/Model/UserRoleModel.h"

//  :: Lifecycle ::

UserDataForm::UserDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDataForm)
{
    ui->setupUi(this);

    ui->roleComboBox->setModel(new UserRoleModel(ui->roleComboBox));
}

UserDataForm::~UserDataForm() {
    delete ui;
}

//  :: Public accessors
//  :: Login ::
QString UserDataForm::getLogin() const {
    return ui->loginLineEdit->text();
}
void UserDataForm::setLogin(const QString &login) {
    ui->loginLineEdit->setText(login);
}

//  :: Password ::
QString UserDataForm::getPassword() const {
    return ui->passwordLineEdit->text();
}
void UserDataForm::setPassword(const QString &password) {
    ui->passwordLineEdit->setText(password);
}

//  :: Repeat password ::
QString UserDataForm::getRepeatPassword() const {
    return ui->repeatPasswordLineEdit->text();
}
void UserDataForm::setRepeatPassword(const QString &repeatPassword) {
    ui->passwordLineEdit->setText(repeatPassword);
}

//  :: Роль ::
UserRole UserDataForm::getRole() const {
    return static_cast<UserRole>(ui->roleComboBox->currentIndex());
}
void UserDataForm::setRole(UserRole role) {
    ui->roleComboBox->setCurrentIndex(static_cast<int>(role));
}
