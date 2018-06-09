#pragma once

#include "Tree.h"

class GroupResults;
class NamedValues;
class ResultStatistics;

class GroupsResultsTree {
public:
    QString getGroupName(uint index) const;

    const Tree::NodePtrs<NamedValues> &getResults() const;
    const Tree::NodePtr<NamedValues> &getResult(uint index) const;

    int groupsCount() const;
    bool hasGroups() const;

    int resultsCount() const;
    bool hasResults() const;

    void setGroupsResults(const QList<GroupResults> &groupsResults);
    void addGroupResults(const GroupResults &groupResults);

private:
    bool hasResult(const QString &resultFormulation) const;
    void appendEmptyResult(const ResultStatistics &result);

    QStringList m_groupNames;
    Tree::NodePtrs<NamedValues> m_results;
};
