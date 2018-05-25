#include "UniqueAnswerOptionsKeyForm.h"
#include "ui_ScaleForm.h"

#include "Entities/Key/UniqueAnswerOptions/PartOfKey/PartOfUniqueAnswerOptionsKey.h"
#include "Forms/AddUniqueAnswerOptonsPartOfKeyForm/AddUniqueAnswerOptonsPartOfKeyForm.h"

typedef AddUniqueAnswerOptonsPartOfKeyForm AddForm;
typedef UniqueAnswerOptionsKeyForm UAOKeyForm;

UAOKeyForm::UniqueAnswerOptionsKeyForm(Scale *scale,
                                       Questions *questions,
                                       QWidget *parent) :
    KeyForm(scale, questions, parent)
{
	configureKeyTable({"Номер вопроса", "Варианты ответов","Баллы", ""});
    configureAddForm(new AddForm(m_questions, this));

    update();
}

void UAOKeyForm::addPartOfKeyOnForm(const PartOfKey &partOfKey) {
    uint insertRow = ui->key->rowCount();
    ui->key->setRowCount(insertRow + 1);

    ui->key->setItem(insertRow, QUESTION_NUMBER, makeQuestionNumber(partOfKey));
    ui->key->setItem(insertRow, ANSWER_OPTIONS, makeAnswerOptions(partOfKey));
    ui->key->setItem(insertRow, POINTS, makePoints(partOfKey));
    ui->key->setItem(insertRow, DELETE_BTN, new QTableWidgetItem("Удалить"));
    ui->key->resizeColumnsToContents();
}

QTableWidgetItem *UAOKeyForm::makeQuestionNumber(const PartOfKey &partOfKey) {
	uint questionIndex = partOfKey.toPOUAOK()->getQuestionIndex();
    if(questionIndex < (uint)m_questions->count()) {
        return new QTableWidgetItem(QString::number(questionIndex + 1));
    } else {
        return new QTableWidgetItem("*Ошибка!*");
    }
}

QTableWidgetItem *UAOKeyForm::makeAnswerOptions(const PartOfKey &partOfKey) {
    QStringList indexes;
	for(const uint &answerOptionIndex : partOfKey.toPOUAOK()->getAnswerOptionIndexes()) {
        indexes << QString('a' + answerOptionIndex);
    }
    return new QTableWidgetItem(indexes.join(", "));
}
