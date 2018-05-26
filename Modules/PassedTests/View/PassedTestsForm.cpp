#include "PassedTestsForm.h"
#include "ui_TestsStatisticsForm.h"

PassedTestsForm::PassedTestsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestsStatisticsForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked,
            this, &PassedTestsForm::backButtonClicked);
}

PassedTestsForm::~PassedTestsForm() {
    delete ui;
}
