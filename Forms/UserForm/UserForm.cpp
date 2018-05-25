#include "UserForm.h"
#include "ui_UserForm.h"

#include <QMessageBox>
#include <QRadioButton>

#include "Modules/CreateUser/Model/CreateUserModel.h"
#include "Modules/UpdateUserData/Model/UpdateUserDataModel.h"

//  :: Lifecycle ::

UserForm::UserForm(const User &user, QWidget *parent) :
    QWidget(parent),
	m_user(user),
    ui(new Ui::UserForm)
{
    ui->setupUi(this);

	initUpdateModel();
	initCreateModel();
	fillGenderRadioButtons();
	fillProfessionsComboBox();
	ui->birthday->setMaximumDate(QDate::currentDate());

	if(m_user.getId()) {
		ui->title->setText("Редактирование профиля");
        hideLoginData();
    } else {
		ui->title->setText("Создание учётной записи");

        connect(ui->login, &QLineEdit::textChanged,
                &m_user, &User::setLogin);
        connect(ui->login, &QLineEdit::textChanged,
                this, &UserForm::onLoginChanged);
        onLoginChanged("");

        connect(ui->password, &QLineEdit::textChanged,
                &m_user, &User::setPassword);
        connect(ui->password, &QLineEdit::textChanged,
                this, &UserForm::onPasswordChanged);
        connect(ui->repeatPassword, &QLineEdit::textChanged,
                this, &UserForm::onRepeatPasswordChanged);

        ui->passConflict->setStyleSheet("QLabel { color : red; }");
        ui->passConflict->hide();

        ui->passOk->setStyleSheet("QLabel { color : green; }");
        ui->passOk->hide();
    }

    connect(ui->name, &QLineEdit::textChanged,
            &m_user, &User::setName);
	connect(ui->maleRadioButton, &QRadioButton::clicked,
			[&](){ m_user.setGender(Gender::Male); });
	connect(ui->femaleRadioButton, &QRadioButton::clicked,
			[&](){ m_user.setGender(Gender::Female); });
    connect(ui->birthday, &QDateEdit::dateChanged,
			&m_user, &User::setBirthday);
    connect(ui->profession, &QComboBox::currentTextChanged,
            &m_user, &User::setProfession);
    connect(ui->assessment, SIGNAL(valueChanged(int)),
            &m_user, SLOT(setExpertAssessment(int)));

    connect(ui->saveBtn, &QPushButton::clicked,
            this, &UserForm::onSaveUserBtnClicked);
    connect(ui->cancelBtn, &QPushButton::clicked,
            this, &UserForm::editingCanceled);

	setUser(m_user);
}

UserForm::~UserForm() {
    delete ui;
}

//  :: Public accessors ::

User UserForm::getUser() const {
	return m_user;
}
void UserForm::setUser(const User &user) {
	m_user = user;
	ui->login->setText(m_user.getLogin());

	ui->name->setText(m_user.getName());
	setGender(m_user.getGender());
	ui->birthday->setDate(m_user.getBirthday());
	ui->profession->setCurrentText(m_user.getProfession());
	ui->assessment->setValue(m_user.getExpertAssessment());
}

//  :: Private methods ::

void UserForm::hideLoginData() {
    ui->loginDataTitle->hide();
    for(int i = 0; i < ui->loginForm->count(); i++) {
        ui->loginForm->itemAt(i)->widget()->hide();
    }
}

void UserForm::initCreateModel() {
	m_createModel = new CreateUserModel(this);
	connect(m_createModel, SIGNAL(userPut()),
			this, SIGNAL(editingCanceled()));
	connect(m_createModel, &CreateUserModel::error,
			this, &UserForm::onError);
}

void UserForm::initUpdateModel() {
	m_updateModel = new UpdateUserDataModel(this);
	connect(m_updateModel, SIGNAL(userPatched()),
			this, SIGNAL(editingCanceled()));
	connect(m_updateModel, &UpdateUserDataModel::error,
			this, &UserForm::onError);
}

void UserForm::fillGenderRadioButtons() {
	ui->maleRadioButton->setText(genderToString(Gender::Male));
	ui->femaleRadioButton->setText(genderToString(Gender::Female));
}

void UserForm::fillProfessionsComboBox() {
	connect(m_createModel, &CreateUserModel::professionsGot,
			this, &UserForm::onProfessionsGot);
	m_createModel->getProfessions();
}

void UserForm::setGender(Gender gender) {
	m_user.setGender(gender);
	switch (gender) {
	case Gender::Male:
		ui->maleRadioButton->click();
		break;
	case Gender::Female:
		ui->femaleRadioButton->click();
		break;
	}
}

void UserForm::onLoginChanged(const QString &login) {
    if(login.isEmpty()) {
        ui->saveBtn->setEnabled(false);
        ui->saveBtn->setToolTip("Для создания пользователя необходимо ввести логин");
    } else {
        ui->saveBtn->setEnabled(true);
        ui->saveBtn->setToolTip("");
    }
}

void UserForm::onPasswordChanged(const QString &pass) {
    QString repPass = ui->repeatPassword->text();
    if(!repPass.isEmpty()) {
        bool passesEqual = pass == repPass;
        ui->passConflict->setVisible(!passesEqual);
        ui->passOk->setVisible(passesEqual);
    } else {
        ui->passConflict->hide();
        ui->passOk->hide();
    }
}

void UserForm::onRepeatPasswordChanged(const QString &repPass) {
    QString pass = ui->password->text();
    if(!pass.isEmpty()) {
        if(repPass.size() >= pass.size()) {
            bool passesEqual = pass == repPass;
            ui->passConflict->setVisible(!passesEqual);
            ui->passOk->setVisible(passesEqual);
        }
    } else {
        ui->passConflict->hide();
        ui->passOk->hide();
    }
}

void UserForm::onSaveUserBtnClicked() {
    QString pass = ui->password->text();
    QString repPass = ui->repeatPassword->text();
    if(pass.isEmpty() && repPass.isEmpty()) {
        saveUser();
    } else if (pass == repPass) {
        saveUser();
    } else {
        ui->passConflict->setVisible(true);
        ui->passOk->setVisible(false);
    }
}

void UserForm::onProfessionsGot(QStringList professions) {
	int indexOfProfession = professions.indexOf(m_user.getProfession());
	if (indexOfProfession < 0) {
		professions.insert(0, m_user.getProfession());
		indexOfProfession = 0;
	}

	ui->profession->addItems(professions);
	ui->profession->setCurrentIndex(indexOfProfession);
	ui->profession->adjustSize();
}

void UserForm::saveUser() {
	if(m_user.getId()) {
        updateUser();
    } else {
        putUser();
    }
}

void UserForm::updateUser() {
	m_updateModel->patchUser(m_user);
}

void UserForm::putUser() {
	m_createModel->putUser(m_user);
}

void UserForm::onError(const QString &error) {
    QMessageBox::critical(this, "Ошибка", error);
}
