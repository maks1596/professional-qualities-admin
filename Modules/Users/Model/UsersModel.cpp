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
            return user.getName();
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
                return "Название теста";
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
    m_users = users;
}

//  :: Public methods ::

User UsersModel::getUser(uint index) const {
    if (index < m_users.size()) {
        return m_users[index];
    }
    return User();
}

int UsersModel::getUserId(uint index) const {
    return getUser(index).getId();
}

int UsersModel::getRemoveColumnIndex() const {
    return REMOVE_COLUMN_INDEX;
}
