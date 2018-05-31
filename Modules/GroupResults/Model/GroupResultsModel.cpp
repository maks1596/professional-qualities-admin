#include "GroupResultsModel.h"

#include "Entities/Statistics/GroupResults/GroupResults.h"

using TreeNodePtr = Tree::NodePtr<Indicator>;
using TreeNodePtrs = Tree::NodePtrs<Indicator>;

//  :: Constants ::

enum ColumnIndex {
    RAMIFICATION_COLUMN_INDEX,
    NAME_COLUMN_INDEX,
    VALUE_COLUMN_INDEX,
    COLUMN_COUNT
};

const QStringList kHorizontalHeaders {
    "",
    "Название",
    "Значение"
};

//  :: Lifecycle ::

GroupResultsModel::GroupResultsModel(const GroupResults &groupResults,
                                     QObject *parent)
    : QAbstractTableModel(parent)
{
    m_groupName = groupResults.getGroupName();
    m_nodes = groupResults.resultsToTreeNodePtrs();
}

//  :: QAbstratTableModel ::

QVariant GroupResultsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal) {
        if (section < COLUMN_COUNT) {
            if (role == Qt::DisplayRole) {
                return kHorizontalHeaders[section];
            }
        }
    }
    return section;
}

int GroupResultsModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid()) {
        return m_nodes.size();
    }
    auto parentNodePtr = *(static_cast<const TreeNodePtr*>(parent.internalPointer()));
    return parentNodePtr->children.size();
}

int GroupResultsModel::columnCount(const QModelIndex &) const {
    return kHorizontalHeaders.size();
}

QVariant GroupResultsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    auto nodePtr = *(static_cast<TreeNodePtr *>(index.internalPointer()));
    const Indicator& indicator = nodePtr->data;

    switch (index.column()) {
    case NAME_COLUMN_INDEX: {
        return indicator.getName();
    } break;

    case VALUE_COLUMN_INDEX: {
        if (nodePtr->children.isEmpty()) {
            return indicator.getValue();
        }
    } break;
    }
    return QVariant();
}

QModelIndex GroupResultsModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (!parent.isValid()) {    // запрашивают индексы корневых узлов
        return createIndex(row, column, const_cast<TreeNodePtr *>(&m_nodes[row]));
    }

    auto parenNodePtr = *(static_cast<TreeNodePtr *>(parent.internalPointer()));
    return createIndex(row, column, &parenNodePtr->children[row]);
}

QModelIndex GroupResultsModel::parent(const QModelIndex &child) const {
    if (!child.isValid()) {
        return QModelIndex();
    }

    auto childNodePtr = *(static_cast<TreeNodePtr *>(child.internalPointer()));
    auto parentNodePtr = childNodePtr->parent;
    if (parentNodePtr != nullptr) { // parent запрашивается не у корневого элемента
        return createIndex(findRow(parentNodePtr), RAMIFICATION_COLUMN_INDEX, &parentNodePtr);
    } else {
        return QModelIndex();
    }
}

//  :: Public accessors ::

QString GroupResultsModel::getGroupName() const {
    return m_groupName;
}

//  :: Private methods ::

int GroupResultsModel::findRow(const Tree::NodePtr<Indicator> &node) const {
    auto parentChildren = node->parent != nullptr ?
                          node->parent->children : m_nodes;
    return parentChildren.indexOf(node);
}
