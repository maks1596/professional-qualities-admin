#include "PassedTestsForm.h"
#include "ui_PassedTestsForm.h"

#include "../Model/PassedTestsColumnIndex.h"
#include "../Model/PassedTestsModel.h"

using namespace PassedTests;

//  :: Lifecycle ::

PassedTestsForm::PassedTestsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassedTestsForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked,
            this, &PassedTestsForm::backButtonClicked);
    connect(ui->passedTestsTableView, &QTableView::doubleClicked,
            this, &PassedTestsForm::onPassedTestDoubleClicked);
}

PassedTestsForm::~PassedTestsForm() {
    delete ui;
}

//  :: Public accessors ::

PassedTestsModel *PassedTestsForm::getModel() const {
    return m_model;
}
void PassedTestsForm::setModel(PassedTestsModel *model) {
    m_model = model;
    ui->passedTestsTableView->setModel(model);

    ui->passedTestsTableView->resizeColumnsToContents();
    ui->passedTestsTableView->horizontalHeader()
            ->setSectionResizeMode(NAME_COLUMN_INDEX, QHeaderView::Stretch);
}

//  :: Public slots ::

void PassedTestsForm::startUpdating() {
    m_model->startUpdating();
}
void PassedTestsForm::stopUpdating() {
    m_model->stopUpdating();
}

//  :: Private slots ::

void PassedTestsForm::onPassedTestDoubleClicked(const QModelIndex &index) {
    auto id = getModel()->getId(index);
    if (id > 0) {
        emit passedTestSelected(id);
    } // иначе 'что-то пошло не так', но это и не важно
}


