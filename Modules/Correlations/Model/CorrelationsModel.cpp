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
    return QVariant();
}

int CorrelationsModel::rowCount(const QModelIndex &) const {
    if (!getGroupsCorrelations().isEmpty()) {
        // Корреляции для всех групп одинаковые и в одинаковом количестве
        return getGroupsCorrelations().first().getCorrelationValues().size();
    }
    return 0;
}

int CorrelationsModel::columnCount(const QModelIndex &) const {
    return getGroupsCorrelations().size();
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
    beginResetModel();
    m_groupsCorrelations = groupsCorrelations;
    endResetModel();
}
