#pragma once

#include "../ResultStatistics/ResultStatistics.h"
#include "Serializable/Object/SerializableObject.h"
#include "Tree.h"

class GroupResults : public SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    QString getGroupName() const;
    void setGroupName(const QString &groupName);

    QList<ResultStatistics> getResults() const;
    void setResults(const QList<ResultStatistics> &results);

    Tree::Nodes<Indicator> resultsToTreeNodes() const;

private:
    QString m_groupName;
    QList<ResultStatistics> m_results;
};
