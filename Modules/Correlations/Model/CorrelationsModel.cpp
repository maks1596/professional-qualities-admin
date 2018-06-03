#include "CorrelationsModel.h"

//  :: Lifecycle ::

CorrelationsModel::CorrelationsModel(QObject *parent)
    : QAbstractTableModel(parent)
{ }

//  :: QAbstractTableModel ::

QVariant CorrelationsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Vertical) {
            if (section < rowCount()) {
                return getGroupsCorrelations()
                        .first()
                        .getCorrelationValues()
                        .at(section)
                        .getName();
            }
        } else {
            if (section < columnCount()) {
                return getGroupsCorrelations()
                        .at(section)
                        .getGroupName();
            }
        }
    }
    return section + 1;
}

int CorrelationsModel::rowCount(const QModelIndex &) const {
    return rowCount(getGroupsCorrelations());
}

int CorrelationsModel::columnCount(const QModelIndex &) const {
    return columnCount(getGroupsCorrelations());
}

QVariant CorrelationsModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    return getGroupsCorrelations()
            .at(index.column())
            .getCorrelationValues()
            .at(index.row())
            .getValue();
}

//  :: Public accessors ::

const QList<GroupCorrelations> &CorrelationsModel::getGroupsCorrelations() const {
    return m_groupsCorrelations;
}
void CorrelationsModel::setGroupsCorrelations(const QList<GroupCorrelations> &groupsCorrelations) {
    checkRowCount(groupsCorrelations);
    checkColumnCount(groupsCorrelations);
    m_groupsCorrelations = groupsCorrelations;
    emitAllDataChanged();
}

//  :: Private methods ::
inline
void CorrelationsModel::checkRowCount(const QList<GroupCorrelations> newGroupsCorrelations) {
    int oldRowCount = rowCount();
    int newRowCount = rowCount(newGroupsCorrelations);

    if (oldRowCount < newRowCount) {
        beginInsertRows(QModelIndex(), oldRowCount, newRowCount - 1);
        endInsertRows();
    } else if (oldRowCount > newRowCount) {
        beginRemoveRows(QModelIndex(), newRowCount, oldRowCount - 1);
        endRemoveRows();
    }
}

inline
void CorrelationsModel::checkColumnCount(const QList<GroupCorrelations> newGroupsCorrelations) {
    int oldColumnCount = columnCount();
    int newColumnCount = columnCount(newGroupsCorrelations);

    if (oldColumnCount < newColumnCount) {
        beginInsertColumns(QModelIndex(), oldColumnCount, newColumnCount - 1);
        endInsertColumns();
    } else if (oldColumnCount > newColumnCount) {
        beginRemoveColumns(QModelIndex(), newColumnCount, oldColumnCount - 1);
        endRemoveColumns();
    }
}

inline
int CorrelationsModel::rowCount(const QList<GroupCorrelations> groupsCorrelations) const {
    if (!groupsCorrelations.isEmpty()) {
        // Корреляции для всех групп одинаковые и в одинаковом количестве
        return groupsCorrelations.first().getCorrelationValues().size();
    }
    return 0;
}
inline
int CorrelationsModel::columnCount(const QList<GroupCorrelations> groupsCorrelations) const {
    return groupsCorrelations.size();
}

inline
void CorrelationsModel::emitAllDataChanged() {
    auto topLeft = index(0, 0);
    auto bottomRight = index(rowCount() - 1, columnCount() - 1);
    emit dataChanged(topLeft, bottomRight);
}
