#include "AddUniqueAnswerOptonsPartOfKeyForm.h"
#include "ui_AddUniqueAnswerOptonsPartOfKeyForm.h"

#include "Entities/Key/UniqueAnswerOptions/PartOfKey/PartOfUniqueAnswerOptionsKey.h"

typedef AddUniqueAnswerOptonsPartOfKeyForm AddForm;

AddForm::AddUniqueAnswerOptonsPartOfKeyForm(Questions *questions,
                                            QWidget *parent) :
    AddPartOfKeyForm(parent),
    m_questions(questions),
    ui(new Ui::AddUniqueAnswerOptonsPartOfKeyForm)
{
    ui->setupUi(this);

    updateQuestionsAmount();
    updateAnswerOptions();
    clear();

    connect(ui->questionNumber, SIGNAL(valueChanged(int)),
            this, SLOT(onQuestionNumberChanged(int)));
    connect(ui->answerOption, SIGNAL(currentIndexChanged(int)),
            SLOT(onAnswerOptionChanged(int)));
    connect(ui->addAnswerOptionBtn, &QPushButton::clicked,
            this, &AddForm::onAddAnswerOptionClicked);
    connect(ui->deleteAnswerOptionBtn, &QPushButton::clicked,
            this, &AddForm::onDeleteAnswerOptionClicked);
    connect(ui->points, SIGNAL(valueChanged(int)),
            this, SLOT(onPointsChanged(int)));
    connect(ui->addPartOfKeyBtn, &QPushButton::clicked,
            this, &AddForm::onAddBtnClicked);

    onAnswerOptionChanged(0);
}

AddForm::~AddUniqueAnswerOptonsPartOfKeyForm() {
    delete ui;
}

void AddForm::onQuestionNumberChanged(const int &number) {
	uint oldQuestion = getPartOfKey().getQuestionIndex();
    uint oldAnswerOptionsAmount = m_questions->value(oldQuestion).getAnswerOptions()->size();
    uint newAnswerOptionsAmount = m_questions->value(number - 1).getAnswerOptions()->size();

	getPartOfKey().setQuestionIndex(static_cast<uint>(number - 1));
    if(oldAnswerOptionsAmount != newAnswerOptionsAmount) {
        updateAnswerOption();
        if(oldAnswerOptionsAmount > newAnswerOptionsAmount) {
            filterAnswerOptions(newAnswerOptionsAmount);
            updateAnswerOptions();
        }
    }
}

void AddForm::filterAnswerOptions(const uint max) {
    Indexes filtered;
	for(const auto &cur : getPartOfKey().getAnswerOptionIndexes()) {
        if(cur < max) {
            filtered.append(cur);
        }
    }
	getPartOfKey().setAnswerOptionIndexes(filtered);
}

QStringList AddForm::makeAnswerOptions(const uint &count) {
    QStringList result;
    for(uint i = 0; i < count; i++) {
        result << QString('a' + i);
    }
    return result;
}

void AddForm::updateQuestionsAmount() {
    ui->questionNumber->setMaximum(m_questions->count());
}

PartOfUniqueAnswerOptionsKey &AddForm::getPartOfKey() {
	return *m_partOfKey->toPOUAOK();
}

void AddForm::setPartOfKey(const PartOfKey &partOfKey) {
	m_partOfKey.reset(new PartOfKey(partOfKey));

	ui->questionNumber->setValue(getPartOfKey().getQuestionIndex() + 1);
    updateAnswerOptions();
    updateAnswerOption();
    onAnswerOptionChanged(ui->answerOption->currentIndex());
	ui->points->setValue(m_partOfKey->getPoints());
}

void AddForm::updateAnswerOptions() {
    ui->answerOptions->clear();
	for(const uint &index : getPartOfKey().getAnswerOptionIndexes()) {
        addAnswerOptionOnForm(index);
    }
}

void AddForm::addAnswerOption(const uint &index) {
	getPartOfKey().addAnswerOptionIndex(index);
    addAnswerOptionOnForm(index);
}

void AddForm::addAnswerOptionOnForm(const uint &index) {
    QString text = ui->answerOptions->text();
    if(!text.isEmpty()) {
        text.append(", ");
    }
    text.append(QString('a' + index));
    ui->answerOptions->setText(text);
}

void AddForm::updateAnswerOption() {
    ui->answerOption->clear();
	auto questionIndex = getPartOfKey().getQuestionIndex();
    auto curQuestion = m_questions->at(questionIndex);
    auto answerOptions = curQuestion.getAnswerOptions();
    auto formAnswerOptions = makeAnswerOptions(answerOptions->count());
    ui->answerOption->addItems(formAnswerOptions);
}

void AddForm::onAnswerOptionChanged(const int &index) {
	bool addBtnVisible = (getPartOfKey().getAnswerOptionIndexes()
						  .indexOf(index) < 0);
    ui->addAnswerOptionBtn->setVisible(addBtnVisible);
    ui->deleteAnswerOptionBtn->setVisible(!addBtnVisible);
}

void AddForm::onAddAnswerOptionClicked() {
    addAnswerOption(ui->answerOption->currentIndex());
    onAnswerOptionChanged(ui->answerOption->currentIndex());
}

void AddForm::onDeleteAnswerOptionClicked() {
    deleteAnswerOption(ui->answerOption->currentIndex());
    onAnswerOptionChanged(ui->answerOption->currentIndex());
}

void AddForm::deleteAnswerOption(const uint &index) {
	getPartOfKey().deleteAnswerOptionIndex(index);
    updateAnswerOptions();
}

void AddForm::onPointsChanged(int points) {
	m_partOfKey->setPoints(points);
}

void AddForm::onAddBtnClicked() {
	emit editingFinished(PartOfKey(*m_partOfKey));
    clear();
}

void AddForm::clear() {
	m_partOfKey.reset(new PartOfUniqueAnswerOptionsKey());
	setPartOfKey(*m_partOfKey);
}
