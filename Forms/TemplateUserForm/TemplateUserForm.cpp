#include "TemplateUserForm.h"
#include "ui_TemplateUserForm.h"

#include <QMessageBox>

//  :: Constants ::

const QString ERROR_MESSAGE_BOX_TITLE = "Ошибка";

//  :: Lifecycle ::

TemplateUserForm::TemplateUserForm(QWidget *userDataWidget,
                                   QWidget *personalDataWidget,
                                   QWidget *parent) :
    QWidget(parent),
    m_userDataWidget(userDataWidget),
    m_personalDataWidget(personalDataWidget),
    ui(new Ui::TemplateUserForm)
{
    ui->setupUi(this);

    userDataWidget->setParent(this);
    ui->userDataLayout->addWidget(userDataWidget);

    personalDataWidget->setParent(this);
    ui->personalDataLayout->addWidget(personalDataWidget);

    connect(ui->saveButton, &QPushButton::clicked,
            this, &TemplateUserForm::saveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &TemplateUserForm::cancelButtonClicked);
}

TemplateUserForm::~TemplateUserForm() {
    delete ui;
}

//  :: Public methods ::

void TemplateUserForm::showErrorMessageBox(const QString &message) {
    QMessageBox::critical(this, ERROR_MESSAGE_BOX_TITLE, message);
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
QWidget *TemplateUserForm::getUserDataWidget() const {
    return m_userDataWidget;
}

//  :: Personal data form ::
QWidget *TemplateUserForm::getPersonalDataWidget() const {
    return m_personalDataWidget;
}

//  :: Public methods ::


void TemplateUserForm::setSaveButtonEnabled(bool enabled) {
    ui->saveButton->setEnabled(enabled);
}

void TemplateUserForm::setSaveButtonToolTip(const QString &toolTip) {
    ui->saveButton->setToolTip(toolTip);
}
