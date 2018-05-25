#pragma once

#include <QWidget>
#include <QStringList>

#include "Entities/Question/Question.h"
#include "Forms/AddPartOfKeyForm/AddPartOfKeyForm.h"

class PartOfUniqueAnswerOptionsKey;

namespace Ui {
class AddUniqueAnswerOptonsPartOfKeyForm;
}

class AddUniqueAnswerOptonsPartOfKeyForm : public AddPartOfKeyForm {
Q_OBJECT

public:
    explicit AddUniqueAnswerOptonsPartOfKeyForm(Questions *questions,
                                                QWidget *parent = 0);
    ~AddUniqueAnswerOptonsPartOfKeyForm();

	PartOfUniqueAnswerOptionsKey &getPartOfKey();
	void setPartOfKey(const PartOfKey &partOfKey) override;

    void addAnswerOption(const uint &index);

    void updateAnswerOptions();
    void updateAnswerOption();
    void updateQuestionsAmount();


private slots:
    void onQuestionNumberChanged(const int &number);
    void onAnswerOptionChanged(const int &index);
    void onAddAnswerOptionClicked();
    void onDeleteAnswerOptionClicked();
    void onPointsChanged(int points);
    void onAddBtnClicked();

private:
    void clear();
    void deleteAnswerOption(const uint &index);
    void addAnswerOptionOnForm(const uint &index);

    QStringList makeAnswerOptions(const uint &count);
    void filterAnswerOptions(const uint max);

    Questions *m_questions;
    Ui::AddUniqueAnswerOptonsPartOfKeyForm *ui;
};
