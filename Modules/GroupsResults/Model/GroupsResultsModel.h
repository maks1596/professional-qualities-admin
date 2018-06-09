#pragma once

#include <QAbstractTableModel>

#include "Entities/Statistics/GroupsResultsTree/GroupsResultsTree.h"

class GroupsResultsModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit GroupsResultsModel(const QList<GroupResults> &groupsResults,
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
    void setGroupsResults(const QList<GroupResults> &groupsResults);
    void addGroupResults(const GroupResults &groupResults);

private:
    // :: Methods ::

    QString getGroupName(uint groupIndex) const;

    Tree::NodePtrs<NamedValues> getResultNodePtrs() const;
    Tree::NodePtr<NamedValues> getResultNodePtr(uint groupIndex) const;

    int findRow(const Tree::NodePtr<NamedValues> &node) const;

    GroupsResultsTree m_groupsResultsTree;
};
