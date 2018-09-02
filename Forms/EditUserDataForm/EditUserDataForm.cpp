#include "EditUserDataForm.h"
#include "ui_EditUserDataForm.h"

EditUserDataForm::EditUserDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserDataForm)
{
    ui->setupUi(this);
}

EditUserDataForm::~EditUserDataForm()
{
    delete ui;
}
