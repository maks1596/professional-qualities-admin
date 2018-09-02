#include "TemplateUserForm.h"
#include "ui_TemplateUserForm.h"

//  :: Lifecycle ::

TemplateUserForm::TemplateUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateUserForm)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked,
            this, &TemplateUserForm::saveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &TemplateUserForm::cancelButtonClicked);
}

TemplateUserForm::~TemplateUserForm() {
    delete ui;
}

//  :: Protected accessors ::
//  :: Title ::
QString TemplateUserForm::getTitle() const {
    return ui->titleLabel->text();
}
void TemplateUserForm::setTitle(const QString &title) {
    ui->titleLabel->setText(title);
}

//  :: User data form ::
QWidget *TemplateUserForm::getUserDataForm() const {
    return ui->userDataForm;
}
void TemplateUserForm::setUserDataForm(QWidget *userDataForm) {
    ui->userDataForm = userDataForm;
}

//  :: Personal data form ::
QWidget *TemplateUserForm::getPersonalDataForm() const {
    return ui->personalDataForm;
}
void TemplateUserForm::setPersonalDataForm(QWidget *personalDataForm) {
    ui->personalDataForm = personalDataForm;
}
