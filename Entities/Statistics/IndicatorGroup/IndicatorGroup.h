#pragma once

#include "../Indicator/Indicator.h"
#include "Serializable/Object/SerializableObject.h"
#include "Tree.h"

class IndicatorGroup : public SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    QString getName() const;
    void setName(const QString &name);

    QList<Indicator> getIndicators() const;
    void setIndicators(const QList<Indicator> &indicators);

    Tree::NodePtr<Indicator> toTreeNodePtr(const Tree::NodePtr<Indicator> &parent) const;
    Tree::NodePtrs<Indicator> indicatorsToTreeNodePtrs(const Tree::NodePtr<Indicator> &parent) const;

private:
    QString m_name;
    QList<Indicator> m_indicators;
};
