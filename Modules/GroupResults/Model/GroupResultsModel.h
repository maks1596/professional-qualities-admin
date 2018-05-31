#pragma once

#include <QAbstractTableModel>

#include "Entities/Statistics/Indicator/Indicator.h"
#include "Tree.h"

class GroupResults;
class NamedValue;

class GroupResultsModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit GroupResultsModel(const GroupResults &groupResults,
                               QObject *parent = nullptr);

    //  :: QAbstractTableModel ::

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);

    bool hasChildren(const QModelIndex &parent) const;

    //  :: Accessors ::

    QString getGroupName() const;

private:
    int findRow(const Tree::NodePtr<NamedValue> &node) const;

    QString m_groupName;
    Tree::NodePtrs<NamedValue> m_nodes;
};
