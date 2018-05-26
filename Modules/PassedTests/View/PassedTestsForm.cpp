#include "PassedTestsForm.h"
#include "ui_PassedTestsForm.h"

PassedTestsForm::PassedTestsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassedTestsForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked,
            this, &PassedTestsForm::backButtonClicked);
}

PassedTestsForm::~PassedTestsForm() {
    delete ui;
}
