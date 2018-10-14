#pragma once

#include "Navigation/NavigationView.h"

#include "Entities/Entity/Entity.h"

class QAbstractItemModel;

namespace Ui {
class EntitiesForm;
}

class EntitiesForm : public NavigationView {
Q_OBJECT

public:
    EntitiesForm(const QString &title,
                 const QString &addButtonIconName,
                 const QString &addButtonToolTip,
                 QWidget *parent = nullptr);
    ~EntitiesForm() override;

    QAbstractItemModel *getModel() const;
    void setModel(QAbstractItemModel *model);

signals:
    void backButtonClicked();
    void addButtonClicked();
    void entityClicked(const QModelIndex &idx);
    void entityDoubleClicked(const QModelIndex &idx);

private:
    void setTitle(const QString &title);
    void setAddButtonIcon(const QString &iconName);
    void setAddButtonToolTip(const QString &toolTip);

    void resizeTable();

    Ui::EntitiesForm *ui;
};
