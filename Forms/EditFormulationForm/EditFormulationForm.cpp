#include "EditFormulationForm.h"
#include "ui_EditFormulationForm.h"

EditFormulationForm::EditFormulationForm(const QString &formulation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditFormulationForm)
{
    ui->setupUi(this);
    ui->formualation->setText(formulation);
    ui->formualation->setFocus();

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &EditFormulationForm::onEditingFinished);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &EditFormulationForm::deleteLater);
    connect(ui->formualation, &QLineEdit::editingFinished,
            this, &EditFormulationForm::onEditingFinished);
}

EditFormulationForm::~EditFormulationForm() {
    delete ui;
}

void EditFormulationForm::onEditingFinished() {
    emit editingFinished(ui->formualation->text());
    deleteLater();
}
