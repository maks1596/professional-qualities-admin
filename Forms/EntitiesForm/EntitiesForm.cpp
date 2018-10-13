#include "EntitiesForm.h"
#include "ui_EntitiesForm.h"

#include <QMessageBox>

//  :: Lifecycle ::

EntitiesForm::EntitiesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntitiesForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked,
            this, &EntitiesForm::backButtonClicked);
    connect(ui->addButton, &QPushButton::clicked,
            this, &EntitiesForm::addButtonClicked);

    connect(ui->entitiesTableView, &QTableView::clicked,
            this, &EntitiesForm::entityClicked);
    connect(ui->entitiesTableView, &QTableView::doubleClicked,
            this, &EntitiesForm::entityDoubleClicked);

    setTitle(getTitle());
    setAddButtonIcon(getAddButtonIconName());
    setAddButtonToolTip(getAddButtonToolTip());
}

EntitiesForm::~EntitiesForm() {
    delete ui;
}

//  :: Public methods ::

QAbstractItemModel *EntitiesForm::getModel() const {
    return ui->entitiesTableView->model();
}
void EntitiesForm::setModel(QAbstractItemModel *model) {
    ui->entitiesTableView->setModel(model);
}

//  :: Public slots ::

void EntitiesForm::showCriticalMessage(const QString &error) {
    QMessageBox::critical(this, "Ошибка", error);
}

//  :: Private methods ::

inline
void EntitiesForm::setTitle(const QString &title) {
    ui->titleLabel->setText(title);
}

inline
void EntitiesForm::setAddButtonIcon(const QString &iconName) {
    ui->addButton->setIcon(QIcon(iconName));
}

inline
void EntitiesForm::setAddButtonToolTip(const QString &toolTip) {
    ui->addButton->setToolTip(toolTip);
}

inline
void EntitiesForm::resizeTable() {
    ui->entitiesTableView->resizeColumnsToContents();
    ui->entitiesTableView->horizontalHeader()
				->setSectionResizeMode(0, QHeaderView::Stretch);
}
