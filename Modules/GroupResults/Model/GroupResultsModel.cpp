#include "GroupResultsModel.h"

#include "Entities/Statistics/GroupResults/GroupResults.h"

using TreeNode = Tree::Node<Indicator>;
using TreeNodes = Tree::Nodes<Indicator>;

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
    m_nodes = groupResults.resultsToTreeNodes();
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
    const TreeNode* parentNode = static_cast<const TreeNode*>(parent.internalPointer());
    return parentNode->children.size();
}

int GroupResultsModel::columnCount(const QModelIndex &) const {
    return kHorizontalHeaders.size();
}

QVariant GroupResultsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const TreeNode* node = static_cast<TreeNode *>(index.internalPointer());
    const Indicator& indicator = node->data;

    switch (index.column()) {
    case NAME_COLUMN_INDEX: {
        return indicator.getName();
    } break;

    case VALUE_COLUMN_INDEX: {
        if (node->children.isEmpty()) {
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
        return createIndex(row, column, const_cast<TreeNode *>(&m_nodes[row]));
    }

    TreeNode* parenNode = static_cast<TreeNode *>(parent.internalPointer());
    return createIndex(row, column, &parenNode->children[row]);
}

QModelIndex GroupResultsModel::parent(const QModelIndex &child) const {
    if (!child.isValid()) {
        return QModelIndex();
    }

    TreeNode* childNode = static_cast<TreeNode *>(child.internalPointer());
    TreeNode* parentNode = childNode->parent;
    if (parentNode != nullptr) { // parent запрашивается не у корневого элемента
        return createIndex(findRow(*parentNode), RAMIFICATION_COLUMN_INDEX, parentNode);
    }
    else {
        return QModelIndex();
    }
}

//  :: Public accessors ::

QString GroupResultsModel::getGroupName() const {
    return m_groupName;
}

//  :: Private methods ::

int GroupResultsModel::findRow(const TreeNode &node) const {
    auto parentChildren = node.parent != nullptr ?
                          node.parent->children : m_nodes;
    return parentChildren.indexOf(node);
}
