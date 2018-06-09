#pragma once

#include "Entities/Statistics/IndicatorGroup/IndicatorGroup.h"
#include "Serializable/Object/SerializableObject.h"
#include "Tree.h"

class NamedValue;

class ResultStatistics : public SerializableObject {
public:

    //  :: Lifecycle ::
    virtual ~ResultStatistics() noexcept = default;

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    QString getFormulation() const;
    void setFormulation(const QString &formulation);

    uint getTimes() const;
    void setTimes(const uint &times);

    double getFrequency() const;
    void setFrequency(double frequency);

    const QList<IndicatorGroup> &getIndicatorGroups() const;
    void setIndicatorGroups(const QList<IndicatorGroup> &indicatorGroups);

    //  :: Methods ::

    Tree::NodePtr<NamedValue> toTreeNodePtr() const;

private:
    Tree::NodePtr<NamedValue> timesToTreeNodePtr(const Tree::NodePtr<NamedValue> &parent) const;
    Tree::NodePtr<NamedValue> frequencyToTreeNodePtr(const Tree::NodePtr<NamedValue> &parent) const;

    Tree::NodePtrs<NamedValue> indicatorGroupsToNodePtrs(const Tree::NodePtr<NamedValue> &parent) const;

    QString m_formulation;
    uint m_times;
    double m_frequency;
    QList<IndicatorGroup> m_indicatorGroups;
};
