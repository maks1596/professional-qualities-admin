#pragma once

#include <QWidget>
#include <QString>
#include <QTimer>

#include "Entities/Entity/Entity.h"

class QString;

namespace Ui {
class EntitiesForm;
}

class EntitiesForm : public QWidget {
Q_OBJECT

public:
	EntitiesForm(QWidget *parent = nullptr);
    ~EntitiesForm();

signals:
    void toMainMenuBtnClicked();
	void error(const QString &errorMessage);

public slots:
	virtual void update() = 0;

	void startUpdating();
	void stopUpdating();

protected slots:
    void showCriticalMessage(const QString &error);
    virtual void onAddBtnClicked() = 0;

protected:

	QList<Entity> getEntities() const;
	void setEntities(const QList<Entity> &entities);

	void setTitle(const QString &title);
	void setHeaderLabels(const QStringList &labels);
	void setContent(const QList<QStringList> &content);

    virtual void removeEntity(const int &id) = 0;
    virtual void editEntity(const int &id) = 0;

private slots:
    void onEntityClicked(const QModelIndex &idx);
    void onEntityPressed(const QModelIndex &idx);
    void onEntityDoubleClicked(const QModelIndex &idx);

	void onTimeout();

private:
	void setRowCount(uint count);
	void setRow(uint row, const QStringList &texts);
	void setItem(uint row, uint column, const QString &text);
    int getEntityID(const QModelIndex &idx) const;
	void resizeTable();
	int deleteColumnIndex() const;

	int m_selectedRow = -1;
	QTimer m_timer;
	QList<Entity> m_entites;
    Ui::EntitiesForm *ui;
};
