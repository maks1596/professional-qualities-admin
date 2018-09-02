#include "EditUserDataForm.h"
#include "ui_EditUserDataForm.h"

#include "Entities/UserRole/UserRole.h"

//  :: Lifecycle ::

EditUserDataForm::EditUserDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserDataForm)
{
    ui->setupUi(this);

    // Пароль пока не меняем

    ui->roleComboBox->setModel(new UserRoleModel(ui->roleComboBox));
    connect(ui->roleComboBox, SIGNAL(currentIndexChanged(int)),
            SLOT(onRoleComboBoxCurrentIndexChanged(int)));
}

EditUserDataForm::~EditUserDataForm() {
    delete ui;
}

//  :: Public accessors ::
//  :: Login ::
QString EditUserDataForm::getLogin() const {
    return ui->loginLabel->text();
}
void EditUserDataForm::setLogin(const QString &login) {
    ui->loginLabel->setText(login);
}

//  :: Password ::
QString EditUserDataForm::getPassword() const {
    return ui->passwordLineEdit->text();
}
void EditUserDataForm::setPassword(const QString &password) {
    ui->passwordLineEdit->setText(password);
}

//  :: Role ::
UserRole EditUserDataForm::getRole() const {
    return static_cast<UserRole>(ui->roleComboBox->currentIndex());
}
void EditUserDataForm::setRole(const UserRole &role) {
    ui->roleComboBox->setCurrentIndex(static_cast<int>(role));
}

//  :: Private slots ::

void EditUserDataForm::onRoleComboBoxCurrentIndexChanged(int index) {
    emit roleChanged(static_cast<UserRole>(index));
}
