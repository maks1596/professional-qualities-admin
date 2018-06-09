#pragma once

#include "../Indicator/Indicator.h"
#include "Serializable/Object/SerializableObject.h"
#include "Tree.h"

class NamedValue;

class IndicatorGroup : public SerializableObject {
public:

    //  :: Lifecycle ::
    virtual ~IndicatorGroup() noexcept = default;

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    QString getName() const;
    void setName(const QString &name);

    QList<Indicator> getIndicators() const;
    void setIndicators(const QList<Indicator> &indicators);

    Tree::NodePtr<NamedValue> toTreeNodePtr(const Tree::NodePtr<NamedValue> &parent) const;

private:
    Tree::NodePtrs<NamedValue> indicatorsToTreeNodePtrs(const Tree::NodePtr<NamedValue> &parent) const;

    QString m_name;
    QList<Indicator> m_indicators;
};
