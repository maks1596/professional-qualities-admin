#include "EntitiesForm.h"
#include "ui_EntitiesForm.h"

#include <QMessageBox>

//  :: Conststants ::

const QString DELETE_HEADER_NAME = "Удалить";

const uint UPDATE_TIMING = 1000;

//  :: Lifecycle ::

EntitiesForm::EntitiesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntitiesForm)
{
    ui->setupUi(this);

    connect(ui->toMainMenuBtn, &QPushButton::clicked,
			[&](){ stopUpdating(); emit toMainMenuBtnClicked();});
    connect(ui->addBtn, &QPushButton::clicked,
			[&](){ stopUpdating(); onAddBtnClicked();});

	connect(ui->entitiesTableWidget, &QTableWidget::clicked,
            this, &EntitiesForm::onEntityClicked);
	connect(ui->entitiesTableWidget, &QTableView::doubleClicked,
            this, &EntitiesForm::onEntityDoubleClicked);

	connect(ui->entitiesTableWidget, &QTableView::pressed,
            this, &EntitiesForm::onEntityPressed);
	connect(ui->entitiesTableWidget, &QTableView::entered,
            this, &EntitiesForm::onEntityPressed);

	connect(&m_timer, &QTimer::timeout,
			this, &EntitiesForm::onTimeout);
	m_timer.start(UPDATE_TIMING);
}

EntitiesForm::~EntitiesForm() {
	delete ui;
}

//  :: Public slots ::

void EntitiesForm::startUpdating() {
	update();
	m_timer.start(UPDATE_TIMING);
}
void EntitiesForm::stopUpdating() {
	m_timer.stop();
}

//  :: Protected accessors ::

QList<Entity> EntitiesForm::getEntities() const {
	return m_entites;
}
void EntitiesForm::setEntities(const QList<Entity> &entities) {
	m_entites = entities;
}

//  :: Protected methods ::

void EntitiesForm::setTitle(const QString &title) {
    ui->title->setText(title);
}

void EntitiesForm::setHeaderLabels(const QStringList &labels) {
	QStringList actualHeaders(labels);
	actualHeaders.append(DELETE_HEADER_NAME);

	ui->entitiesTableWidget->setColumnCount(actualHeaders.size());
	ui->entitiesTableWidget->setHorizontalHeaderLabels(actualHeaders);
	resizeTable();
}

void EntitiesForm::setContent(const QList<QStringList> &content) {
	setRowCount(content.size());
	for (int i = 0; i < content.size(); ++i) {
		setRow(i, content.at(i));
	}
	resizeTable();
}

//  :: Protected slots ::

void EntitiesForm::showCriticalMessage(const QString &error) {
	QMessageBox::critical(this, "Ошибка", error);
}

//  :: Private slots ::

void EntitiesForm::onEntityDoubleClicked(const QModelIndex &idx) {
    if(idx.isValid()) {
		if(idx.column() != deleteColumnIndex()) {
			stopUpdating();
			editEntity(getEntityID(idx));
        }
    }
}

void EntitiesForm::onEntityPressed(const QModelIndex &idx) {
    if(idx.isValid()) {
        m_selectedRow = idx.row();
		ui->entitiesTableWidget->selectRow(m_selectedRow);
    } else {
        m_selectedRow = -1;
    }
}

void EntitiesForm::onEntityClicked(const QModelIndex &idx) {
    if(idx.isValid()) {
		if(idx.column() == deleteColumnIndex()) {
            removeEntity(getEntityID(idx));
        }
    } else {
        m_selectedRow = -1;
    }
}

void EntitiesForm::onTimeout() {
	update();
	if(m_selectedRow > -1) {
		ui->entitiesTableWidget->selectRow(m_selectedRow);
	} else {
		ui->entitiesTableWidget->clearSelection();
	}
}

//  :: Private methods

void EntitiesForm::setRowCount(uint count) {
	ui->entitiesTableWidget->setRowCount(count);
}

void EntitiesForm::setRow(uint row, const QStringList &texts) {
	for (int column = 0; column < texts.size(); ++column) {
		setItem(row, column, texts[column]);
	}
	setItem(row, texts.size(), DELETE_HEADER_NAME);
}

void EntitiesForm::setItem(uint row, uint column, const QString &text) {
	ui->entitiesTableWidget->setItem(row, column, new QTableWidgetItem(text));
}

inline
int EntitiesForm::getEntityID(const QModelIndex &idx) const {
    if (!idx.isValid()) { return 0; }
	return m_entites.at(idx.row()).getId();
}

inline
void EntitiesForm::resizeTable() {
	ui->entitiesTableWidget->resizeColumnsToContents();
	ui->entitiesTableWidget->horizontalHeader()
				->setSectionResizeMode(0, QHeaderView::Stretch);
}

inline
int EntitiesForm::deleteColumnIndex() const {
	return ui->entitiesTableWidget->columnCount() - 1;
}
