#include "QuestionForm.h"

#include <QVBoxLayout>

QuestionForm::QuestionForm(const uint &number,
                           Question *question,
                           QWidget *parent) :
    QWidget(parent),
    m_question(question),
    m_formulationForm(new FormulationForm(number, ".", question->getFormulation(), this)),
    m_answerOptions(new AnswerOptionsContainer(question->getAnswerOptions(), true, this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_formulationForm);
    layout->addWidget(m_answerOptions);

    connect(m_formulationForm, &FormulationForm::destroyed,
            this, &QuestionForm::deleteLater);
    connect(m_formulationForm, &FormulationForm::formulationChanged,
            this, &QuestionForm::onFormulationChanged);
    connect(m_formulationForm, &FormulationForm::formulationDeleted,
            this, &QuestionForm::questionDeleted);
}

void QuestionForm::decreaseNumber() {
    m_formulationForm->decreaseNumber();
}

void QuestionForm::setAnswerOptionsHidden(bool hidden) {
    m_answerOptions->setHidden(hidden);
}

void QuestionForm::onFormulationChanged(const QString &newFormulation) {
    m_question->setFormulation(newFormulation);
}
