#include "TestsStatisticsForm.h"
#include "ui_TestsStatisticsForm.h"

TestsStatisticsForm::TestsStatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestsStatisticsForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked,
            this, &TestsStatisticsForm::backButtonClicked);
}

TestsStatisticsForm::~TestsStatisticsForm() {
    delete ui;
}
