#include "PassedTestsForm.h"
#include "ui_PassedTestsForm.h"

#include "../Model/PassedTestsModel.h"

PassedTestsForm::PassedTestsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassedTestsForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked,
            this, &PassedTestsForm::backButtonClicked);

    ui->passedTestsTableView->setModel(new PassedTestsModel(this));
    ui->passedTestsTableView->resizeColumnsToContents();
    ui->passedTestsTableView->horizontalHeader()
            ->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->passedTestsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

PassedTestsForm::~PassedTestsForm() {
    delete ui;
}
