#pragma once

#include <QAbstractTableModel>

#include "Entities/Statistics/GroupCorrelations/GroupCorrelations.h"

class CorrelationsModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit CorrelationsModel(QObject *parent = nullptr);

    //  :: QAbstractTableModel ::
    //  :: Header ::
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //  :: Basic functionality ::
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //  :: Accessors ::

    const QList<GroupCorrelations> &getGroupsCorrelations() const;
    void setGroupsCorrelations(const QList<GroupCorrelations> &groupsCorrelations);

private:
    void checkRowCount(const QList<GroupCorrelations> newGroupsCorrelations);
    void checkColumnCount(const QList<GroupCorrelations> newGroupsCorrelations);


    int rowCount(const QList<GroupCorrelations> groupsCorrelations) const;
    int columnCount(const QList<GroupCorrelations> groupsCorrelations) const;

    void emitAllDataChanged();

    QList<GroupCorrelations> m_groupsCorrelations;
};
