#include "EvaluationMapForm.h"
#include "ui_ScaleForm.h"

#include "Entities/EvaluationMap/EvaluationMap.h"
#include "Entities/Range/Appraised/AppraisedRange.h"
#include "Entities/Scale/Scale.h"
#include "Forms/AddAppraisedRangeForm/AddAppraisedRangeForm.h"

typedef AddAppraisedRangeForm AddForm;

EvaluationMapForm::EvaluationMapForm(Scale *scale, QWidget *parent) :
    QWidget(parent),
    m_scale(scale),
    m_evaluationMap(scale->getEvaluationMap()),
    ui(new Ui::ScaleForm)
{
    ui->setupUi(this);
    connect(ui->deleteBtn, &QPushButton::clicked,
            this, &EvaluationMapForm::onDeleteBtnClicked);

    configureTable();
    configureAddForm();
    update();
}

EvaluationMapForm::~EvaluationMapForm() {
    delete ui;
}

void EvaluationMapForm::configureTable() {
    ui->key->setColumnCount(COLUMNS_AMOUNT);

    QStringList labels;
    labels << "Баллы" << "Результат" << "";
    ui->key->setHorizontalHeaderLabels(labels);

    connect(ui->key, &QTableWidget::cellDoubleClicked,
            this, &EvaluationMapForm::onRangeDoubleClicked);
    connect(ui->key, &QTableWidget::cellClicked,
            [&](int i, int j) { if(j == DELETE_BTN) deleteRangeAt(i); });
}

void EvaluationMapForm::configureAddForm() {
    m_addForm = new AddForm(this);
    connect(m_addForm, &AddForm::editingFinished,
			this, &EvaluationMapForm::addAppraisedRange);
    ui->addFormLayout->addWidget(m_addForm);
}

void EvaluationMapForm::update() {
    ui->key->clearContents();
    ui->key->setRowCount(0);
    ui->scaleName->setText(m_scale->getName());

	for(uint i = 0; i < m_evaluationMap->size(); ++i) {
		addAppraisedRangeOnForm(m_evaluationMap->at(i));
    }
}

void EvaluationMapForm::onDeleteBtnClicked() {
    emit scaleDeleted(m_scale->getName());
    deleteLater();
}

void EvaluationMapForm::deleteRangeAt(const uint index) {
    ui->key->removeRow(index);
    m_evaluationMap->removeAt(index);
}

void EvaluationMapForm::onRangeDoubleClicked(int row) {
    m_addForm->setAppraisedRange(m_evaluationMap->at(row));
    deleteRangeAt(row);
}

void EvaluationMapForm::addAppraisedRange(const AppraisedRange &appraisedRange) {
	m_scale->getEvaluationMap()->addAppraisedRange(appraisedRange);
	addAppraisedRangeOnForm(appraisedRange);
}

void EvaluationMapForm::addAppraisedRangeOnForm(const AppraisedRange &appraisedRange) {
    uint insertRow = ui->key->rowCount();
    ui->key->setRowCount(insertRow + 1);

	ui->key->setItem(insertRow, RANGE, makeRange(appraisedRange.getRange()));
	ui->key->setItem(insertRow, RESULT,
					 new QTableWidgetItem(appraisedRange.getResult()));
    ui->key->setItem(insertRow, DELETE_BTN, new QTableWidgetItem("Удалить"));
    ui->key->resizeColumnsToContents();
}

QTableWidgetItem *EvaluationMapForm::makeRange(const Range &range) const {
    QString result = QString::number(range.first);
    if(range.first != range.second) {
        result.append(" - " + QString::number(range.second));
    }
    return new QTableWidgetItem(result);
}
