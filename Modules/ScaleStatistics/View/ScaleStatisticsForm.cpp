#include "ScaleStatisticsForm.h"
#include "ui_ScaleStatisticsForm.h"

//  :: Lifecycle ::

ScaleStatisticsForm::ScaleStatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScaleStatisticsForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked,
            this, &ScaleStatisticsForm::backButtonClicked);
}

ScaleStatisticsForm::~ScaleStatisticsForm() {
    delete ui;
}
