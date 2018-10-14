#include "UsersModel.h"

#include "Entities/User/User.h"

//  :: Constants ::

enum ColumnIndex {
    NAME_COLUMN_INDEX,
    GENDER_COLUMN_INDEX,
    AGE_COLUMN_INDEX,
    PROFESSION_COLUMN_INDEX,
    EXPERT_ASSESSMENT_COLUMN_INDEX,
    REMOVE_COLUMN_INDEX,
    COLUMNS_COUNT
};

//  :: Lifecycle ::

UsersModel::UsersModel(QObject *parent)
    : QAbstractTableModel(parent)
{ }

//  :: QAbstractTableModel ::

int UsersModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_users.size();
}

int UsersModel::columnCount(const QModelIndex &) const {
    return COLUMNS_COUNT;
}

QVariant UsersModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole && index.isValid()) {
        auto user = m_users[index.row()];

        switch (index.column()) {
        case NAME_COLUMN_INDEX:
            return user.getName().isEmpty() ? user.getLogin() : user.getName();
        case GENDER_COLUMN_INDEX:
            return user.getGenderString();
        case AGE_COLUMN_INDEX:
            return user.getAge();
        case PROFESSION_COLUMN_INDEX:
            return user.getProfession();
        case EXPERT_ASSESSMENT_COLUMN_INDEX:
            return user.getExpertAssessment();
        case REMOVE_COLUMN_INDEX:
            return "Удалить";
        }
    }
    return QVariant();
}

QVariant UsersModel::headerData(int section,
                                Qt::Orientation orientation,
                                int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case NAME_COLUMN_INDEX:
                return "Имя";
            case GENDER_COLUMN_INDEX:
                return "Пол";
            case AGE_COLUMN_INDEX:
                return "Возраст";
            case PROFESSION_COLUMN_INDEX:
                return "Профессия";
            case EXPERT_ASSESSMENT_COLUMN_INDEX:
                return "Оценка эксперта";
            }
        } else {
            return section + 1;
        }
    }
    return QVariant();
}

//  :: Public accessors ::

const QList<User> &UsersModel::getUsers() const {
    return m_users;
}
void UsersModel::setUsers(const QList<User> &users) {
    if (m_users.isEmpty()) {
        beginResetModel();
        m_users = users;
        endResetModel();
    } else {
        updateData(users);
    }
    emitAllDataChanged();
}

//  :: Public methods ::

User UsersModel::getUser(int index) const {
    if (index < m_users.size()) {
        return m_users[index];
    }
    return User();
}

int UsersModel::getUserId(int index) const {
    return getUser(index).getId();
}

int UsersModel::getRemoveColumnIndex() const {
    return REMOVE_COLUMN_INDEX;
}

//  :: Private methods ::

inline
void UsersModel::updateData(const QList<User> &users) {
    if (users.size() < m_users.size()) {
        beginRemoveRows(QModelIndex(), users.size(), m_users.size() - 1);
        m_users = users;
        endRemoveRows();
    } else if (users.size() > m_users.size()) {
        beginInsertRows(QModelIndex(), m_users.size(), users.size() - 1);
        m_users = users;
        endInsertRows();
    } else {
        m_users = users;
    }
}

inline
void UsersModel::emitAllDataChanged() {
    emit dataChanged(index(0, 0),
                     index(m_users.size() - 1,
                           COLUMNS_COUNT - 1));
}
