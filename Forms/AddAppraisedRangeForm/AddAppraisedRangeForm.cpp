#include "AddAppraisedRangeForm.h"
#include "ui_AddAppraisedRangeForm.h"

#include "Entities/Range/Appraised/AppraisedRange.h"

typedef AddAppraisedRangeForm AddForm;

AddForm::AddAppraisedRangeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAppraisedRangeForm)
{
    ui->setupUi(this);

    connect(ui->lowerBound, SIGNAL(valueChanged(int)),
            SLOT(onLowerBoundChanged(int)));
    connect(ui->upperBound, SIGNAL(valueChanged(int)),
            SLOT(onUpperBoundChanged(int)));

    connect(ui->result, &QLineEdit::returnPressed,
            ui->addBtn, &QPushButton::click);
    connect(ui->addBtn, &QPushButton::clicked,
            this, &AddForm::onAddBtnClicked);
}

AddForm::~AddAppraisedRangeForm() {
    delete ui;
}

void AddForm::setAppraisedRange(const AppraisedRange &appraisedRange) {
	ui->lowerBound->setValue(appraisedRange.getLowerRangeValue());
	ui->upperBound->setValue(appraisedRange.getUpperRangeValue());
	ui->result->setText(appraisedRange.getResult());
}

AppraisedRange AddForm::getAppraisedRange() const {
    return makeAppraisedRange();
}

void AddForm::onAddBtnClicked() {
    auto range = makeAppraisedRange();

    ui->lowerBound->setValue(ui->upperBound->value() + 1);
    ui->result->clear();

    emit editingFinished(range);
}

AppraisedRange AddForm::makeAppraisedRange() const {
    AppraisedRange result;
	result.setLowerRangeValue(ui->lowerBound->value());
	result.setUpperRangeValue(ui->upperBound->value());
	result.setResult(ui->result->text());
    return result;
}

void AddForm::onLowerBoundChanged(int value) {
    if(ui->upperBound->value() < value) {
        ui->upperBound->setValue(value);
    }
}

void AddForm::onUpperBoundChanged(int value) {
    if(ui->lowerBound->value() > value) {
        ui->lowerBound->setValue(value);
    }
}
