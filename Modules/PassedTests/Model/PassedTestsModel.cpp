#include "PassedTestsModel.h"

#include <QTimer>

#include "../Service/PassedTestsService.h"
#include "Entities/Statistics/PassedTestPreview/PassedTestPreview.h"
#include "PassedTestsColumnIndex.h"

using namespace PassedTests;

//  :: Constants ::

const QStringList kHorizontalHeaders {
    "Название теста",
    "Пройден"
};

const int UPDATE_INTERVAL = 5000;

//  :: Lifecycle ::

PassedTestsModel::PassedTestsModel(QObject *parent/*= nullptr*/)
    : QAbstractTableModel(parent)
{
    initTimer();
}

//  :: QAbstractTableModel ::

int PassedTestsModel::rowCount(const QModelIndex &) const {
    return m_previews.size();
}

int PassedTestsModel::columnCount(const QModelIndex &) const {
    return NUMBER_OF_COLUMNS;
}

QVariant PassedTestsModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        auto preview = m_previews[index.row()];
        switch (index.column()) {
        case NAME_COLUMN_INDEX:
            return preview.getName();
        case NUMBER_OF_PASSES_COLUMN_INDEX:
            return preview.getNumberOfPasses();
        }
    }
    return QVariant();
}

QVariant PassedTestsModel::headerData(int section,
                                      Qt::Orientation orientation,
                                      int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section < kHorizontalHeaders.size()) {
                return kHorizontalHeaders[section];
            }
        } else {
            return section + 1;
        }
    }
    return QVariant();
}

//  :: Public accessors ::
//  :: Passed test previews ::
QList<PassedTestPreview> PassedTestsModel::getPassedTestPreviews() const {
    return m_previews;
}
void PassedTestsModel::setPassedTestPreviews(const QList<PassedTestPreview> &previews) {
    checkRowsCountChanged(previews);
    m_previews = previews;
    emitAllDataChanged();
}

//  :: Service ::
PassedTestsService *PassedTestsModel::getService() const {
    return m_service;
}
void PassedTestsModel::setService(PassedTestsService *service) {
    m_service = service;
    connect(m_service, &PassedTestsService::previewsGot,
            this, &PassedTestsModel::setPassedTestPreviews);
    connect(m_timer, &QTimer::timeout,
            m_service, &PassedTestsService::getPreviews);
}

//  :: Public methods ::

int PassedTestsModel::getId(const QModelIndex &index) const {
    if (index.isValid()) {
        return getPassedTestPreviews()[index.row()].getId();
    }
    return 0;
}

//  :: Public slots ::

void PassedTestsModel::startUpdating() const {
    m_service->getPreviews();
    m_timer->start();
}

void PassedTestsModel::stopUpdating() const {
    m_timer->stop();
}

//  :: Private methods ::

inline
void PassedTestsModel::initTimer() {
    m_timer = new QTimer(this);
    m_timer->setInterval(UPDATE_INTERVAL);
}

inline
void PassedTestsModel::checkRowsCountChanged(const QList<PassedTestPreview> &newPreviews) {
    if (m_previews.size() < newPreviews.size()) {
        beginInsertRows(QModelIndex(), m_previews.size(), newPreviews.size() - 1);
        endInsertRows();
    } else if (m_previews.size() > newPreviews.size()) {
        beginRemoveRows(QModelIndex(), newPreviews.size(), m_previews.size() - 1);
        endRemoveRows();
    }
}

inline
void PassedTestsModel::emitAllDataChanged() {
    auto topLeft = index(0, 0);
    auto bottomRight = index(m_previews.size() - 1,
                             NUMBER_OF_COLUMNS - 1);
    emit dataChanged(topLeft, bottomRight);
}
