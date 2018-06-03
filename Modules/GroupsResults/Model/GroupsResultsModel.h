#pragma once

#include <QObject>

#include "Entities/Statistics/GroupResults/GroupResults.h"

class GroupsResultsModel : public QObject {
    Q_OBJECT
public:

    //  :: Lifeycle ::
    explicit GroupsResultsModel(const QList<GroupResults> &groupsResults,
                                QObject *parent = nullptr);

    //  :: Accessors ::
    const QList<GroupResults> &getGroupsResults() const;
    void setGroupsResults(const QList<GroupResults> &groupsResults);

    uint getNumberOfGroups() const;
    GroupResults getGroupResults(uint index) const;
    QString getGroupName(uint index) const;

private:
    QList<GroupResults> m_groupsResults;
};
