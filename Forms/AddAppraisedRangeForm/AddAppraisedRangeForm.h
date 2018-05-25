#pragma once

#include <QWidget>

namespace Ui {
class AddAppraisedRangeForm;
}

class AppraisedRange;

class AddAppraisedRangeForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddAppraisedRangeForm(QWidget *parent = 0);
    ~AddAppraisedRangeForm();

	void setAppraisedRange(const AppraisedRange &appraisedRange);
    AppraisedRange getAppraisedRange() const;

signals:
    void editingFinished(const AppraisedRange &range);

private slots:
    void onAddBtnClicked();
    void onLowerBoundChanged(int value);
    void onUpperBoundChanged(int value);

private:
    AppraisedRange makeAppraisedRange() const;

    Ui::AddAppraisedRangeForm *ui;
};
