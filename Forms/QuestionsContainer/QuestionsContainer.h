#pragma once

#include "Entities/Question/Question.h"
#include "Forms/QuestionForm/QuestionForm.h"
#include "Forms/AnswerOptionsContainer/AnswerOptionsContainer.h"

namespace Ui {
class QuestionsContainer;
}

class QuestionsContainer : public QWidget {
    Q_OBJECT

signals:
    void answerOptionsVisibilityChanged(bool hidden);

public:
    explicit QuestionsContainer(Questions *questions,
                                QWidget *parent = nullptr);
    ~QuestionsContainer();

    void addQuestion(const Question &question);

public slots:
    void setAnswerOptionsHidden(bool hidden);


private slots:
    void onFormulationReturnPressed();
    void onAddQuestionClicked();
    void onQuestionDeleted(const QString &formulation);

private:
    void addQuestionForm(const uint &number, Question *question);
    Question makeQuestion() const;
    void connectNewQuestionToOld(QuestionForm *newQuestionForm);

    Questions *m_questions;
    bool m_hideAddForm;
    AnswerOptionsContainer *m_answerOptionsContainer;
    Ui::QuestionsContainer *ui;
};
