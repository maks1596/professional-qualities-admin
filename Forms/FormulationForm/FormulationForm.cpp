#include "FormulationForm.h"
#include "ui_FormulationForm.h"

#include <QMouseEvent>

FormulationForm::FormulationForm(const unsigned &number,
                                 const QString &separator,
                                 const QString &formulation,
                                 QWidget *parent) :
    QWidget(parent),
    m_separator(separator),
    m_editForm(nullptr),
    ui(new Ui::FormulationForm)
{
    ui->setupUi(this);
    setNumber(number);
    setFormulation(formulation);

    ui->deleteBtn->setFlat(true);
    connect(ui->deleteBtn, &QPushButton::clicked,
            this, &FormulationForm::onFormulationDeleted);
}

FormulationForm::~FormulationForm() {
    delete ui;
}

unsigned FormulationForm::getNumber() const {
    return m_number;
}

void FormulationForm::setNumber(const unsigned &number) {
    m_number = number;
    ui->number->setText(QString::number(m_number) + m_separator);
}

void FormulationForm::decreaseNumber() {
    setNumber(--m_number);
}

void FormulationForm::increaseNumber() {
    setNumber(++m_number);
}

QString FormulationForm::getFormulation() const {
    return ui->formulation->text();
}

void FormulationForm::setFormulation(const QString &formulation) {
    ui->formulation->setText(formulation);
}

void FormulationForm::mouseDoubleClickEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        toEditForm();
    }
}

void FormulationForm::toEditForm() {
    hideReadForm();
    showEditForm();
}

void FormulationForm::showEditForm() {
    m_editForm = new EditFormulationForm(ui->formulation->text(), this);
    layout()->addWidget(m_editForm);
    connect(m_editForm, &EditFormulationForm::editingFinished,
            this, &FormulationForm::onEditingFinished);
    connect(m_editForm, &EditFormulationForm::destroyed,
            this, &FormulationForm::showReadForm);
}

void FormulationForm::hideEditForm() {
    delete m_editForm;
}

void FormulationForm::showReadForm() {
    for(int i = 0; i < ui->readForm->count(); i++) {
        ui->readForm->itemAt(i)->widget()->show();
    }
}

void FormulationForm::hideReadForm() {
    for(int i = 0; i < ui->readForm->count(); i++) {
        ui->readForm->itemAt(i)->widget()->hide();
    }
}

void FormulationForm::onEditingFinished(const QString &newFormulation) {
    emit formulationChanged(newFormulation, ui->formulation->text());
    ui->formulation->setText(newFormulation);
    showReadForm();
}

void FormulationForm::onFormulationDeleted() {
    emit formulationDeleted(ui->formulation->text());
    deleteLater();
}

bool FormulationForm::event(QEvent *event)  {
    if (event->type() == QEvent::Enter)  {
        ui->deleteBtn->setFlat(false);
    } else if (event->type()==QEvent::Leave) {
        ui->deleteBtn->setFlat(true);
    }
    return QWidget::event(event);
}
