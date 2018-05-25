#include "ScalesContainer.h"
#include "ui_ScalesContainer.h"

#include <algorithm>
using namespace std;

#include "Entities/Test/Test.h"
#include "Forms/GeneralAnswerOptionsKeyForm/GeneralAnswerOptionsKeyForm.h"
#include "Forms/UniqueAnswerOptionsKeyForm/UniqueAnswerOptionsKeyForm.h"

typedef GeneralAnswerOptionsKeyForm GAOKeyForm;
typedef UniqueAnswerOptionsKeyForm UAOKeyForm;

ScalesContainer::ScalesContainer(Test *test, QWidget *parent) :
    QWidget(parent),
    m_test(test),
    m_scales(test->getScales()),
    ui(new Ui::ScalesContainer)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
    connect(ui->scaleName, &QLineEdit::returnPressed,
            ui->addScalesBtn, &QPushButton::click);
    connect(ui->addScalesBtn, &QPushButton::clicked,
            this, &ScalesContainer::onAddScaleBtnClicked);

    for(auto &scale : *m_scales) {
        addScaleOnForm(&scale);
    }
}

ScalesContainer::~ScalesContainer() {
    delete ui;
}

void ScalesContainer::onAddScaleBtnClicked() {
    if(addScale(ui->scaleName->text())) {
        ui->scaleName->clear();
    }
}

bool ScalesContainer::addScale(const QString &scaleName) {
    if(scaleName.isEmpty()) return false;

    auto iter = find_if(m_scales->begin(), m_scales->end(),
                        [&](const Scale &cur)
                        { return cur.getName() == scaleName; });
	if(iter == m_scales->end()) {
		m_scales->append(Scale(scaleName));
        addScaleOnForm(&m_scales->back());
    }

    return true;
}

void ScalesContainer::addScaleOnForm(Scale *scale) {
    KeyForm *keyForm = addScaleOnKeyForm(scale);
    EvaluationMapForm *evaluationMapForm = addScaleOnEvaluationMapForm(scale);

    connect(keyForm, &KeyForm::scaleDeleted,
            evaluationMapForm, &EvaluationMapForm::deleteLater);
    connect(evaluationMapForm, &EvaluationMapForm::scaleDeleted,
            keyForm, &KeyForm::deleteLater);
}

KeyForm *ScalesContainer::addScaleOnKeyForm(Scale *scale) {
    KeyForm *keyForm = nullptr;
    if (m_test->getAnswerOptionsType() == UNIQUE) {
        keyForm = addUniqueAnswerOptionsScaleForm(scale);
    } else {
        keyForm = addGeneralAnswerOptionsScaleForm(scale);
    }

    connect(keyForm, &KeyForm::scaleDeleted,
            this, &ScalesContainer::deleteScale);
    ui->key->layout()->addWidget(keyForm);

    return keyForm;
}

inline
KeyForm *ScalesContainer::addGeneralAnswerOptionsScaleForm(Scale *scale) {
    return new GAOKeyForm(scale, m_test->getGeneralAnswerOptions(),
                          m_test->getQuestions(), this);
}

inline
KeyForm *ScalesContainer::addUniqueAnswerOptionsScaleForm(Scale *scale) {
    return new UAOKeyForm(scale, m_test->getQuestions(), this);
}

EvaluationMapForm * ScalesContainer::addScaleOnEvaluationMapForm(Scale *scale) {
    EvaluationMapForm *evaluationMapForm = new EvaluationMapForm(scale, this);

    connect(evaluationMapForm, &EvaluationMapForm::scaleDeleted,
            this, &ScalesContainer::deleteScale);
    ui->evaluationMap->layout()->addWidget(evaluationMapForm);

    return evaluationMapForm;
}

void ScalesContainer::deleteScale(const QString &scaleName) {
    auto iter = find_if(m_scales->begin(), m_scales->end(),
                        [&](const Scale &cur)
                        { return cur.getName() == scaleName; });
    uint scaleIndex = (iter - m_scales->begin());
    m_scales->removeAt(scaleIndex);
}
