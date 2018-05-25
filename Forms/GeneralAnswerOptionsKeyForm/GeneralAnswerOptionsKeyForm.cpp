#include "GeneralAnswerOptionsKeyForm.h"
#include "ui_ScaleForm.h"

#include <QStringList>

#include "Entities/Key/GeneralAnswerOptions/PartOfKey/PartOfGeneralAnswerOptionsKey.h"
#include "Forms/AddGeneralAnswerOptionsPartOfKeyForm/AddGeneralAnswerOptionsPartOfKeyForm.h"

typedef AddGeneralAnswerOptionsPartOfKeyForm AddForm;
typedef GeneralAnswerOptionsKeyForm GAOKeyForm;

GAOKeyForm::GeneralAnswerOptionsKeyForm(Scale *scale,
                                        AnswerOptions *answerOptions,
                                        Questions *questions,
                                        QWidget *parent) :
    KeyForm(scale, questions, parent)
{
    m_answerOptions = answerOptions;
	configureKeyTable({"Вариант ответа", "Номера вопросов", "Баллы", ""});
    configureAddForm(new AddForm(m_answerOptions, m_questions, this));

    update();
}

void GAOKeyForm::addPartOfKeyOnForm(const PartOfKey &partOfKey) {
    uint insertRow = ui->key->rowCount();
    ui->key->setRowCount(insertRow + 1);

    ui->key->setItem(insertRow, ANSWER_OPTION, makeAnswerOption(partOfKey));
    ui->key->setItem(insertRow, QUESTION_NUMBERS, makeQuestionNumbers(partOfKey));
    ui->key->setItem(insertRow, POINTS, makePoints(partOfKey));
    ui->key->setItem(insertRow, DELETE_BTN, new QTableWidgetItem("Удалить"));
    ui->key->resizeColumnsToContents();
}

QTableWidgetItem *GAOKeyForm::makeAnswerOption(const PartOfKey &partOfKey) {
	uint answerOptionIndex = partOfKey.toPOGAOK()->getAnswerOptionIndex();
    QTableWidgetItem *result = nullptr;
    if(answerOptionIndex < (uint)m_answerOptions->count()) {
        auto formulation = m_answerOptions->at(answerOptionIndex).getFormulation();
        result = new QTableWidgetItem(formulation);
    } else {
        result = new QTableWidgetItem("*Ошибка!*");
    }
    return result;
}

QTableWidgetItem *GAOKeyForm::makeQuestionNumbers(const PartOfKey &partOfKey) {
    QStringList strList;
	for(auto questionIndex : partOfKey.toPOGAOK()->getQuestionIndexes()) {
        strList << QString::number(questionIndex + 1);
    }
    return new QTableWidgetItem(strList.join(", "));
}
