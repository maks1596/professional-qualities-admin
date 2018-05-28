#include "PassedTestStatisticsForm.h"
#include "ui_PassedTestStatisticsForm.h"

PassedTestStatisticsForm::PassedTestStatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassedTestStatisticsForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked,
            this, &PassedTestStatisticsForm::backButtonClicked);
}

PassedTestStatisticsForm::~PassedTestStatisticsForm() {
    delete ui;
}
