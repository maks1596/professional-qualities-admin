#pragma once

#include <QAbstractTableModel>

#include "Entities/Statistics/GroupCorrelations/GroupCorrelations.h"

class CorrelationsService;

class CorrelationsModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit CorrelationsModel(int testId, int scaleId, QObject *parent = nullptr);

    //  :: QAbstractTableModel ::
    //  :: Header ::
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant headerDataForDisplayRole(int section, Qt::Orientation orientation) const;
    QVariant headerDataForToolTipRole(int section, Qt::Orientation orientation) const;

    //  :: Basic functionality ::
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //  :: Accessors ::

    int getTestId() const;
    int getScaleId() const;

    CorrelationsService *getService() const;
    void setService(CorrelationsService *service);

    const QList<GroupCorrelations> &getGroupsCorrelations() const;
    void setGroupsCorrelations(const QList<GroupCorrelations> &groupsCorrelations);

private:
    int m_testId;
    int m_scaleId;
    CorrelationsService *m_service;
    QList<GroupCorrelations> m_groupsCorrelations;
};
