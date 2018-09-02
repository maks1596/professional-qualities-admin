#include "EditUserView.h"
#include "ui_EditUserView.h"

EditUserView::EditUserView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserView)
{
    ui->setupUi(this);
}

EditUserView::~EditUserView()
{
    delete ui;
}
