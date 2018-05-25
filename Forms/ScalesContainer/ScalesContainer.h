#pragma once

#include <QWidget>

#include "Entities/Scale/Scale.h"
#include "Forms/KeyForm/KeyForm.h"
#include "Forms/EvaluationMapForm/EvaluationMapForm.h"

namespace Ui {
class ScalesContainer;
}

class Test;

class ScalesContainer : public QWidget {
Q_OBJECT

public:
    explicit ScalesContainer(Test *test, QWidget *parent = 0);
    ~ScalesContainer();

private slots:
    void onAddScaleBtnClicked();

private:
    bool addScale(const QString &scaleName);
    void addScaleOnForm(Scale *scale);
    KeyForm *addScaleOnKeyForm(Scale *scale);
    KeyForm *addGeneralAnswerOptionsScaleForm(Scale *scale);
    KeyForm *addUniqueAnswerOptionsScaleForm(Scale *scale);
    EvaluationMapForm *addScaleOnEvaluationMapForm(Scale *scale);
    void deleteScale(const QString &scaleName);

    Test *m_test;
    Scales *m_scales;
    Ui::ScalesContainer *ui;
};
