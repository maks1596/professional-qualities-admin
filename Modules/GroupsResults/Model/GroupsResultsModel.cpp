#include "GroupsResultsModel.h"

//  :: Lifecycle ::

GroupsResultsModel::GroupsResultsModel(const QList<GroupResults> &groupsResults, QObject *parent)
    : QObject(parent)
{
    setGroupsResults(groupsResults);
}

//  :: Public accessors ::

const QList<GroupResults> &GroupsResultsModel::getGroupsResults() const {
    return m_groupsResults;
}
void GroupsResultsModel::setGroupsResults(const QList<GroupResults> &groupsResults) {
    m_groupsResults = groupsResults;
}

//  :: Public methods ::

uint GroupsResultsModel::getNumberOfGroups() const {
    return getGroupsResults().size();
}

GroupResults GroupsResultsModel::getGroupResults(uint index) const {
    if (index < getNumberOfGroups()) {
        return getGroupsResults().at(index);
    }
    return GroupResults();
}

QString GroupsResultsModel::getGroupName(uint index) const {
    return getGroupResults(index).getGroupName();
}
