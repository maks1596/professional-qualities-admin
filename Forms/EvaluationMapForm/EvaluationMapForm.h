#pragma once

#include <QTableWidgetItem>
#include <QWidget>

#include "Entities/Range/Range.h"

namespace Ui {
class ScaleForm;
}

class AddAppraisedRangeForm;
class AppraisedRange;
class EvaluationMap;
class Scale;

class EvaluationMapForm : public QWidget {
	Q_OBJECT

public:
    explicit EvaluationMapForm(Scale *scale, QWidget *parent = 0);
    ~EvaluationMapForm();

signals:
    void scaleDeleted(const QString &scaleName);

public slots:
    void update();

private slots:
    void onDeleteBtnClicked();
    void onRangeDoubleClicked(int row);

private:
    void configureAddForm();
    void configureTable();

	void addAppraisedRange(const AppraisedRange &appraisedRange);
	void addAppraisedRangeOnForm(const AppraisedRange &appraisedRange);

    QTableWidgetItem *makeRange(const Range &range) const;

    void deleteRangeAt(const uint index);

    enum ColumnName {
        RANGE,
        RESULT,
        DELETE_BTN,
        COLUMNS_AMOUNT
    };

    Scale *m_scale;
    EvaluationMap *m_evaluationMap;
    AddAppraisedRangeForm *m_addForm;
    Ui::ScaleForm *ui;
};
