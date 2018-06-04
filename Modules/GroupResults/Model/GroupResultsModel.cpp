#include "GroupResultsModel.h"

#include "Entities/Statistics/GroupResults/GroupResults.h"
#include "GroupResultsColumnIndex.h"
#include "NamedValue/NamedValue.h"

using TreeNode = Tree::Node<NamedValue>;
using TreeNodePtr = Tree::NodePtr<NamedValue>;
using TreeNodePtrs = Tree::NodePtrs<NamedValue>;

//  :: Constants ::

const QStringList kHorizontalHeaders {
    "Название",
    "Значение"
};

//  :: Lifecycle ::

GroupResultsModel::GroupResultsModel(const GroupResults &groupResults,
                                     QObject *parent)
    : QAbstractItemModel(parent)
{
    m_groupName = groupResults.getGroupName();
    m_nodes = groupResults.resultsToTreeNodePtrs();
}

//  :: QAbstratTableModel ::

QVariant GroupResultsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section < COLUMN_COUNT) {
            return kHorizontalHeaders[section];
        }
    }
    return section + 1;
}

int GroupResultsModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid()) {
        return m_nodes.size();
    }
    auto parentNodePtr = static_cast<const TreeNode *>(parent.internalPointer());
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

    auto nodePtr = static_cast<TreeNode *>(index.internalPointer());
    auto namedValue = nodePtr->data;

    switch (index.column()) {
    case NAME_COLUMN_INDEX: {
        return namedValue.name;
    } break;

    case VALUE_COLUMN_INDEX: {
        return namedValue.value;
    } break;
    }
    return QVariant();
}

QModelIndex GroupResultsModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (!parent.isValid()) {    // запрашивают индексы корневых узлов
        return createIndex(row, column, const_cast<TreeNode *>(m_nodes[row].data()));
    }

    auto parenNodePtr = static_cast<TreeNode *>(parent.internalPointer());
    return createIndex(row, column, parenNodePtr->children[row].data());
}

QModelIndex GroupResultsModel::parent(const QModelIndex &child) const {
    if (!child.isValid()) {
        return QModelIndex();
    }

    auto childNodePtr = static_cast<TreeNode *>(child.internalPointer());
    auto parentNodePtr = childNodePtr->parent;
    if (parentNodePtr != nullptr) { // parent запрашивается не у корневого элемента
        return createIndex(findRow(parentNodePtr), RAMIFICATION_COLUMN_INDEX, parentNodePtr.data());
    } else {
        return QModelIndex();
    }
}

bool GroupResultsModel::canFetchMore(const QModelIndex &parent) const {
    if (parent.isValid()) {
        auto parentNodePtr = static_cast<TreeNode *>(parent.internalPointer());
        return !(parentNodePtr->children.isEmpty() || parentNodePtr->mapped);
    }
    return false;
}

void GroupResultsModel::fetchMore(const QModelIndex &parent) {
    auto parentNodePtr = static_cast<TreeNode *>(parent.internalPointer());
    beginInsertRows(parent, 0, parentNodePtr->children.size() - 1);
    parentNodePtr->mapped = true;
    endInsertRows();
}

bool GroupResultsModel::hasChildren(const QModelIndex &parent) const {
    if (parent.isValid()) {
        auto parentNode = static_cast<TreeNode *>(parent.internalPointer());
        return !(parentNode->children.isEmpty());
    }
    return QAbstractItemModel::hasChildren(parent);
}

//  :: Public accessors ::

QString GroupResultsModel::getGroupName() const {
    return m_groupName;
}

//  :: Private methods ::

int GroupResultsModel::findRow(const Tree::NodePtr<NamedValue> &node) const {
    auto parentChildren = node->parent != nullptr ?
                          node->parent->children : m_nodes;
    return parentChildren.indexOf(node);
}
