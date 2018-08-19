#ifndef USERROLEMODEL_H
#define USERROLEMODEL_H

#include <QAbstractListModel>

class UserRoleModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit UserRoleModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // USERROLEMODEL_H