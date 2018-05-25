#pragma once

#include <QWidget>
#include <QTableWidgetItem>

#include "Entities/AnswerOption/AnswerOption.h"
#include "Forms/KeyForm/KeyForm.h"

class GeneralAnswerOptionsKeyForm : public KeyForm {
Q_OBJECT

public:
    explicit GeneralAnswerOptionsKeyForm(Scale *scale,
                                         AnswerOptions *answerOptions,
                                         Questions *questions,
                                         QWidget *parent = 0);
    ~GeneralAnswerOptionsKeyForm() {}

protected:
	virtual void addPartOfKeyOnForm(const PartOfKey &partOfKey) override;

private:
	QTableWidgetItem *makeAnswerOption(const PartOfKey &partOfKey);
	QTableWidgetItem *makeQuestionNumbers(const PartOfKey &partOfKey);

    enum ColumnName {
        ANSWER_OPTION,
        QUESTION_NUMBERS,
        POINTS
    };

    AnswerOptions *m_answerOptions;
};
