#include "AddUserView.h"
#include "ui_AddUserView.h"

#include <QMessageBox>
#include <QRadioButton>

#include "Entities/Gender/Gender.h"

#include "Modules/CreateUser/Model/CreateUserModel.h"
#include "Modules/UpdateUserData/Model/UpdateUserDataModel.h"

//  :: Lifecycle ::

AddUserView::AddUserView(const User &user, QWidget *parent) :
    QWidget(parent),
	m_user(user),
    ui(new Ui::AddUserView)
{
    ui->setupUi(this);

	initUpdateModel();
    initCreateModel();

	if(m_user.getId()) {
		ui->title->setText("Редактирование профиля");
        hideLoginData();
    } else {
		ui->title->setText("Создание учётной записи");

        connect(ui->userDataForm, &UserDataForm::loginChanged,
                this, &AddUserView::loginChanged);
        connect(ui->userDataForm, &UserDataForm::passwordChanged,
                this, &AddUserView::passwordChanged);
        connect(ui->userDataForm, &UserDataForm::repeatPasswordChanged,
                this, &AddUserView::repeatPasswordChanged);

    }

    connect(ui->personalDataForm, &PersonalDataForm::expertAssessmentChanged,
            this, &AddUserView::expertAssessmentChanged);

    connect(ui->saveBtn, &QPushButton::clicked,
            this, &AddUserView::saveUserButtonClicked);
    connect(ui->cancelBtn, &QPushButton::clicked,
            this, &AddUserView::editingCanceled);

	setUser(m_user);
}

AddUserView::~AddUserView() {
    delete ui;
}

//  :: Public accessors ::
//  :: User ::
User AddUserView::getUser() const {
	return m_user;
}
void AddUserView::setUser(const User &user) {
	m_user = user;
    ui->userDataForm->setLogin(m_user.getLogin());

//	ui->name->setText(m_user.getName());
//	setGender(m_user.getGender());
//	ui->birthday->setDate(m_user.getBirthday());
//	ui->profession->setCurrentText(m_user.getProfession());
//  ui->assessment->setValue(m_user.getExpertAssessment());
}

//  :: Login ::
QString AddUserView::getLogin() const {
    return ui->userDataForm->getLogin();
}

//  :: Password ::
QString AddUserView::getPassword() const {
    return ui->userDataForm->getPassword();
}

//  :: Repeat password ::
QString AddUserView::getRepeatPassword() const {
    return ui->userDataForm->getRepeatPassword();
}

//  :: Role ::
UserRole AddUserView::getRole() const {
    return ui->userDataForm->getRole();
}

//  :: Passwords hint ::
void AddUserView::setPasswordsHintStatus(PasswordsHintStatus status) {
    ui->userDataForm->setPasswordsHintStatus(status);
}

//  :: Birthdate range ::
void AddUserView::setMaximumBirtdate(const QDate &maxDate) {
    ui->personalDataForm->setMaximumBirtdate(maxDate);
}
void AddUserView::setMinimumBirtdate(const QDate &minDate) {
    ui->personalDataForm->setMinimumBirtdate(minDate);
}

//  :: Expert assessment range ::
void AddUserView::setMaximumExpertAssessment(int maxAssessment) {
    ui->personalDataForm->setMaximumExpertAssessment(maxAssessment);
}
void AddUserView::setMinimumExpertAssessment(int minAssessment) {
    ui->personalDataForm->setMinimumExpertAssessment(minAssessment);
}

//  :: Professions model ::
QAbstractItemModel *AddUserView::getProfessionsModel() const {
    return ui->personalDataForm->getProfessionsModel();
}
void AddUserView::setProfessionsModel(QAbstractItemModel *model) {
    ui->personalDataForm->setProfessionsModel(model);
}

void AddUserView::setUserExcludedFromAsstimationMessageVisibility(bool visible) {
    ui->personalDataForm
            ->setUserExcludedFromAsstimationMessageVisibility(visible);
}

//  :: Public methods ::

void AddUserView::setSaveButtonEnabled(bool enabled) {
    ui->saveBtn->setEnabled(enabled);
}

void AddUserView::setSaveButtonToolTip(const QString &toolTip) {
    ui->saveBtn->setToolTip(toolTip);
}

void AddUserView::showErrorMessage(const QString &message) {
    QMessageBox::critical(this, "Ошибка", message);
}

//  :: Private methods ::

void AddUserView::hideLoginData() {
    ui->loginDataTitle->hide();
    ui->userDataForm->hide();
}

void AddUserView::initCreateModel() {
	m_createModel = new CreateUserModel(this);
	connect(m_createModel, SIGNAL(userPut()),
			this, SIGNAL(editingCanceled()));
	connect(m_createModel, &CreateUserModel::error,
            this, &AddUserView::showErrorMessage);
}

void AddUserView::initUpdateModel() {
	m_updateModel = new UpdateUserDataModel(this);
	connect(m_updateModel, SIGNAL(userPatched()),
			this, SIGNAL(editingCanceled()));
	connect(m_updateModel, &UpdateUserDataModel::error,
            this, &AddUserView::showErrorMessage);
}

void AddUserView::saveUser() {
	if(m_user.getId()) {
        updateUser();
    } else {
        putUser();
    }
}

void AddUserView::updateUser() {
	m_updateModel->patchUser(m_user);
}

void AddUserView::putUser() {
	m_createModel->putUser(m_user);
}
