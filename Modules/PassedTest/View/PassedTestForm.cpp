#include "PassedTestForm.h"
#include "ui_PassedTestForm.h"

PassedTestForm::PassedTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassedTestForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked,
            this, &PassedTestForm::backButtonClicked);
}

PassedTestForm::~PassedTestForm() {
    delete ui;
}
