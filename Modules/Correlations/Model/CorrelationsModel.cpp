#include "CorrelationsModel.h"

#include "../Service/CorrelationsService.h"

//  :: Lifecycle ::

CorrelationsModel::CorrelationsModel(int testId, int scaleId, QObject *parent)
    : QAbstractTableModel(parent),
      m_testId(testId),
      m_scaleId(scaleId)
{ }

//  :: QAbstractTableModel ::

QVariant CorrelationsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
    case Qt::DisplayRole:
        return headerDataForDisplayRole(section, orientation);

    case Qt::ToolTipRole:
        return headerDataForToolTipRole(section, orientation);

    default:
        return QVariant();
    }
}

QVariant CorrelationsModel::headerDataForDisplayRole(int section, Qt::Orientation orientation) const {
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
    return QVariant();
}

QVariant CorrelationsModel::headerDataForToolTipRole(int section, Qt::Orientation orientation) const {
    if (orientation == Qt::Vertical) {
        if (section < rowCount()) {
            return getGroupsCorrelations()
                    .first()
                    .getCorrelationValues()
                    .at(section)
                    .getFullName();
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

int CorrelationsModel::getTestId() const {
    return m_testId;
}

int CorrelationsModel::getScaleId() const {
    return m_scaleId;
}

//  :: Service ::
CorrelationsService *CorrelationsModel::getService() const {
    return m_service;
}
void CorrelationsModel::setService(CorrelationsService *service) {
    m_service = service;

    connect(service, &CorrelationsService::defaultGroupsCorrelationsGot,
            this, &CorrelationsModel::setGroupsCorrelations);

    service->getDefaultGroupsCorrelations(getTestId(), getScaleId());
}

//  :: Groups correlations ::
const QList<GroupCorrelations> &CorrelationsModel::getGroupsCorrelations() const {
    return m_groupsCorrelations;
}
void CorrelationsModel::setGroupsCorrelations(const QList<GroupCorrelations> &groupsCorrelations) {
    beginResetModel();
    m_groupsCorrelations = groupsCorrelations;
    endResetModel();
}




