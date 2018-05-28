#include "PassedTestStatisticsForm.h"
#include "ui_PassedTestStatisticsForm.h"

PassedTestStatisticsForm::PassedTestStatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassedTestStatisticsForm)
{
    ui->setupUi(this);
}

PassedTestStatisticsForm::~PassedTestStatisticsForm() {
    delete ui;
}
