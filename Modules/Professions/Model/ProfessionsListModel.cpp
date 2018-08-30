#include "ProfessionsListModel.h"

#include <QTimer>

#include "../Service/ProfessionsService.h"

//  :: Constants ::

const unsigned short UPDATE_TIMING = 5000;

//  :: Lifecycle ::

ProfessionsListModel::ProfessionsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    initTimer();
}

//  :: Abstract list implememntation ::

int ProfessionsListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_professions.size();
}


QVariant ProfessionsListModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        return m_professions[index.row()];
    }
    return QVariant();
}

//  :: Accessors ::
//  :: Service ::
ProfessionsService *ProfessionsListModel::getService() const {
    return m_service;
}
void ProfessionsListModel::setService(ProfessionsService *service) {
    m_service = service;

    connect(m_timer, &QTimer::timeout,
            m_service, &ProfessionsService::getProfessions);
    connect(m_service, &ProfessionsService::professionsGot,
            this, &ProfessionsListModel::setProfessions);
}

//  :: Professions ::
const QStringList &ProfessionsListModel::getProfessions() const {
    return m_professions;
}

//  :: Public methods ::

void ProfessionsListModel::startUpdating() {
    getService()->getProfessions();
    m_timer->start();
}
void ProfessionsListModel::stopUpdating() {
    m_timer->stop();
}

//  :: Private accessors ::
//  :: Professions ::
void ProfessionsListModel::setProfessions(const QStringList &professions) {
    if (m_professions.isEmpty()) {
        beginResetModel();
        m_professions = professions;
        endResetModel();
    } else {
        checkProfessionsCountChanged(professions);
        m_professions = professions;
        emitAllDataChanged();
    }
}

//  :: Private methods ::

inline
void ProfessionsListModel::initTimer() {
    m_timer = new QTimer(this);
    m_timer->setInterval(UPDATE_TIMING);
}

inline
void ProfessionsListModel::checkProfessionsCountChanged(const QStringList &newProfessions) {
    if (getProfessions().size() < newProfessions.size()) {
        beginInsertRows(QModelIndex(), rowCount(), newProfessions.size() - 1);
        endInsertRows();
    } else if (getProfessions().size() > newProfessions.size()) {
        beginRemoveRows(QModelIndex(), newProfessions.size(), rowCount() - 1);
        endRemoveRows();
    }
}

inline
void ProfessionsListModel::emitAllDataChanged() {
    auto topLeft = index(0, 0);
    auto bottomRight = index(rowCount() - 1, 0);
    emit dataChanged(topLeft, bottomRight);
}
