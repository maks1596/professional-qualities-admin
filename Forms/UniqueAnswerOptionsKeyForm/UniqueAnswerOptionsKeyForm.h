#pragma once

#include "Forms/KeyForm/KeyForm.h"

class QWidget;

namespace Ui {
class ScaleForm;
}

class UniqueAnswerOptionsKeyForm : public KeyForm {
Q_OBJECT

signals:
    void scaleDeleted(const QString &scaleName);

public:
    explicit UniqueAnswerOptionsKeyForm(Scale *scale,
                                        Questions *questions,
                                        QWidget *parent = 0);
    ~UniqueAnswerOptionsKeyForm() {}

protected:
	void addPartOfKeyOnForm(const PartOfKey &partOfKey) override;

private:
	QTableWidgetItem *makeQuestionNumber(const PartOfKey &partOfKey);
	QTableWidgetItem *makeAnswerOptions(const PartOfKey &partOfKey);

    enum ColumnName {
        QUESTION_NUMBER,
        ANSWER_OPTIONS,
        POINTS
    };
};
