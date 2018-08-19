#include "UserRoleModel.h"

#include "../UserRole.h"

UserRoleModel::UserRoleModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int UserRoleModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return static_cast<int>(UserRole::AmountOfRoles);
}

QVariant UserRoleModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        auto indexRow = index.row();
        auto userRole = static_cast<UserRole>(indexRow);
        return userRoleToString(userRole);
    }

    return QVariant();
}
