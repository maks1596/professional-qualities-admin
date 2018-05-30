#pragma once

#include "../GroupResults/GroupResults.h"
#include "../ResultStatistics/ResultStatistics.h"
#include "Serializable/Object/SerializableObject.h"

class ScaleStatistics : public SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    int getId() const;
    void setId(int id);

    QString getName() const;
    void setName(const QString &name);

    QList<GroupResults> getGroupsResults() const;
    void setGroupsResults(const QList<GroupResults> &groupsResults);

private:
    int m_id;
    QString m_name;
    QList<GroupResults> m_groupsResults;
};
