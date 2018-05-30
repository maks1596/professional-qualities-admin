#pragma once

#include <QAbstractTableModel>

#include "Entities/Statistics/Indicator/Indicator.h"
#include "Tree.h"

class GroupResults;
class Indicator;

class GroupResultsModel : public QAbstractTableModel {
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

    //  :: Accessors ::

    QString getGroupName() const;

private:
    int findRow(const Tree::Node<Indicator> &node) const;

    QString m_groupName;
    Tree::Nodes<Indicator> m_nodes;
};
