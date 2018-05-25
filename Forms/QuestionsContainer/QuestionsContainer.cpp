#include "QuestionsContainer.h"
#include "ui_QuestionsContainer.h"

#include <algorithm>
using namespace std;

QuestionsContainer::QuestionsContainer(Questions *questions,
                                       QWidget *parent) :
    QWidget(parent),
    m_questions(questions),
    m_answerOptionsContainer(new AnswerOptionsContainer(new AnswerOptions(), false, this)),
    ui(new Ui::QuestionsContainer)
{
    ui->setupUi(this);

    connect(ui->addQuestionBtn, &QPushButton::clicked,
            this, &QuestionsContainer::onAddQuestionClicked);
    connect(ui->formulation, &QLineEdit::returnPressed,
            this, &QuestionsContainer::onFormulationReturnPressed);

    ui->answerOptionsContainerLayout->addWidget(m_answerOptionsContainer);
    connect(this, &QuestionsContainer::answerOptionsVisibilityChanged,
            m_answerOptionsContainer, &AnswerOptionsContainer::setHidden);

    uint counter = 1;
    for(auto &question : *m_questions) {
        addQuestionForm(counter++, &question);
    }
}

QuestionsContainer::~QuestionsContainer() {
    delete ui;
}

void QuestionsContainer::onAddQuestionClicked() {
    addQuestion(makeQuestion());
    ui->formulation->clear();
    m_answerOptionsContainer->clear();
}

Question QuestionsContainer::makeQuestion() const {
    Question result;
    result.setFormulation(ui->formulation->text());

    if(m_answerOptionsContainer->isVisible()) {
        result.setAnswerOptions(m_answerOptionsContainer->copyAnswerOptions());
    }

    return result;
}

void QuestionsContainer::addQuestion(const Question &question) {
    m_questions->append(question);
    addQuestionForm(m_questions->size(), &m_questions->back());
}

void QuestionsContainer::addQuestionForm(const uint &number, Question *question) {
    auto questionForm = new QuestionForm(number, question, this);
    questionForm->setAnswerOptionsHidden(m_answerOptionsContainer->isHidden());

    connectNewQuestionToOld(questionForm);
    connect(this, &QuestionsContainer::answerOptionsVisibilityChanged,
            questionForm, &QuestionForm::setAnswerOptionsHidden);
    connect(questionForm, &QuestionForm::questionDeleted,
            this, &QuestionsContainer::onQuestionDeleted);

    ui->questions->addWidget(questionForm);
}

void QuestionsContainer::connectNewQuestionToOld(QuestionForm *newQuestionForm) {
    for(int i = 0; i < ui->questions->count(); i++) {
        QuestionForm *old = (QuestionForm *)ui->questions->itemAt(i)->widget();
        connect(old, &QuestionForm::destroyed,
                newQuestionForm, &QuestionForm::decreaseNumber);
    }
}

void QuestionsContainer::setAnswerOptionsHidden(bool hidden) {
    emit answerOptionsVisibilityChanged(hidden);
}

void QuestionsContainer::onQuestionDeleted(const QString &formulation) {
    auto iter = find_if(m_questions->begin(), m_questions->end(),
                        [&](const Question &q)
                        { return q.getFormulation() == formulation; });
    m_questions->removeAt(iter - m_questions->begin());
}

void QuestionsContainer::onFormulationReturnPressed() {
    if(m_answerOptionsContainer->isVisible()) {
        m_answerOptionsContainer->setFocus();
    } else {
        onAddQuestionClicked();
    }
}
