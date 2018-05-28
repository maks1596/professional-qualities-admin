#include "PassedTestsForm.h"
#include "ui_PassedTestsForm.h"

#include "../Model/PassedTestsColumnIndex.h"
#include "../Model/PassedTestsModel.h"

using namespace PassedTests;

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
            ->setSectionResizeMode(NAME_COLUMN_INDEX, QHeaderView::Stretch);

    // При нажатии на элемент таблицы выделяется целая строка вместо одной ячейки
    ui->passedTestsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

PassedTestsForm::~PassedTestsForm() {
    delete ui;
}
