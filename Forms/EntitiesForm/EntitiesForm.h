#pragma once

#include <QWidget>
#include <QString>
#include <QTimer>

#include "Entities/Entity/Entity.h"

class QAbstractItemModel;
class QString;

namespace Ui {
class EntitiesForm;
}

class EntitiesForm : public QWidget {
Q_OBJECT

public:
    EntitiesForm(QWidget *parent = nullptr);
    ~EntitiesForm() override;

    QAbstractItemModel *getModel() const;
    void setModel(QAbstractItemModel *model);

public slots:
    void showCriticalMessage(const QString &error);

signals:
    void backButtonClicked();
    void addButtonClicked();
    void entityClicked(const QModelIndex &idx);
    void entityDoubleClicked(const QModelIndex &idx);

protected:
    virtual QString getTitle() const = 0;
    virtual QString getAddButtonIconName() const = 0;
    virtual QString getAddButtonToolTip() const = 0;

private:
    void setTitle(const QString &title);
    void setAddButtonIcon(const QString &iconName);
    void setAddButtonToolTip(const QString &toolTip);

    void resizeTable();

    Ui::EntitiesForm *ui;
};
