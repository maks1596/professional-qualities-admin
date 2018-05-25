#include "AnswerOptionForm.h"

#include <QVBoxLayout>

#include "Entities/AnswerOption/AnswerOption.h"
#include "Forms/FormulationForm/FormulationForm.h"

AnswerOptionForm::AnswerOptionForm(const uint &number,
                                   AnswerOption *answerOption,
                                   QWidget *parent) :
    QWidget(parent),
    m_answerOption(answerOption),
    m_formulationForm(new FormulationForm(number, ")", answerOption->getFormulation(), this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_formulationForm);

    connect(m_formulationForm, &FormulationForm::destroyed,
            this, &AnswerOptionForm::deleteLater);
    connect(m_formulationForm, &FormulationForm::formulationChanged,
            this, &AnswerOptionForm::onFormulationChanged);
    connect(m_formulationForm, &FormulationForm::formulationDeleted,
            this, &AnswerOptionForm::answerOptionDeleted);
}

void AnswerOptionForm::decreaseNumber() {
    m_formulationForm->decreaseNumber();
}

void AnswerOptionForm::onFormulationChanged(const QString &newFormulation) {
    m_answerOption->setFormulation(newFormulation);
}
