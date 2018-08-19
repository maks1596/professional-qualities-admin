#include "UserDataForm.h"
#include "ui_UserDataForm.h"

#include "Entities/UserRole/UserRole.h"
#include "Entities/UserRole/Model/UserRoleModel.h"
#include "PasswordsHintStatus.h"

//  :: Constatnts ::

const QString PASSWORDS_DO_NOT_MATCH = "Пароли не совпадают";
const QString PASSWORDS_MATCH = "Пароли совпадают";

const QString PASSWORDS_MATCH_TEXT_COLOR = "green";
const QString PASSWORDS_DO_NO_MATCH_TEXT_COLOR = "red";

const int PASSWORD_HINT_LABEL_MARGIN_TOP = 6;

//  :: Lifecycle ::

UserDataForm::UserDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDataForm)
{
    ui->setupUi(this);

    ui->roleComboBox->setModel(new UserRoleModel(ui->roleComboBox));

    connect(ui->loginLineEdit, &QLineEdit::textChanged,
            this, &UserDataForm::loginChanged);
    connect(ui->passwordLineEdit, &QLineEdit::textChanged,
            this, &UserDataForm::passwordChanged);
    connect(ui->repeatPasswordLineEdit, &QLineEdit::textChanged,
            this, &UserDataForm::repeatPasswordChanged);
    connect(ui->roleComboBox, SIGNAL(currentIndexChanged(int)),
            SLOT(onRoleComboBoxCurrentIndexChanged(int)));

    ui->passwordsHintLabel->setStyleSheet(QString("QLabel { margin-top : %1}")
                                          .arg(PASSWORD_HINT_LABEL_MARGIN_TOP));
    setPasswordsHintStatus(PasswordsHintStatus::Hidden);
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

//  :: Passwords hint ::
void UserDataForm::setPasswordsHintStatus(PasswordsHintStatus status) {
    switch (status) {
    case PasswordsHintStatus::Hidden: {
        ui->passwordsHintLabel->hide();
    } break;

    case PasswordsHintStatus::Match: {
        ui->passwordsHintLabel->setText(PASSWORDS_MATCH);
        setPasswordHintLabelTextColor(PASSWORDS_MATCH_TEXT_COLOR);
        ui->passwordsHintLabel->show();
    } break;

    case PasswordsHintStatus::NotMatch: {
        ui->passwordsHintLabel->setText(PASSWORDS_DO_NOT_MATCH);
        setPasswordHintLabelTextColor(PASSWORDS_DO_NO_MATCH_TEXT_COLOR);
        ui->passwordsHintLabel->show();
    } break;
    }
}

//  :: Private slots ::

void UserDataForm::onRoleComboBoxCurrentIndexChanged(int index) {
    emit roleChanged(static_cast<UserRole>(index));
}

//  :: Private methods ::

void UserDataForm::setPasswordHintLabelTextColor(const QString &color) {
    ui->passwordsHintLabel->setStyleSheet(QString("QLabel { color : %1 }")
                                          .arg(color));
}
