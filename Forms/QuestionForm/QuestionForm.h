#pragma once

#include <QWidget>

#include "Entities/Question/Question.h"
#include "Forms/FormulationForm/FormulationForm.h"
#include "Forms/AnswerOptionsContainer/AnswerOptionsContainer.h"

class QuestionForm : public QWidget {
    Q_OBJECT

public:
    explicit QuestionForm(const uint& number,
                          Question *question,
                          QWidget *parent = 0);

signals:
    void questionDeleted(const QString &formulation);

public slots:
    void setAnswerOptionsHidden(bool hidden);
    void decreaseNumber();

private slots:
    void onFormulationChanged(const QString &newFormulation);

private:
    Question *m_question;
    FormulationForm *m_formulationForm;
    AnswerOptionsContainer *m_answerOptions;
};
