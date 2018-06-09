#include "GroupsResultsModel.h"

#include "GroupsResultsColumnIndex.h"
#include "NamedValues/NamedValues.h"

//  :: Type definitions ::

using Node = Tree::Node<NamedValues>;
using NodePtr = Tree::NodePtr<NamedValues>;
using NodePtrs = Tree::NodePtrs<NamedValues>;

//  :: Constants ::

const QString NAME_HORIZONTAL_HEADER_LABEL;

//  :: Lifecycle ::

GroupsResultsModel::GroupsResultsModel(const QList<GroupResults> &groupsResults,
                                       QObject *parent)
    : QAbstractItemModel(parent)
{
    setGroupsResults(groupsResults);
}

//  :: QAbstratTableModel ::

QVariant GroupsResultsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section < columnCount()) {
            if (section == NAME_COLUMN_INDEX) {
                return NAME_HORIZONTAL_HEADER_LABEL;
            } else {
                return getGroupName(section - DEFINED_COLUMNS_COUNT);
            }
        }
    }
    return QVariant();
}

int GroupsResultsModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid()) {
        return m_groupsResultsTree.resultsCount();
    }
    auto parentNodePtr = static_cast<const Node *>(parent.internalPointer());
    return parentNodePtr->childrenCount();
}

int GroupsResultsModel::columnCount(const QModelIndex &) const {
    return m_groupsResultsTree.groupsCount() + DEFINED_COLUMNS_COUNT;
}

QVariant GroupsResultsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    auto nodePtr = static_cast<Node *>(index.internalPointer());
    auto namedValue = nodePtr->getData();

    if (index.column() == NAME_COLUMN_INDEX) {
        return namedValue.getName();
    } else {
        return namedValue.getValue(index.column() - DEFINED_COLUMNS_COUNT);
    }
    return QVariant();
}

QModelIndex GroupsResultsModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (!parent.isValid()) {    // запрашивают индексы корневых узлов
        return createIndex(row, column, const_cast<Node *>(getResultNodePtr(row).data()));
    }

    auto parenNodePtr = static_cast<Node *>(parent.internalPointer());
    return createIndex(row, column, parenNodePtr->child(row).data());
}

QModelIndex GroupsResultsModel::parent(const QModelIndex &child) const {
    if (!child.isValid()) {
        return QModelIndex();
    }

    auto childNodePtr = static_cast<Node *>(child.internalPointer());
    auto parentNodePtr = childNodePtr->getParent();
    if (parentNodePtr != nullptr) { // parent запрашивается не у корневого элемента
        return createIndex(findRow(parentNodePtr), RAMIFICATION_COLUMN_INDEX, parentNodePtr.data());
    } else {
        return QModelIndex();
    }
}

bool GroupsResultsModel::canFetchMore(const QModelIndex &parent) const {
    if (parent.isValid()) {
        auto parentNodePtr = static_cast<Node *>(parent.internalPointer());
        return parentNodePtr->hasChildren() && !parentNodePtr->isMapped();
    }
    return false;
}

void GroupsResultsModel::fetchMore(const QModelIndex &parent) {
    auto parentNodePtr = static_cast<Node *>(parent.internalPointer());
    beginInsertRows(parent, 0, parentNodePtr->childrenCount() - 1);
    parentNodePtr->setMapped(true);
    endInsertRows();
}

bool GroupsResultsModel::hasChildren(const QModelIndex &parent) const {
    if (parent.isValid()) {
        auto parentNode = static_cast<Node *>(parent.internalPointer());
        return parentNode->hasChildren();
    }
    return QAbstractItemModel::hasChildren(parent);
}

//  :: Public methods ::

void GroupsResultsModel::setGroupsResults(const QList<GroupResults> &groupsResults) {
    m_groupsResultsTree.setGroupsResults(groupsResults);
}

void GroupsResultsModel::addGroupResults(const GroupResults &groupResults) {
    m_groupsResultsTree.addGroupResults(groupResults);
}

//  :: Private methods ::

QString GroupsResultsModel::getGroupName(uint groupIndex) const {
    return m_groupsResultsTree.getGroupName(groupIndex);
}

Tree::NodePtrs<NamedValues> GroupsResultsModel::getResultNodePtrs() const {
    return m_groupsResultsTree.getResults();
}

Tree::NodePtr<NamedValues> GroupsResultsModel::getResultNodePtr(uint groupIndex) const {
    return m_groupsResultsTree.getResult(groupIndex);
}

int GroupsResultsModel::findRow(const Tree::NodePtr<NamedValues> &nodePtr) const {
    auto parentChildren = nodePtr->hasParent() ?
                          nodePtr->getParent()->getChildren() :
                          getResultNodePtrs();
    return parentChildren.indexOf(nodePtr);
}
