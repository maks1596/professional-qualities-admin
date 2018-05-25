#include "AddGeneralAnswerOptionsPartOfKeyForm.h"
#include "ui_AddGeneralAnswerOptionsPartOfKeyForm.h"

#include <QStringList>

#include "Entities/Key/GeneralAnswerOptions/PartOfKey/PartOfGeneralAnswerOptionsKey.h"

typedef AddGeneralAnswerOptionsPartOfKeyForm AddForm;

AddForm::AddGeneralAnswerOptionsPartOfKeyForm(AnswerOptions *answerOptions,
                                                    Questions *questions,
                                                    QWidget *parent) :
    AddPartOfKeyForm(parent),
    m_answerOptions(answerOptions),
    m_questions(questions),
    ui(new Ui::AddGeneralAnswerOptionsPartOfKeyForm)
{
    ui->setupUi(this);

    updateQuestionsAmount();
    updateAnswerOptions();
    clear();

    connect(ui->answerOption, SIGNAL(activated(QString)),
            SLOT(onAnswerOptionChanged(QString)));
    connect(ui->questionNumber, SIGNAL(valueChanged(int)),
            this, SLOT(onQuestionNumberChanged(int)));
    connect(ui->addQuestionNumberBtn, &QPushButton::clicked,
            this, &AddForm::onAddQuestionNumberClicked);
    connect(ui->deleteQuestionNumberBtn, &QPushButton::clicked,
            this, &AddForm::onDeleteQuestionNumberClicked);
    connect(ui->points, SIGNAL(valueChanged(int)),
            this, SLOT(onPointsChanged(int)));
    connect(ui->addPartOfKeyBtn, &QPushButton::clicked,
            this, &AddForm::onAddBtnClicked);

    onQuestionNumberChanged(1);
}

AddForm::~AddGeneralAnswerOptionsPartOfKeyForm() {
    delete ui;
}

void AddForm::updateAnswerOptions() {
    ui->answerOption->clear();

    QStringList items;
    for(const AnswerOption &answerOption : *m_answerOptions) {
        items << answerOption.getFormulation();
    }
    ui->answerOption->addItems(items);
}

void AddForm::updateQuestionsAmount() {
    ui->questionNumber->setMaximum(m_questions->count());
}

PartOfGeneralAnswerOptionsKey &AddForm::getPartOfKey() {
	return *m_partOfKey->toPOGAOK();
}

void AddForm::setPartOfKey(const PartOfKey &partOfKey) {
	m_partOfKey.reset(new PartOfKey(partOfKey));

    updateAnswerOption();
    updateQuestionNumbers();
    onQuestionNumberChanged(ui->questionNumber->value());
	ui->points->setValue(m_partOfKey->getPoints());
}

void AddForm::addQuestionNumber(const uint &questionNumber) {
    addQuestionIndex(questionNumber - 1);
}

void AddForm::addQuestionIndex(const uint &questionIndex) {
	getPartOfKey().addQuestionIndex(questionIndex);
    addQuestionIndexOnForm(questionIndex);
}

void AddForm::addQuestionIndexOnForm(const uint &questionIndex) {
    QString text = ui->questionNumbers->text();
    if(!text.isEmpty()) {
        text.append(", ");
    }
    text.append(QString::number(questionIndex + 1));
    ui->questionNumbers->setText(text);
}

void AddForm::updateAnswerOption() {
	uint answerOptionIndex = getPartOfKey().getAnswerOptionIndex();
    if(answerOptionIndex < (uint)ui->answerOption->count()) {
        auto formulation = m_answerOptions->at(answerOptionIndex).getFormulation();
        ui->answerOption->setCurrentText(formulation);
    } else {
        ui->answerOption->setCurrentIndex(0);
    }
}

void AddForm::updateQuestionNumbers() {
    ui->questionNumbers->clear();
	for(const uint &index : getPartOfKey().getQuestionIndexes()) {
        addQuestionIndexOnForm(index);
    }
}

void AddForm::onAnswerOptionChanged(const QString &answerOption) {
	m_partOfKey.reset(new PartOfGeneralAnswerOptionsKey());
    int index = m_answerOptions->indexOf(answerOption);
	getPartOfKey().setAnswerOptionIndex(index);
}

void AddForm::onAddQuestionNumberClicked() {
    addQuestionNumber(ui->questionNumber->value());
    onQuestionNumberChanged(ui->questionNumber->value());
}

void AddForm::onDeleteQuestionNumberClicked() {
    deleteQuestionIndex(ui->questionNumber->value() - 1);
    onQuestionNumberChanged(ui->questionNumber->value());
}

void AddForm::deleteQuestionIndex(const uint &index) {
	getPartOfKey().deleteQuestionIndex(index);
    updateQuestionNumbers();
}

void AddForm::onQuestionNumberChanged(int number) {
	auto questionIndexes = getPartOfKey().getQuestionIndexes();
	bool addBtnVisible = (questionIndexes.indexOf(number - 1) < 0);
    ui->addQuestionNumberBtn->setVisible(addBtnVisible);
    ui->deleteQuestionNumberBtn->setVisible(!addBtnVisible);
}

void AddForm::onPointsChanged(int points) {
	m_partOfKey->setPoints(points);
}

void AddForm::onAddBtnClicked() {
	emit editingFinished(PartOfKey(*m_partOfKey));
    clear();
}

void AddForm::clear() {
	ui->questionNumber->setValue(1);
	m_partOfKey.reset(new PartOfGeneralAnswerOptionsKey());
	setPartOfKey(*m_partOfKey);
}
