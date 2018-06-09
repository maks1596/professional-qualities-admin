#pragma once

#include "../ResultStatistics/ResultStatistics.h"
#include "Serializable/Object/SerializableObject.h"
#include "Tree.h"

class NamedValue;

class GroupResults : public SerializableObject {
public:

    //  :: Lifecycle ::
    virtual ~GroupResults() noexcept = default;

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    QString getGroupName() const;
    void setGroupName(const QString &groupName);

    const QList<ResultStatistics> &getResults() const;
    void setResults(const QList<ResultStatistics> &results);

    //  :: Methods ::
    Tree::NodePtrs<NamedValue> resultsToTreeNodePtrs() const;

private:
    QString m_groupName;
    QList<ResultStatistics> m_results;
};
