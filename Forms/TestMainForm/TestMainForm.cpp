#include "TestMainForm.h"
#include "ui_TestMainForm.h"

#include "Entities/Test/Test.h"
#include "Forms/AnswerOptionsContainer/AnswerOptionsContainer.h"
#include "Forms/QuestionsContainer/QuestionsContainer.h"

TestMainForm::TestMainForm(Test *test,
                           QWidget *parent) :
    QWidget(parent),
    m_test(test),
    ui(new Ui::TestMainForm)
{
    ui->setupUi(this);

    configureName();
    configureInstruction();
    configureGeneralAnswerOptions();
    configureQuestions();

    configureAnswerOptionsType();
    setAnswerOptionsTypeEditable(true);
}

TestMainForm::~TestMainForm() {
    delete ui;
}

void TestMainForm::onAnswerOptionsTypeToggled(bool checked) {
    m_test->setAnswerOptionsType(checked? GENERAL: UNIQUE);
}

void TestMainForm::onNameEditingFinished() {
    if(!ui->name->text().isEmpty()) {
        m_test->setName(ui->name->text());
    } else {
        ui->name->setText(m_test->getName());
    }
}

void TestMainForm::onInstructionTextChanged() {
    m_test->setInstruction(ui->instruction->document()->toPlainText());
}

void TestMainForm::setAnswerOptionsTypeEditable(bool editable) {
    bool answerOptionTypeNotUnique = m_test->getAnswerOptionsType() != UNIQUE;
    ui->answerOptionsType->setVisible(editable);
    ui->answerOptionsLabel->setVisible(!editable &&
                                       answerOptionTypeNotUnique);
}

inline
void TestMainForm::configureName() {
    ui->name->setText(m_test->getName());
    connect(ui->name,  &QLineEdit::editingFinished,
            this, &TestMainForm::onNameEditingFinished);
}

inline
void TestMainForm::configureInstruction() {
    ui->instruction->setText(m_test->getInstruction());
    connect(ui->instruction, &QTextEdit::textChanged,
            this, &TestMainForm::onInstructionTextChanged);
}

inline
void TestMainForm::configureGeneralAnswerOptions() {
    AnswerOptionsContainer *answerOptions = new AnswerOptionsContainer(m_test->getGeneralAnswerOptions(),
                                                                       false, this);
    ui->generalAnswerOptionsLayout->addWidget(answerOptions);
    connect(ui->answerOptionsType, &QCheckBox::toggled,
            answerOptions, &AnswerOptionsContainer::setVisible);

    answerOptions->setVisible(m_test->getAnswerOptionsType() != UNIQUE);
}

inline
void TestMainForm::configureQuestions() {
    QuestionsContainer *questions = new QuestionsContainer(m_test->getQuestions(), this);
    ui->questionsLayout->addWidget(questions);
    connect(ui->answerOptionsType, &QCheckBox::toggled,
            questions, &QuestionsContainer::setAnswerOptionsHidden);
}

inline
void TestMainForm::configureAnswerOptionsType() {
    ui->answerOptionsType->setChecked(m_test->getAnswerOptionsType() != UNIQUE);
    connect(ui->answerOptionsType, &QCheckBox::toggled,
            this, &TestMainForm::onAnswerOptionsTypeToggled);
}
