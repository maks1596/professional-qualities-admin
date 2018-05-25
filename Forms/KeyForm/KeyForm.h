#pragma once

#include <QWidget>
#include <QStringList>
#include <QTableWidgetItem>

#include "Entities/Question/Question.h"
#include "Forms/AddPartOfKeyForm/AddPartOfKeyForm.h"

class Scale;
class Key;

namespace Ui {
class ScaleForm;
}

class KeyForm : public QWidget {
   Q_OBJECT

public:
    explicit KeyForm(Scale *scale,
                     Questions *questions,
                     QWidget *parent = 0);
    ~KeyForm();

signals:
    void scaleDeleted(const QString &scaleName);

public slots:
    void update();

protected slots:
    void onDeleteBtnClicked();
    void onKeyDoubleClicked(int row);

protected:
    void configureAddForm(AddPartOfKeyForm *addForm);
    void configureKeyTable(const QStringList &labels);

	void addPartOfKey(const PartOfKey &partOfKey);
	virtual void addPartOfKeyOnForm(const PartOfKey &partOfKey) = 0;

	void deletePartOfKeyAt(uint index);

	QTableWidgetItem *makePoints(const PartOfKey &partOfKey);

    Scale *m_scale;
    Key *m_key;
    Questions *m_questions;
    AddPartOfKeyForm *m_addForm;
    Ui::ScaleForm *ui;

    const char DELETE_BTN = 3;
    const char COLUMNS_AMOUNT = 4;
};
