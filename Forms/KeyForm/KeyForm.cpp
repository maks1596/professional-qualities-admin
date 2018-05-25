#include "KeyForm.h"

#include "ui_ScaleForm.h"

#include "Entities/Key/Key.h"
#include "Entities/Scale/Scale.h"

typedef AddPartOfKeyForm AddForm;

KeyForm::KeyForm(Scale *scale,
                 Questions *questions,
                 QWidget *parent) :
    QWidget(parent),
    m_scale(scale),
    m_key(scale->getKey()),
    m_questions(questions),
    ui(new Ui::ScaleForm)
{
    ui->setupUi(this);

    connect(ui->deleteBtn, &QPushButton::clicked,
            this, &KeyForm::onDeleteBtnClicked);
}

KeyForm::~KeyForm() {
    delete ui;
}

void KeyForm::configureKeyTable(const QStringList &labels) {
    ui->key->setColumnCount(COLUMNS_AMOUNT);
    ui->key->setHorizontalHeaderLabels(labels);

    connect(ui->key, &QTableWidget::cellDoubleClicked,
            this, &KeyForm::onKeyDoubleClicked);
    connect(ui->key, &QTableWidget::cellClicked,
            [&](int i, int j) { if(j == DELETE_BTN) deletePartOfKeyAt(i); });
}

void KeyForm::configureAddForm(AddPartOfKeyForm *addForm) {
    m_addForm = addForm;
    connect(m_addForm, &AddForm::editingFinished,
            this, &KeyForm::addPartOfKey);
    ui->addFormLayout->addWidget(m_addForm);
}

void KeyForm::update() {
    ui->key->clearContents();
    ui->key->setRowCount(0);
    ui->scaleName->setText(m_scale->getName());
	for (uint i = 0; i < m_key->amountOfParts(); ++i) {
		addPartOfKeyOnForm(m_key->at(i));
	}
}

void KeyForm::onDeleteBtnClicked() {
    emit scaleDeleted(m_scale->getName());
    deleteLater();
}

void KeyForm::onKeyDoubleClicked(int row) {
    m_addForm->setPartOfKey(m_key->at(row));
    deletePartOfKeyAt(row);
}

void KeyForm::addPartOfKey(const PartOfKey &partOfKey) {
	m_scale->getKey()->addPartOfKey(partOfKey);
	addPartOfKeyOnForm(partOfKey);
}

QTableWidgetItem *KeyForm::makePoints(const PartOfKey &partOfKey) {
	return new QTableWidgetItem(QString::number(partOfKey.getPoints()));
}

void KeyForm::deletePartOfKeyAt(uint index) {
	ui->key->removeRow(index);
	m_key->deletePartOfKey(index);
}
