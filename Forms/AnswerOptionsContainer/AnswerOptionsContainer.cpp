#include "AnswerOptionsContainer.h"
#include "ui_AnswerOptionsContainer.h"

AnswerOptionsContainer::AnswerOptionsContainer(AnswerOptions *answerOptions,
                                               bool hideAddForm,
                                               QWidget *parent) :
    QWidget(parent),
    m_answerOptions(answerOptions),
    m_hideAddForm(hideAddForm),
    ui(new Ui::AnswerOptionsContainer)
{
    ui->setupUi(this);

    connect(ui->addAnswerOptionBtn, &QPushButton::clicked,
            this, &AnswerOptionsContainer::onAddAnswerOptionBtnClicked);
    connect(ui->formulation, &QLineEdit::returnPressed,
            ui->addAnswerOptionBtn, &QPushButton::click);

    setAnswerOptions(m_answerOptions);
    setAddFormHidden(m_hideAddForm);
    setFocusProxy(ui->formulation);
}

AnswerOptionsContainer::~AnswerOptionsContainer() {
    delete ui;
}

void AnswerOptionsContainer::onAnswerOptionDeleted(const QString &formulation) {
    m_answerOptions->removeOne(formulation);
}

void AnswerOptionsContainer::onAddAnswerOptionBtnClicked() {
    if(!ui->formulation->text().isEmpty()) {
        addAnswerOption(ui->formulation->text());
        ui->formulation->clear();
    }
}

void AnswerOptionsContainer::addAnswerOption(const AnswerOption &answerOption) {
    m_answerOptions->append(answerOption);
	addAnswerOptionForm(m_answerOptions->size(),
						&m_answerOptions->back());
}

void AnswerOptionsContainer::addAnswerOptionForm(const uint &number,
                                                 AnswerOption *answerOption) {
    auto answerOptionForm = new AnswerOptionForm(number, answerOption, this);
    connectNewAnswerOptionToOld(answerOptionForm);
    connect(answerOptionForm, &AnswerOptionForm::answerOptionDeleted,
            this, &AnswerOptionsContainer::onAnswerOptionDeleted);

    ui->answerOptions->addWidget(answerOptionForm);
}

void AnswerOptionsContainer::connectNewAnswerOptionToOld(AnswerOptionForm *newAnswerOption) {
    for(int i = 0; i < ui->answerOptions->count(); i++) {
        AnswerOptionForm *old = (AnswerOptionForm *)ui->answerOptions->itemAt(i)->widget();
        connect(old, &AnswerOptionForm::destroyed,
                newAnswerOption, &AnswerOptionForm::decreaseNumber);
    }
}

bool AnswerOptionsContainer::event(QEvent *event)  {
    if(m_hideAddForm) {
        if (event->type() == QEvent::Enter)  {
            setAddFormHidden(false);
        } else if (event->type()==QEvent::Leave) {
            if(ui->formulation->text().isEmpty()) {
                setAddFormHidden(true);
            }
        }
    }
    return QWidget::event(event);
}

inline
void AnswerOptionsContainer::setAddFormHidden(bool hidden) {
    ui->addAnswerOptionBtn->setHidden(hidden);
    ui->formulation->setHidden(hidden);
    ui->onHiddenAndEmptyListMessage->setVisible(hidden && m_answerOptions->isEmpty());
}

AnswerOptions *AnswerOptionsContainer::getAnswerOptions() {
    return m_answerOptions;
}

AnswerOptions AnswerOptionsContainer::copyAnswerOptions() {
    return *m_answerOptions;
}

void AnswerOptionsContainer::setAnswerOptions(AnswerOptions *answerOptions) {
    m_answerOptions = answerOptions;
    deleteAnswerOptionForms();

    uint counter = 1;
    for(AnswerOption &cur : *answerOptions) {
        addAnswerOptionForm(counter++, &cur);
    }
}

void AnswerOptionsContainer::clear() {
    deleteAnswerOptionForms();
    ui->formulation->clear();
    m_answerOptions->clear();
}

void AnswerOptionsContainer::deleteAnswerOptionForms() {
    for(int i = 0; i < ui->answerOptions->count(); i++) {
        ui->answerOptions->itemAt(i)->widget()->deleteLater();
    }
}
