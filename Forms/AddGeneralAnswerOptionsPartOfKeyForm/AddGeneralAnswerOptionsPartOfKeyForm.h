#pragma once

#include <QWidget>

#include "Forms/AddPartOfKeyForm/AddPartOfKeyForm.h"
#include "Entities/AnswerOption/AnswerOption.h"
#include "Entities/Question/Question.h"

class PartOfGeneralAnswerOptionsKey;

namespace Ui {
class AddGeneralAnswerOptionsPartOfKeyForm;
}

class AddGeneralAnswerOptionsPartOfKeyForm : public AddPartOfKeyForm {
Q_OBJECT

public:
    explicit AddGeneralAnswerOptionsPartOfKeyForm(AnswerOptions *answerOptions,
                                                  Questions *questions,
                                                  QWidget *parent = 0);
    ~AddGeneralAnswerOptionsPartOfKeyForm();

	PartOfGeneralAnswerOptionsKey &getPartOfKey();
	virtual void setPartOfKey(const PartOfKey &partOfKey) override;

    void addQuestionNumber(const uint &questionNumber);
    void addQuestionIndex(const uint &questionIndex);

    void updateAnswerOptions();
    void updateAnswerOption();
    void updateQuestionsAmount();
    void updateQuestionNumbers();

private slots:
    void onAnswerOptionChanged(const QString &answerOption);
    void onQuestionNumberChanged(int number);
    void onAddQuestionNumberClicked();
    void onDeleteQuestionNumberClicked();
    void onPointsChanged(int points);
    void onAddBtnClicked();

private:
    void clear();
    void deleteQuestionIndex(const uint &index);
    void addQuestionIndexOnForm(const uint &questionIndex);

    AnswerOptions *m_answerOptions;
    Questions *m_questions;
    Ui::AddGeneralAnswerOptionsPartOfKeyForm *ui;
};
